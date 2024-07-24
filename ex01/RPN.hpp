#include <iostream>
#include <stack>

class RPN
{
public:
	RPN();
	RPN(std::stack<double> number);
	~RPN();
	RPN &operator=(const RPN &var);
	void calculate(std::string input);
private:
	RPN(const RPN &var);
	std::stack<double> numbers;
    void processDigit(char c);
    void processOperator(char c);
    void printResultOrError();
};