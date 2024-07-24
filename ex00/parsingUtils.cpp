#include "BitcoinExchange.hpp"

bool isValidDate(const std::string& dateString) {
	if (dateString.size() != 10) {
		return false;
	}
	int y, m, d;
	if (sscanf(dateString.c_str(), "%4d-%2d-%2d", &y, &m, &d) != 3) {
		return false;
	}
	if (m < 1 || m > 12 || d < 1 || d > 31) {
		return false;
	}
	if ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30) {
		return false;
	}
	if (m == 2) {
		if (((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0)) {
			if (d > 29) {
				return false;
			}
		} else {
			if (d > 28) {
				return false;
			}
		}
	}
	return true;
}

bool isValidValue(const std::string& value, char c, int iLine, const std::string& line) {
	if (std::atof(value.c_str()) < 0)
		return (Error("not a positive number", iLine, line));
	if (value.empty() || value[0] == '.' || value.find('.') != value.rfind('.'))
		return false;
	for (size_t i = 0; i < value.length(); ++i) {
		if (!isdigit(value[i]) && value[i] != '.')
			return false; }
	if (c == '|')
	{
		if (std::atof(value.c_str()) > 1000)
			return (Error("too large a number", iLine, line));
	}
	if (!isdigit(value[0]) && ! (value[0] != '.') && (value[0] != '-'))
		return false;
	return true;
}

bool isValidLine(const std::string& line, char c, int iLine) {

	std::string date, value;
	size_t pos = line.find(c);

	if (pos == std::string::npos)
		return false;
	date = line.substr(0, pos);
	value = line.substr(pos + 1);
	if (!isValidDate(date))
		return (Error("Invalid line", iLine, line));
	if (!isValidValue(value, c, iLine, line)) {
		return false;
	}
	if (c == '|')
		finalValue(date, value, iLine);
	return true;
}
