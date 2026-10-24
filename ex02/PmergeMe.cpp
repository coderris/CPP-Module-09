#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){}
PmergeMe::PmergeMe(const PmergeMe& other){(void)other;}
PmergeMe	&PmergeMe::operator=(const PmergeMe& other){(void)other; return (*this);}
PmergeMe::~PmergeMe(){};

static void	groupsort(std::vector<int>& nums, int s)
{

}

void	PmergeMe::organizevct(std::vector<int>& nums)
{
	int	s, k, p, n;

	s = 1;
	n = const_cast<int>(nums.size());
	p = s * 2;
	k = n / s - 1;
	for (int j = 0; j < n/p; j++)
	{
		 
	}
	groupsort(nums, 2*s);
}
