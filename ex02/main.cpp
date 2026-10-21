#include "PmergeMe.hpp"

static bool	valid_inp(std::string raw_nums)
{
	if (raw_nums.empty() || raw_nums.find_first_not_of("0123456789 "))
		return false;
	return true;
}
static std::vector<int>	parse(std::string raw_nums)
{
	
}

int main(int argc, char **argv)
{
	if (argc != 2 || !valid_inp(argv[1]))
		std::cerr << "Error: invalid input" << std::endl;
	std::vector<int> nums = parse(argv[1]);
}
