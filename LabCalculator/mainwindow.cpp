#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::clearMessages()
{
    ui->labelError->clear();
}



bool MainWindow::getBigIntFromLineEdit(QLineEdit* edit, BigInt& num, QString& error)
{
    QString text = edit->text().trimmed();
    if (text.isEmpty()) {
        error = "Поле не может быть пустым";
        return false;
    }
    std::string str = text.toStdString();
    size_t start = (str[0] == '-') ? 1 : 0;
    if (str.length() - start > 1000) {
        error = "Число превышает 1000 цифр";
        return false;
    }
    try {
        num = BigInt(str);
    } catch (const std::exception& e) {
        error = QString("Ошибка: ") + e.what();
        return false;
    }
    return true;
}



void MainWindow::on_lineEditA_textChanged(const QString &text)
{
    if (text.isEmpty()) {
        ui->labelError->clear();
        return;
    }
    std::string str = text.toStdString();
    size_t start = (str[0] == '-') ? 1 : 0;
    if (str.length() - start > 1000) {
        ui->labelError->setText("Число A превышает 1000 цифр");
        return;
    }
    try {
        BigInt test(str);
        ui->labelError->clear();
    } catch (const std::exception& e) {
        ui->labelError->setText("Ошибка в числе A: " + QString(e.what()));
    }
}


void MainWindow::on_lineEditB_textChanged(const QString &text)
{
    if (text.isEmpty()) {
        ui->labelError->clear();
        return;
    }
    std::string str = text.toStdString();
    size_t start = (str[0] == '-') ? 1 : 0;
    if (str.length() - start > 1000) {
        ui->labelError->setText("Число B превышает 1000 цифр");
        return;
    }
    try {
        BigInt test(str);
        ui->labelError->clear();
    } catch (const std::exception& e) {
        ui->labelError->setText("Ошибка в числе B: " + QString(e.what()));
    }
}


void MainWindow::on_btnPlus_clicked()
{
    clearMessages();
    BigInt a, b;
    QString err;
    if (!getBigIntFromLineEdit(ui->lineEditA, a, err) ||
        !getBigIntFromLineEdit(ui->lineEditB, b, err)) {
        ui->labelError->setText(err);
        return;
    }
    BigInt result = a + b;
    ui->labelResult->setText(QString::fromStdString(result.toString()));
}


void MainWindow::on_btnMultiply_clicked()
{
    clearMessages();
    BigInt a, b;
    QString err;
    if (!getBigIntFromLineEdit(ui->lineEditA, a, err) ||
        !getBigIntFromLineEdit(ui->lineEditB, b, err)) {
        ui->labelError->setText(err);
        return;
    }
    BigInt result = a * b;
    ui->labelResult->setText(QString::fromStdString(result.toString()));
}


void MainWindow::on_btnIncrPreA_clicked()
{
    clearMessages();
    BigInt a;
    QString err;
    if (!getBigIntFromLineEdit(ui->lineEditA, a, err)) {
        ui->labelError->setText(err);
        return;
    }
    BigInt old = a;
    a++;
    ui->lineEditA->setText(QString::fromStdString(a.toString()));
    ui->labelResult->setText("Префиксный ++: было " + QString::fromStdString(old.toString()) + ", стало " + QString::fromStdString(a.toString()));
}


void MainWindow::on_btnIncrPostA_clicked()
{
    clearMessages();
    BigInt a;
    QString err;
    if (!getBigIntFromLineEdit(ui->lineEditA, a, err)) {
        ui->labelError->setText(err);
        return;
    }
    BigInt old = a;
    a++;
    ui->lineEditA->setText(QString::fromStdString(a.toString()));
    ui->labelResult->setText("Постфиксный ++: было " + QString::fromStdString(old.toString()) + ", вернул " + QString::fromStdString(old.toString()) + ", стало " + QString::fromStdString(a.toString()));
}


void MainWindow::on_btnIncrPreB_clicked()
{
    clearMessages();
    BigInt b;
    QString err;
    if (!getBigIntFromLineEdit(ui->lineEditB, b, err)) {
        ui->labelError->setText(err);
        return;
    }
    BigInt old = b;
    ++b;
    ui->lineEditB->setText(QString::fromStdString(b.toString()));
    ui->labelResult->setText("Префиксный ++: было " + QString::fromStdString(old.toString()) + ", стало " + QString::fromStdString(b.toString()));
}


