#ifndef BITCOIN_EXCHANGE_HPP
#define BITCOIN_EXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <cctype>
#include <map>
#include <vector>
#include <algorithm>

#define RED "\033[1;31m"
#define RESET "\033[0m"

# define CSV_FILE "data.csv"
# define CSV_HEADER "date,exchange_rate"
# define INPUT_HEADER "date | value"

extern std::map<std::string, double> exchangeRates;

std::map<std::string, double>& getExchangeRates();

bool Error(const std::string& message, int iLine, const std::string& line);
bool btc(const std::string& fileName);
bool parseCsv();
bool loadCsv();
void finalValue(const std::string date, const std::string value, int line);
bool loadInput(const std::string& fileName);
bool isValidDate(const std::string& dateString);
bool isValidValue(const std::string& value, char c, int iLine, const std::string& line);
bool isValidLine(const std::string& line, char c, int iLine);
#endif
