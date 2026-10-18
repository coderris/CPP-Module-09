/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanton-m <lanton-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 13:12:32 by lanton-m          #+#    #+#             */
/*   Updated: 2026/10/17 17:55:43 by lanton-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>

class BitcoinExchange
{
	private:
		std::map<std::string, float> db;
	public:
		BitcoinExchange();
		BitcoinExchange(std::ifstream& raw_db);
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange	&operator=(const BitcoinExchange& other);
		~BitcoinExchange();

		void	exchange(std::ifstream& raw_input);
};

bool	split(const std::string& line, std::string& date, std::string& value, std::string delim);

#endif
