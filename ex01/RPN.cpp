#include "RPN.hpp"

RPN::RPN(){}

RPN::RPN(const RPN& other){static_cast<void>(other);}

RPN	&RPN::operator=(const RPN& other){static_cast<void>(other); return *this;}

RPN::~RPN(){}

void	RPN::execute(const std::string& raw_expr)
{
	std::stack<int>	nums;
	std::string		token;
	int				value1, value2;

	if (raw_expr.empty())
		throw std::runtime_error("Empty input.");
	if (raw_expr.find_first_not_of("0123456789+-*/ ") != std::string::npos)
		throw std::runtime_error("Invalid character used.");
	if (!std::isdigit(raw_expr[0]))
		throw std::runtime_error("Invalid start of expresion");
	std::istringstream aux(raw_expr);
	while (aux >> token)
	{
		if (token.size() != 1)
			throw std::runtime_error("Invalid expresion: " + token);
		if (std::isdigit(token[0]))
		{
			nums.push(token[0] - '0');
			continue;
		}
		if (nums.size() < 2)
			throw std::runtime_error("Invalid operator position");
		value1 = nums.top();
		nums.pop();
		value2 = nums.top();
		nums.pop();
		switch (token[0])
		{
			case '+':
				nums.push(value2 + value1);
				break;
			case '-':
				nums.push(value2 - value1);
				break;
			case '*':
				nums.push(value2 * value1);
				break;
			case '/':
				nums.push(value2 / value1);
				break;
		}
	}
	std::cout << nums.top() << std::endl;
}