void MainWindow::on_btnIncrPostB_clicked()
{
    clearMessages();
    BigInt b;
    QString err;
    if (!getBigIntFromLineEdit(ui->lineEditB, b, err)) {
        ui->labelError->setText(err);
        return;
    }
    BigInt old = b;
    b++;
    ui->lineEditB->setText(QString::fromStdString(b.toString()));
    ui->labelResult->setText("Постфиксный ++: было " + QString::fromStdString(old.toString()) + ", вернул " + QString::fromStdString(old.toString()) + ", стало " + QString::fromStdString(b.toString()));
}


void MainWindow::on_btnDivide_clicked()
{
    clearMessages();
    BigInt a, b;
    QString err;
    if (!getBigIntFromLineEdit(ui->lineEditA, a, err) ||
        !getBigIntFromLineEdit(ui->lineEditB, b, err)) {
        ui->labelError->setText(err);
        return;
    }
    if (b == BigInt("0")) {
        ui->labelError->setText("Деление на ноль невозможно");
        return;
    }
    try {
        BigInt result = a / b;
        ui->labelResult->setText(QString::fromStdString(result.toString()));
    } catch (const std::exception& e) {
        ui->labelError->setText(e.what());
    }
}


void MainWindow::on_btnOst_clicked()
{
    clearMessages();
    BigInt a, b;
    QString err;
    if (!getBigIntFromLineEdit(ui->lineEditA, a, err) ||
        !getBigIntFromLineEdit(ui->lineEditB, b, err)) {
        ui->labelError->setText(err);
        return;
    }
    if (b == BigInt("0")) {
        ui->labelError->setText("Деление на ноль невозможно");
        return;
    }
    try {
        BigInt result = a % b;
        ui->labelResult->setText(QString::fromStdString(result.toString()));
    } catch (const std::exception& e) {
        ui->labelError->setText(e.what());
    }
}


void MainWindow::on_btnPow_clicked()
{
    clearMessages();
    BigInt a;
    QString err;
    if (!getBigIntFromLineEdit(ui->lineEditA, a, err)) {
        ui->labelError->setText(err);
        return;
    }
    QString expStr = ui->lineEditB->text().trimmed();
    if (expStr.isEmpty()) {
        ui->labelError->setText("Введите показатель степени");
        return;
    }
    bool ok;
    int exponent = expStr.toInt(&ok);
    if (!ok || exponent < 0) {
        ui->labelError->setText("Показатель должен быть целым неотрицательным числом");
        return;
    }
    try {
        BigInt result = a.pow(exponent);
        ui->labelResult->setText(QString::fromStdString(result.toString()));
    } catch (const std::exception& e) {
        ui->labelError->setText(e.what());
    }
}


void MainWindow::on_btnKoren_clicked()
{
    clearMessages();
    BigInt a;
    QString err;
    if (!getBigIntFromLineEdit(ui->lineEditA, a, err)) {
        ui->labelError->setText(err);
        return;
    }
    QString degreeStr = ui->lineEditB->text().trimmed();
    if (degreeStr.isEmpty()) {
        ui->labelError->setText("Введите степень корня");
        return;
    }
    bool ok;
    int n = degreeStr.toInt(&ok);
    if (!ok || n <= 0) {
        ui->labelError->setText("Степень корня должна быть положительным целым числом");
        return;
    }
    try {
        BigInt result = a.root(n);
        ui->labelResult->setText(QString::fromStdString(result.toString()));
    } catch (const std::exception& e) {
        ui->labelError->setText(e.what());
    }
}


void MainWindow::on_btnCompare_clicked()
{
    clearMessages();
    BigInt a, b;
    QString err;
    if (!getBigIntFromLineEdit(ui->lineEditA, a, err) ||
        !getBigIntFromLineEdit(ui->lineEditB, b, err)) {
        ui->labelError->setText(err);
        return;
    }
    QString relation;
    if (a == b) relation = "==";
    else if (a < b) relation = "<";
    else relation = ">";
    ui->labelResult->setText(QString::fromStdString(a.toString() + " " + relation.toStdString() + " " + b.toString()));
}
