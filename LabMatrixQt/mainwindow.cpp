#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableWidget>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Сложение матриц");
    setupConnections();

    resizeTable(ui-> tableA, ui->spinBoxStrA->value(), ui->spinBoxSlbA->value());
    resizeTable(ui-> tableB, ui->spinBoxStrB->value(), ui->spinBoxSlbB->value());
    resizeTable(ui->tableRes, 0 ,0);

    validateAll();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupConnections()
{
    connect(ui->spinBoxStrA, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::onSpinBoxStrAChanged);
    connect(ui->spinBoxSlbA, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::onSpinBoxSlbAChanged);
    connect(ui->spinBoxStrB, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::onSpinBoxStrBChanged);
    connect(ui->spinBoxSlbB, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::onSpinBoxSlbBChanged);



    connect(ui->tableA, &QTableWidget::itemChanged,
            this, &MainWindow::onTableItemChanged);
    connect(ui->tableB, &QTableWidget::itemChanged,
            this, &MainWindow::onTableItemChanged);



    connect(ui->btnCalculate, &QPushButton::clicked,
            this, &MainWindow::onCalculateClicked);
    connect(ui->btnIncrA, &QPushButton::clicked,
            this, &MainWindow::onIncrementAClicked);
    connect(ui->btnIncrB, &QPushButton::clicked,
            this, &MainWindow::onIncrementBClicked);
    connect(ui->btnIncrResult, &QPushButton::clicked,
            this, &MainWindow::onIncrementResultClicked);
}


void MainWindow::resizeTable(QTableWidget *table, int str, int slb){
    table->blockSignals(true);

    int oldStr = table->rowCount();
    int oldSlb = table->columnCount();

    table->setRowCount(str);
    table->setColumnCount(slb);

    for (int i = 0; i < str; ++i) {
        for (int j = 0; j < slb; ++j) {
            QTableWidgetItem *item = new QTableWidgetItem("0");
            item->setTextAlignment(Qt::AlignRight | Qt::AlignCenter);
            table->setItem(i, j, item);
        }
    }

    table->blockSignals(false);
    validateAll();
}


void MainWindow::fillTableFromMatrix(QTableWidget *table, const mt::matrix &mat){
    size_t str = mat.get_str();
    size_t slb = mat.get_slb();

    table->blockSignals(true);
    table->setRowCount(static_cast<int>(str));
    table->setColumnCount(static_cast<int>(slb));

    for (int i = 0; i < str; ++i) {
        for (int j = 0; j < slb; ++j) {
            double value = mat.sh(i, j);

            QTableWidgetItem *item = new QTableWidgetItem(QString::number(value, 'g', 6));
            item->setTextAlignment(Qt::AlignRight | Qt::AlignCenter);
            table->setItem(static_cast<int>(i), static_cast<int>(j), item);
        }
    }

    table->blockSignals(false);
}

mt::matrix MainWindow::readMat(QTableWidget *table,bool &ok)const
{
    ok = true;
    int str = table->rowCount();
    int slb = table->columnCount();

    if(str==0 || slb==0){
        return mt::matrix(0,0);
    }
    mt::matrix mat(static_cast<int>(str),static_cast<int>(slb));

    for (int i=0;i<str;++i){
        for(int j=0;j<slb;++j){
            QTableWidgetItem *item = table->item(i,j);
            if(!item || item->text().isEmpty()){
                mat.sh(i,j)=0.0;
                continue;
            }
            bool convOk;
            double val = item->text().toDouble(&convOk);
            if (!convOk) {
                ok = false;
                return mt::matrix(0, 0);
            }
            mat.sh(i, j) = val;
        }
    }
    return mat;
}


bool MainWindow::validateAll()
{
    bool okA, okB;
    mt::matrix A = readMat(ui->tableA, okA);
    mt::matrix B = readMat(ui->tableB, okB);

    QString errorText;

    if (!okA) {
        errorText = "Матрица A содержит некорректные символы.";
        ui->labelErrorA->setText(errorText);
    } else {
        ui->labelErrorA->clear();
    }

    if (!okB) {
        errorText = "Матрица B содержит некорректные символы.";
        ui->labelErrorB->setText(errorText);
    } else {
        ui->labelErrorB->clear();
    }

    if (!okA || !okB) {
        ui->labelErrorResult->clear();
        return false;
    }

    if (A.get_str() != B.get_str() || A.get_slb() != B.get_slb()) {
        ui->labelErrorResult->setText("Размеры матриц не совпадают. Сложение невозможно.");
        return false;
    }

    ui->labelErrorResult->clear();
    return true;
}
void MainWindow::onTableItemChanged(QTableWidgetItem *item)
{
    validateAll();
}


void MainWindow::onSpinBoxStrAChanged(int str)
{
    resizeTable(ui->tableA, str, ui->spinBoxSlbA->value());
}

void MainWindow::onSpinBoxSlbAChanged(int slb)
{
    resizeTable(ui->tableA, ui->spinBoxStrA->value(), slb);
}

void MainWindow::onSpinBoxStrBChanged(int str)
{
    resizeTable(ui->tableB, str, ui->spinBoxSlbB->value());
}

void MainWindow::onSpinBoxSlbBChanged(int slb)
{
    resizeTable(ui->tableB, ui->spinBoxStrB->value(), slb);
}


void MainWindow::onCalculateClicked()
{
    if (!validateAll()) {
        return;
    }

    bool okA, okB;
    mt::matrix A = readMat(ui->tableA, okA);
    mt::matrix B = readMat(ui->tableB, okB);
    if (!okA || !okB) return;

    try {
        mt::matrix result = A + B;
        fillTableFromMatrix(ui->tableRes, result);
    } catch (const std::exception &e) {
        ui->labelErrorResult->setText(QString("Ошибка: ") + e.what());
    }
}

void MainWindow::onIncrementAClicked()
{
    bool ok;
    mt::matrix A = readMat(ui->tableA, ok);
    if (!ok) {
        ui->labelErrorA->setText("Некорректные данные в матрице A. Инкремент невозможен.");
        return;
    }
    ++A;
    fillTableFromMatrix(ui->tableA, A);
    validateAll();
}


void MainWindow::onIncrementBClicked()
{
    bool ok;
    mt::matrix B = readMat(ui->tableB, ok);
    if (!ok) {
        ui->labelErrorB->setText("Некорректные данные в матрице B. Инкремент невозможен.");
        return;
    }
    ++B;
    fillTableFromMatrix(ui->tableB, B);
    validateAll();
}

void MainWindow::onIncrementResultClicked()
{
    if (ui->tableRes->rowCount() == 0 || ui->tableRes->columnCount() == 0) {
        return;
    }

    bool ok;
    mt::matrix R = readMat(ui->tableRes, ok);
    if (!ok) {
        ui->labelErrorResult->setText("Некорректные данные в результирующей матрице.");
        return;
    }
    ++R;
    fillTableFromMatrix(ui->tableRes, R);
}
