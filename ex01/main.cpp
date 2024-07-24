# include <iostream>
#include "RPN.hpp"

 

int main(int ac, char **av)
{
	std::string s;

    if (ac != 2) {
		std::cout << "Error: You must have ./RPN \"nbrs\"." << std::endl;
		return 1;
	}
	s = av[1];
	if (s.size() < 5)
	{
		std::cout << "Error: You must have minimum one operation" << std::endl;
		return 1;
	}
	RPN calculator;
	calculator.calculate(s);
	return 0;
}