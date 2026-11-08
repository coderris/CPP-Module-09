#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){}
PmergeMe::PmergeMe(const PmergeMe& other){(void)other;}
PmergeMe	&PmergeMe::operator=(const PmergeMe& other){(void)other; return (*this);}
PmergeMe::~PmergeMe(){};

static int			jacobseries(int prev1, int prev2)
{
	return prev1 + 2*prev2;
}

static std::vector<int>	vctjacobsthal(int size)
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

static std::deque<int>	deqjacobsthal(int size)
{
	std::deque<int>		result;
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

static void	vctbinarySearch(std::vector<int>::iterator hi, std::vector<int>& main, const std::vector<int>& nums, int k_b, int s)
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

static void	deqbinarySearch(std::deque<int>::iterator hi, std::deque<int>& main, const std::deque<int>& nums, int k_b, int s)
{
	std::deque<int>::iterator	lo = main.begin(), mid;

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

static void	vctfordjohnson(std::vector<int>& nums, int s)
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
	vctfordjohnson(nums, s*2);
	for (int i = 0; i < n/p_size; i++)
	{
		if (i == 0)
			main.push_back(2 * i);
		main.push_back(2 * i + 1);
		if ((n / s) - 2*(i+1) > 0)
			pend.push_back(2 * (i + 1));
	}
	jacobOrd = vctjacobsthal(pend.size());
	for (size_t j = 0; j < jacobOrd.size(); j++)
		vctbinarySearch(std::find(main.begin(), main.end(), pend[jacobOrd[j]] + 1), main, nums, pend[jacobOrd[j]], s);
	result.reserve(n);
	for (size_t k = 0; k < main.size(); k++)
		result.insert(result.end(), nums.begin() + s * main[k], nums.begin() + s * (main[k] + 1));
	result.insert(result.end(), nums.begin() + s *(n / s), nums.end());
	nums.swap(result);
}

static void	deqfordjohnson(std::deque<int>& nums, int s)
{
	std::deque<int>		main, pend, jacobOrd, result;
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
	deqfordjohnson(nums, s*2);
	for (int i = 0; i < n/p_size; i++)
	{
		if (i == 0)
			main.push_back(2 * i);
		main.push_back(2 * i + 1);
		if ((n / s) - 2*(i+1) > 0)
			pend.push_back(2 * (i + 1));
	}
	jacobOrd = deqjacobsthal(pend.size());
	for (size_t j = 0; j < jacobOrd.size(); j++)
		deqbinarySearch(std::find(main.begin(), main.end(), pend[jacobOrd[j]] + 1), main, nums, pend[jacobOrd[j]], s);
	for (size_t k = 0; k < main.size(); k++)
		result.insert(result.end(), nums.begin() + s * main[k], nums.begin() + s * (main[k] + 1));
	result.insert(result.end(), nums.begin() + s *(n / s), nums.end());
	nums.swap(result);
}

void	PmergeMe::organize(std::list<int>& nums)
{
	struct timeval	start, end;
	double			vcttime, deqtime;

	gettimeofday(&start, NULL);
	std::vector<int>	vctnums(nums.begin(), nums.end());
	vctfordjohnson(vctnums, 1);
	gettimeofday(&end, NULL);
	vcttime = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);

	gettimeofday(&start, NULL);
	std::deque<int>	deqnums(nums.begin(), nums.end());
	deqfordjohnson(deqnums, 1);
	gettimeofday(&end, NULL);
	deqtime = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);

	std::cout << "Before:";
	for (std::list<int>::iterator it = nums.begin(); it != nums.end(); it++)
		std::cout << " " << *it;
	std::cout << std::endl;
	std::cout << "After:";
	for (size_t i = 0; i < vctnums.size(); i++)
		std::cout << " " << vctnums[i];
	std::cout << std::endl;
	std::cout << "Time to process a range of " << vctnums.size() << " elements with std::vector : " << vcttime << " us";
	std::cout << std::endl;
	std::cout << "Time to process a range of " << deqnums.size() << " elements with std::deque : " << deqtime << " us";
	std::cout << std::endl;
}
