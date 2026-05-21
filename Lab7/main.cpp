#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <filesystem>
#include <sstream>
#include <map>
#include "exp/nloahman/json.hpp"

namespace fs = std::filesystem;


enum class FormatType {
    ASCII,
    BINARY,
    JSON,
    CSV,
    INI
};


struct FormatInfo{
    FormatType type;
    std::string extension;
    std::string name;
};




const FormatInfo FORMATS[] = {
    {FormatType::ASCII, ".txt"},
    {FormatType::BINARY, ".bin"},
    {FormatType::JSON, ".json"},
    {FormatType::CSV, ".csv"},
    {FormatType::INI, ".ini"},
};

std::string getExtension(FormatType type){
    for(const auto& info: FORMATS){
        if(info.type== type){
            return info.extension;
        }
    }
    return "";
}

std::string getFormatName(FormatType type){
    for(const auto& info: FORMATS){
        if(info.type== type){
            return info.name;
        }
    }
    return "UNKNOWN";
}

FormatType getTypeFromExtension(const std::string& extension){
    for(const auto& info: FORMATS){
        if(info.extension == extension){
            return info.type;
        }
    }
}



class FormatProcessor {
public:
    FormatProcessor(const std::string& filename) : filename_(filename) {}
    virtual ~FormatProcessor() = default;
    virtual std::string Read() = 0;
    virtual void Write(const std::string&) = 0;
    virtual void Write(int) = 0;

protected:
    std::ifstream in_;
    std::ofstream out_;
    std::string value_;
    std::string filename_;
};


class ASCIIProcessor : public FormatProcessor {
public:
    using FormatProcessor::FormatProcessor;

    std::string Read() override {
        in_.open(filename_);
        if (!in_.is_open()) {
            throw std::runtime_error("[Read]: file not opened");
        }
        std::string content;
        std::string line;
        while(std::getline(in_, line)){
            content += line + "\n";
        }
        in_.close();
        return content;
    }
    
    void Write(const std::string& msg) override {
        out_.open(filename_, std::ios::trunc);
        if (!out_.is_open()) {
            throw std::runtime_error("[Write]: file not opened");
        }
        out_ << msg;
        out_.close();
    }
    
    void Write(int value) override {
        out_.open(filename_);
        if (!out_.is_open()) {
            throw std::runtime_error("[Write]: file not opened");
        }
        out_ << value;
        out_.close();
    }
};


class BinaryProcessor : public FormatProcessor {
public:
    using FormatProcessor::FormatProcessor;

    std::string Read() override {
        in_.open(filename_, std::ios::binary);
        if (!in_.is_open()) {
            throw std::runtime_error("[Read]: file not opened");
        }
        int x;
        in_.read(reinterpret_cast<char*>(&x), sizeof(int));
        in_.close();
        return std::to_string(x);
    }
    
    void Write(const std::string& msg) override {
        out_.open(filename_, std::ios::binary);
        if (!out_.is_open()) {
            throw std::runtime_error("[Write]: file not opened");
        }
        out_ << msg;
        out_.close();
    }
    
    void Write(int value) override {
        out_.open(filename_, std::ios::binary);
        if (!out_.is_open()) {
            throw std::runtime_error("[Write]: file not opened");
        }
        out_.write(reinterpret_cast<const char*>(&value), sizeof(int));
        out_.close();
    }
};


class JSONProcessor : public FormatProcessor {
public:
    using FormatProcessor::FormatProcessor;

    std::string Read() override {
        in_.open(filename_);
        if (!in_.is_open()) {
            throw std::runtime_error("[Read]: file not opened");
        }
        nlohmann::json data;
        in_ >> data;
        in_.close();
        
        if (data.contains("age")) {
            return std::to_string(data["age"].get<int>());
        }
        if (data.contains("message")) {
            return data["message"].get<std::string>();
        }
        return data;
    }
    
