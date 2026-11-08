#include "PmergeMe.hpp"

static bool	valid_inp(const std::string& raw_nums)
{
	if (raw_nums.empty() || raw_nums.find_first_not_of("0123456789 ") != std::string::npos)
		return false;
	return true;
}

static size_t	counter(const std::string& raw_nums)
{
	size_t	num_pos, spc_pos;
	int		quant = 0;

	num_pos = raw_nums.find_first_not_of(" ");
	while (num_pos != std::string::npos)
	{
		quant++;
		spc_pos = raw_nums.find_first_of(" ", num_pos);
		num_pos = raw_nums.find_first_not_of(" ", spc_pos);
	}
	return quant;
}

void	parse(std::list<int>& nums, const std::string& raw_nums)
{
	std::istringstream	aux(raw_nums);
	int					holder;
	size_t				elems;


	if (!valid_inp(raw_nums))
		throw std::runtime_error("Invalid usage.");
	elems = counter(raw_nums) + nums.size();
	while (aux >> holder)
		nums.push_back(holder);
	if (elems != nums.size() || std::find(nums.begin(), nums.end(), 0) != nums.end())
		throw std::runtime_error("Invalid number used.");
	if (nums.empty())
		throw std::runtime_error("No numbers found.");

	std::list<int>	sort_copy(nums);

	sort_copy.sort();
	if (std::adjacent_find(sort_copy.begin(), sort_copy.end()) != sort_copy.end())
		throw std::runtime_error("Invalid use of duplicates.");
}

int main(int argc, char **argv)
{
	PmergeMe			example;
	std::list<int>		nums;

	if (argc < 2)
		return (std::cerr << "Error: invalid input" << std::endl, 1);
	try
	{
		for (int i = 1; i < argc; i++)
			parse(nums, argv[i]);

		example.organize(nums);
	}
	catch (const std::exception& e)
	{
		return (std::cerr << "Error: " << e.what() << std::endl, 1);
	}
}
