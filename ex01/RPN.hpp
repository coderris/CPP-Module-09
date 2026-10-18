#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <stdexcept>

class RPN
{
	public:
		RPN();
		RPN(const RPN& other);
		RPN	&operator=(const RPN& other);
		~RPN();

	void	execute(const std::string& expersion);
};

#endif
