#include "BitcoinExchange.hpp"

int	main(int argc, char **argv) {
	if (argc != 2) {
		std::cerr << "Error: You must have ./BitcoinExchange [fileName]." << std::endl;
		return 1;
	}
	if (btc(argv[1]) == false)
		return 1;
	return 0;
}