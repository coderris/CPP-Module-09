#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <sstream>
#include <limits>
#include <algorithm>
#include <sys/time.h>

class PmergeMe
{
	public:
		PmergeMe();
		PmergeMe(const PmergeMe& other);
		PmergeMe	&operator=(const PmergeMe& other);
		~PmergeMe();

		void	organize(std::list<int>& nums);
};

#endif
