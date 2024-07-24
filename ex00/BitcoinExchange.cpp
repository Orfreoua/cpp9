#include "BitcoinExchange.hpp"

std::map<std::string, double> exchangeRates;

std::map<std::string, double>& getExchangeRates() {
	return exchangeRates;
}

bool Error(const std::string& message, int iLine, const std::string& line) {
	std::cerr << RED << "Error: " << message << " (line : " << iLine << ") => " <<  line << RESET << std::endl;
	return false;
}

bool btc(const std::string& fileName){
	if (loadCsv() == false)
		return false;
	loadInput(fileName);
	return true;
}