    void Write(const std::string& msg) override {
        out_.open(filename_);
        if (!out_.is_open()) {
            throw std::runtime_error("[Write]: file not opened");
        }
        nlohmann::json output_data = {
            {"message", msg}
        };
        out_ << output_data;
        out_.close();
    }
    
    void Write(int value) override {
        out_.open(filename_);
        if (!out_.is_open()) {
            throw std::runtime_error("[Write]: file not opened");
        }
        nlohmann::json output_data = {
            {"age", value}
        };
        out_ << output_data;
        out_.close();
    }
};


class CSVProcessor : public FormatProcessor {
private:
    std::vector<std::vector<std::string>> data_;
    std::vector<std::string> headers_;             
    
    std::vector<std::string> splitLine(const std::string& line) {
        std::vector<std::string> cells;
        std::string cell;
        
        for (char c : line) {
            if (c == ',') {
                cells.push_back(cell);
                cell.clear();           
            } else {
                cell += c; 
            }
        }
        cells.push_back(cell); 
        
        return cells;
    }
public:    
    using FormatProcessor::FormatProcessor;

    void loadFile() {
        data_.clear();
        headers_.clear();
        
        in_.open(filename_);
        if (!in_.is_open()) {
            throw std::runtime_error("Cannot open file");
        }
        
        std::string line;
        
        if (std::getline(in_, line)) {
            headers_ = splitLine(line);
        }
        
        while (std::getline(in_, line)) {
            if (!line.empty()) {
                data_.push_back(splitLine(line));
            }
        }
        
        in_.close();
    }
    
    
    std::string getValue(int row, int col) {
        if (row < 0 || row >= (int)data_.size()) {
            return "ERROR: row out of range";
        }
        if (col < 0 || col >= (int)headers_.size()) {
            return "ERROR: column out of range";
        }
        if (col >= (int)data_[row].size()) {
            return ""; 
        }
        return data_[row][col];
    }

    std::string Read() override {
        loadFile();

        if(data_.empty() || headers_.empty()){
            return "";
        }
        std::string result;

        for (size_t i = 0; i < headers_.size(); ++i) {
        result += headers_[i];
            if (i < headers_.size() - 1) result += ",";
        }
        result += "\n";
        

        for (size_t row = 0; row < data_.size(); ++row) {
            for (size_t col = 0; col < headers_.size(); ++col) {
                if (col < data_[row].size()) {
                    result += data_[row][col];
                }
                if (col < headers_.size() - 1) result += ",";
            }
            if (row < data_.size() - 1) result += "\n";
        }
        
        return result;
    }
    
    void Write(const std::string& msg) override {
        out_.open(filename_);
        if (!out_.is_open()) {
            throw std::runtime_error("[Write]: file not opened");
        }
        out_ << "message\n";
        out_ << msg;
        out_.close();
    }
    
    void Write(int value) override {
        out_.open(filename_);
        if (!out_.is_open()) {
            throw std::runtime_error("[Write]: file not opened");
        }
        out_ << "number\n";
        out_ << value;
        out_.close();
    }
};


class INIProcessor : public FormatProcessor {
public:
    using FormatProcessor::FormatProcessor;

    std::string Read() override {
        in_.open(filename_);
        if (!in_.is_open()) {
            throw std::runtime_error("[Read]: file not opened");
        }
        
        std::map<std::string, std::string> config;
        std::string line;
        std::string current_section;
        
        while (std::getline(in_, line)) {
            line.erase(0, line.find_first_not_of(" \t\r\n"));
            line.erase(line.find_last_not_of(" \t\r\n") + 1);
            
            if (line.empty() || line[0] == ';' || line[0] == '#') {
                continue;
            }
            
            if (line[0] == '[' && line.back() == ']') {
                current_section = line.substr(1, line.length() - 2);
            }

            else if (line.find('=') != std::string::npos) {
                size_t eq_pos = line.find('=');
                std::string key = line.substr(0, eq_pos);
                std::string value = line.substr(eq_pos + 1);
                
                key.erase(0, key.find_first_not_of(" \t"));
                key.erase(key.find_last_not_of(" \t") + 1);
                value.erase(0, value.find_first_not_of(" \t"));
                value.erase(value.find_last_not_of(" \t") + 1);
                
                std::string full_key = current_section.empty() ? key : current_section + "." + key;
                config[full_key] = value;
            }
        }
        in_.close();
        
        if (config.find("data.value") != config.end()) {
            return config["data.value"];
        }
        if (config.find("value") != config.end()) {
            return config["value"];
        }
        if (config.find("message") != config.end()) {

            return config["message"];
        }
        
        return "";
    }
    
