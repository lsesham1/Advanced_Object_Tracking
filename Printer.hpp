#include <string>
#include <fstream>
#include <iostream>
#include <cmath>  // For handling NaN with std::isnan()

class Printer {
public:
    // Methods for writing to a file: use const references for string parameters to avoid copying.
    void writeToFile(const std::string &fileName, double data);
    void writeToFile(const std::string &fileName, const std::string &data);
    
    // Method to clear the contents of a file.
    void clearFile(const std::string &fileName);
};

// Writes numerical data to a CSV file.
void Printer::writeToFile(const std::string &fileName, double data) {
    std::ofstream file(fileName, std::ios_base::app);
    if (!file) {
        std::cerr << "Unable to open csv file\n";
        return;
    }
    // Check for NaN and adjust the value to be written.
    if (std::isnan(data)) {
        data = 0;
    }
    file << data << ";\n";  // Use '\n' for better performance instead of std::endl
}

// Writes string data to a CSV file.
void Printer::writeToFile(const std::string &fileName, const std::string &data) {
    std::ofstream file(fileName, std::ios_base::app);
    if (!file) {
        std::cerr << "Unable to open csv file\n";
        return;
    }
    file << data << ";\n";  // Consistently use ';', assume that is the desired delimiter
}

// Clears the contents of a file.
void Printer::clearFile(const std::string &fileName) {
    std::ofstream file(fileName, std::ios_base::trunc); // Open in truncate mode to clear content
    if (!file) {
        std::cerr << "Unable to open and clear csv file\n";
    }
}
