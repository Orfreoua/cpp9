#include "BitcoinExchange.hpp"

bool loadCsv() {
	std::string line;
	std::string date;
	std::string value;

	std::ifstream file(CSV_FILE);
	if (!file.is_open()) {
		std::cout << RED << "Error: (CSV) cannot accsess." << RESET << std::endl;
        return false;
	}
	std::getline(file, line);
	if (line != CSV_HEADER) {
		file.close();
		return (Error("(CSV) Bad header", 1, line));
	}
	for (int iLine = 2; std::getline(file, line); iLine++) {
		if (isValidLine(line, ',', iLine) == false) {
			file.close();
			return (Error("(CSV) Bad line ", iLine, line));
		}
		std::istringstream iss(line);
		std::getline(iss, date, ',') && std::getline(iss, value, ',');
		exchangeRates[date] = std::strtod(value.c_str(), NULL);
	}
	file.close();
	return true;
}