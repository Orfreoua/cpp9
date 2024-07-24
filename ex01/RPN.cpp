#include "RPN.hpp"
#include <stdlib.h>

RPN::RPN(){}

RPN::~RPN(){}

RPN::RPN(std::stack<double> number) : numbers(number){}

RPN::RPN(const RPN &var)
{
	*this = var;
}

RPN &RPN::operator=(const RPN &var)
{
	this->numbers = var.numbers;
	return (*this);
}

void RPN::calculate(std::string input) {
    for (std::string::iterator it = input.begin(); it != input.end(); ++it) {
        char c = *it;

        if (c == ' ') {
            continue;
        } else if (isdigit(c)) {
            processDigit(c);
        } else if (numbers.size() >= 2) {
            processOperator(c);
        } else {
            std::cout << "Invalid input." << std::endl;
            return;
        }
    }

    printResultOrError();
}

void RPN::processDigit(char c) {
    numbers.push(c - '0');
}

void RPN::processOperator(char c) {
    double b = numbers.top(); numbers.pop();
    double a = numbers.top(); numbers.pop();
    
    switch (c) {
        case '+': numbers.push(a + b); break;
        case '-': numbers.push(a - b); break;
        case '*': numbers.push(a * b); break;
        case '/': numbers.push(a / b); break;
        default:
            std::cout << "Invalid input." << std::endl;
            exit(1);
    }
}

void RPN::printResultOrError() {
    if (numbers.size() == 1) {
        double result = numbers.top();
        numbers.pop();
        std::cout << "Result: " << result << std::endl;
    } else {
        std::cout << "Invalid input." << std::endl;
    }
}