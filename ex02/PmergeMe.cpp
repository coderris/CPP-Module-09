#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){}
PmergeMe::PmergeMe(const PmergeMe& other){(void)other;}
PmergeMe	&PmergeMe::operator=(const PmergeMe& other){(void)other; return (*this);}
PmergeMe::~PmergeMe(){};

static int			jacobseries(int prev1, int prev2)
{
	return prev1 + 2*prev2;
}

static std::vector<int>	jacobsthal(int size)
{
	std::vector<int>	result;
	int					prev = 1, curr = 3, tmp, actSize = size;

	while (actSize > 0)
	{
		for (int i = curr; i > prev; i--)
		{
			if (i > size + 1)
				continue;
			result.push_back(i - 2);
			actSize--;
		}
		tmp = curr;
		curr = jacobseries(tmp, prev);
		prev = tmp;
	}
	return result;
}

static void	binarySearch(std::vector<int>::iterator hi, std::vector<int>& main, const std::vector<int>& nums, int k_b, int s)
{
	std::vector<int>::iterator	lo = main.begin(), mid;

	while (lo < hi)
	{
		mid = lo + (hi - lo)/ 2;
		if (nums[s*(k_b + 1) - 1] < nums[s*(*mid + 1) - 1])
			hi = mid;
		else
			lo = mid + 1;
	}
	main.insert(lo, k_b);
}

static void	fordjohnson(std::vector<int>& nums, int s)
{
	std::vector<int>	main, pend, jacobOrd, result;
	int 				p_size, n, start;

	n = nums.size();
	p_size = s * 2;
	if (n/p_size < 1)
		return ;
	for (int p = 0; p < n / p_size; p++)
	{
		start = p_size * p;
		if (nums[start + s - 1] > nums[p_size * (p + 1) - 1])
			std::swap_ranges(nums.begin() + start, nums.begin() + start + s, nums.begin() + start + p_size/2);
	}
	fordjohnson(nums, s*2);
	for (int i = 0; i < n/p_size; i++)
	{
		if (i == 0)
			main.push_back(2 * i);
		main.push_back(2 * i + 1);
		if ((n / s) - 2*(i+1) > 0)
			pend.push_back(2 * (i + 1));
	}
	jacobOrd = jacobsthal(pend.size());
	for (size_t j = 0; j < jacobOrd.size(); j++)
		binarySearch(std::find(main.begin(), main.end(), pend[jacobOrd[j]] + 1), main, nums, pend[jacobOrd[j]], s);
	result.reserve(n);
	for (size_t k = 0; k < main.size(); k++)
		result.insert(result.end(), nums.begin() + s * main[k], nums.begin() + s * (main[k] + 1));
	result.insert(result.end(), nums.begin() + s *(n / s), nums.end());
	nums.swap(result);
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
