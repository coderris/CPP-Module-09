#include "BitcoinExchange.hpp"

int	main(int argc, char** argv)
{

	if (argc != 2)
		return (std::cerr<< "Check your input. Usage: ./btc <file>" << std::endl, 1);
	std::ifstream input(argv[1]), data("data.csv");
	if (!input.is_open() || !data.is_open())
		return (std::cerr << "Couldn't find or open the file. Check your files" << std::endl, 1);
	try
	{
		BitcoinExchange	db(data);
		db.exchange(input);
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
}
