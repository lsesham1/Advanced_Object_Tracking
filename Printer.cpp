#include "Printer.hpp"
#include <iostream>
#include <fstream>
#include <cmath>  // Use <cmath> instead of <math.h> for C++

class Printer {
public:
    void writeToFile(const std::string &fileName, double data);
    void writeToFile(const std::string &fileName, const std::string &data);
    void clearFile(const std::string &fileName);
};

// Method to write numerical data to a csv file.
void Printer::writeToFile(const std::string &fileName, double data) {
    std::ofstream file(fileName, std::ios_base::app);
    if (!file) {
        std::cerr << "Unable to open csv file\n";
        return;
    }

    if (std::isnan(data)) {
        data = 0;
    }

    file << data << ";\n";  // Use '\n' for a newline for better performance
}

// Method to write string data to a csv file.
void Printer::writeToFile(const std::string &fileName, const std::string &data) {
    std::ofstream file(fileName, std::ios_base::app);
    if (!file) {
        std::cerr << "Unable to open csv file\n";
        return;
    }

    file << data << ";\n";  // Use '\n' for a newline for better performance
}

// Method to clear the contents of a file.
void Printer::clearFile(const std::string &fileName) {
    std::ofstream file(fileName, std::ios_base::trunc);  // Use std::ios_base::trunc to clear the contents
    if (!file) {
        std::cerr << "Unable to open and clear csv file\n";
    }
}
