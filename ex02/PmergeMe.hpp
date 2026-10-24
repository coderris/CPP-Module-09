#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <algorithm>

class PmergeMe
{
	public:
		PmergeMe();
		PmergeMe(const PmergeMe& other);
		PmergeMe	&operator=(const PmergeMe& other);
		~PmergeMe();

		void	organizevct(std::vector<int>& nums);
};

#endif
