#include "RPN.hpp"

int main(int argc, char** argv)
{
	RPN calculator;

	if (argc != 2)
		return (std::cerr << "Error: Usage ./RPN <mathematical expresion>" << std::endl, 1);
	try
	{
	calculator.execute(argv[1]);
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
}