    void Write(const std::string& msg) override {
        out_.open(filename_);
        if (!out_.is_open()) {
            throw std::runtime_error("[Write]: file not opened");
        }
        
        out_ << "[data]\n";
        out_ << "message = " << msg << "\n";
        out_.close();
    }
    
    void Write(int value) override {
        out_.open(filename_);
        if (!out_.is_open()) {
            throw std::runtime_error("[Write]: file not opened");
        }
        
        out_ << "[data]\n";
        out_ << "value = " << value << "\n";
        out_.close();
    }
};





FormatType define_type(const fs::path& filename) {
   std::string ext = filename.extension().string();
   return getTypeFromExtension(ext);
}


FormatProcessor* create_processor(FormatType type, const std::string& filename) {
    switch (type) {

        case FormatType::ASCII:
            return new ASCIIProcessor(filename);
        case FormatType::BINARY:
            return new BinaryProcessor(filename);
        case FormatType::JSON:
            return new JSONProcessor(filename);
        case FormatType::CSV:
            return new CSVProcessor(filename);
        case FormatType::INI:
            return new INIProcessor(filename);
        default:
            throw std::invalid_argument("[create_processor]: not supported type");
    }
}


class ProcessorFacade {
public:
    void Create(const std::vector<fs::path>& filenames) {
        for (const auto& filename : filenames) {
            FormatType type = define_type(filename);
            FormatProcessor* processor = create_processor(type, filename.string());
            processors_.push_back(processor);
        }
    }
    
    ~ProcessorFacade() {
        for (auto processor : processors_) {
            delete processor;
        }
    }
    
    void Write(int value) {
        for (auto processor : processors_) {
            processor->Write(value);
        }
        std::cout << "Integer value " << value << " written to all files" << std::endl;
    }
    
    void Write(const std::string& message) {
        for (auto processor : processors_) {
            processor->Write(message);
        }
        std::cout << "String message \"" << message << "\" written to all files" << std::endl;
    }
    
    std::vector<std::string> ReadAll() {
        std::vector<std::string> results;
        for (auto processor : processors_) {
            results.push_back(processor->Read());
        }
        return results;
    }
    
private:
    std::vector<FormatProcessor*> processors_;
};


int main() {
    ProcessorFacade processors_facade;
    
   try {
        
        processors_facade.Create({
            "data.txt", 
            "data.bin", 
            "data.json",
            "data.csv",
            "config.ini"
        });
        
        std::cout << "1. Запись числовых данных:" << std::endl;
        
        std::cout << "\n2. Запись строковых данных:" << std::endl;
         processors_facade.Write("Review and Cheak");
        std::cout << "\n3. Чтение данных из всех файлов:" << std::endl;
        auto results = processors_facade.ReadAll();
        
        const char* formats[] = {"TXT", "BIN", "JSON", "CSV", "INI"};
        for (size_t i = 0; i < results.size(); ++i) {
            std::cout << "   " << formats[i] << ": " << results[i] << std::endl;
        }
        
    }
    catch (const std::exception& ex) {
        std::cerr << "Ошибка: " << ex.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Неизвестная ошибка!" << std::endl;
    }
    
    return 0;
}