#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(std::ifstream& raw_data)
{
	std::string	line;

	std::getline(raw_data, line);
	while (std::getline(raw_data, line))
	{
		std::string date, value;
		if (line.empty())
			continue;
		if (!split(line, date, value, ","))
			throw std::runtime_error("Not ',' finded " + line);
		std::istringstream aux(value);
		float num;
		if (!(aux >> num))
			throw std::runtime_error("Invalid value: " + value);
		if (!aux.eof())
			throw std::runtime_error("Invalid type of num: " + value);
		std::pair<std::string, float> values(date, num);
		db.insert(values);
	}
}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
	*this = other;
}
BitcoinExchange	&BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
		this->db = other.db;
	return *this;
}
BitcoinExchange::~BitcoinExchange(){}

bool	split(const std::string& line, std::string& date, std::string& value, std::string delim)
{
	if (line.empty())
		return false;
	size_t pos = line.find(delim, 0);
	if (pos == std::string::npos)
		return false;
	date = line.substr(0, pos);
	value = line.substr(pos + delim.size());
	return true;
}

static bool	valid_year(std::string& year)
{
	if (year.size() != 4)
		return false;
	if (year.find_first_not_of("0123456789") != std::string::npos)
		return false;
	return true;
}

static bool valid_month(std::string& month)
{
	std::istringstream	aux(month);
	int					i_month;

	if (month.size() != 2)
		return false;
	if (month.find_first_not_of("0123456789") != std::string::npos)
		return false;
	if (!(aux >> i_month))
		return false;
	if (i_month <= 0 || i_month > 12)
		return false;
	return true;
}

static bool	valid_day(std::string day, std::string month)
{
	std::istringstream	aux(day), aux2(month);
	int					i_day, i_month;

	if (day.size() != 2)
		return false;
	if (day.find_first_not_of("0123456789") != std::string::npos)
		return false;
	if (!(aux >> i_day))
		return false;
	aux2 >> i_month;
	if (i_day < 1 || i_day > 31 || (i_day > 30 && (i_month == 4 || i_month == 6 || i_month == 9 || i_month == 11)) || (i_day > 29 && i_month == 2))
		return false;
	return true;
}

static bool	valid_date(std::string& date)
{
	std::string	year, aux, month, day;

	if (date.empty())
		return false;
	if (!split(date, year, aux, "-"))
		return false;
	if (!split(aux, month, day, "-"))
		return false;
	if (!valid_year(year))
		return false;
	if (!valid_month(month))
		return false;
	if (!valid_day(day, month))
		return false;
	return true;
}

static bool valid_quant(std::istringstream& aux, float& num)
{
	if (!(aux >> num))
		return (std::cout << "Error: invalid number." << std::endl, false);
	if (!aux.eof())
		return (std::cout << "Error: invalid number." << std::endl, false);
	if (num < 0)
		return (std::cout << "Error: not a positive number." << std::endl, false);
	if (num > 1000)
		return (std::cout << "Error: too large a number." << std::endl, false);
	return true;
}

void	BitcoinExchange::exchange(std::ifstream& raw_input)
{
	std::string	line;

	std::getline(raw_input, line);
	while (std::getline(raw_input, line))
	{
		std::string date, quantity;
		if (line.empty())
			continue;
		if (!split(line, date, quantity, " | "))
		{
			std::cout << "Error: bad input => " + line << std::endl;
			continue;
		}
		if (!valid_date(date))
		{
			std::cout << "Error: invalid date => " + date << std::endl;
			continue;
		}
		std::istringstream	aux(quantity);
		float 				num;
		if (!valid_quant(aux, num))
			continue;
		std::map<std::string, float>::iterator it = db.find(date);
		if (it != db.end())
		{
			std::cout << date + " => " + quantity + " = " << num * it->second << std::endl;
			continue;
		}
		it = db.upper_bound(date);
		if (it != db.begin())
		{
			it--;
			std::cout << "No data finded for " + date + " the nearest previous date is: ";
			std::cout << date + " => " + quantity + " = " << num * it->second << std::endl;
			continue;
		}
		std::cout << "No data or previous data finded for " + date << std::endl;
	}
}
