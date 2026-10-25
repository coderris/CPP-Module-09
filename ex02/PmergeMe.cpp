#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){}
PmergeMe::PmergeMe(const PmergeMe& other){(void)other;}
PmergeMe	&PmergeMe::operator=(const PmergeMe& other){(void)other; return (*this);}
PmergeMe::~PmergeMe(){};

static void	fordjohnson(std::vector<int>& nums, int s)
{
	int p_size, n, start;

	n = nums.size();
	p_size = s * 2;
	if (n == 1 || n/p_size < 1)
		return ;
	for (int p = 0; p < n / p_size; p++)
	{
		start = p_size * p;
		if (nums[start + s - 1] > nums[p_size * (p + 1) - 1])
			std::swap_ranges(nums.begin() + start, nums.begin() + start + s, nums.begin() + start + p_size/2);
	}
	fordjohnson(nums, s*2);
	
}

void	PmergeMe::organizevct(std::vector<int>& nums)
{
	fordjohnson(nums, 1);
	for (size_t i = 0; i < nums.size(); i++)
	{
		std::cout << nums[i] << " ";
	}
	std::cout << std::endl;

}
