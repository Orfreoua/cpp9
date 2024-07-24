#include "BitcoinExchange.hpp"

void finalValue(const std::string date, const std::string value, int line){
	std::cout <<  date << " => " << value << " = ";
    std::map<std::string, double>& rates = getExchangeRates();
    std::map<std::string, double>::iterator it = rates.find(date);

    if (it != rates.end())
        std::cout << rates[date] * std::strtod(value.c_str(), NULL) << std::endl;
    else {
        it = rates.lower_bound(date);
        if (it != rates.begin()){
            --it;
            std::cout << it->second * std::strtod(value.c_str(), NULL) << std::endl;
        } else
            std::cout << "Error: invalid date at line : " << line << std::endl;
    }
}

bool loadInput(const std::string& fileName) {
    std::string line;

    std::ifstream file(fileName.c_str());
    if (!file.is_open()) {
        std::cerr << RED << "Error: (INPUT) cannot accsess." << RESET << std::endl;
        return false;
    }
    std::getline(file, line);
    if (line != INPUT_HEADER)
        std::cerr << RED << "Error: (INPUT) Bad header." << RESET << std::endl;
    for (int iLine = 2; std::getline(file, line); iLine++){
        line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
        isValidLine(line, '|', iLine);
    }
    file.close();
    return true;
}
