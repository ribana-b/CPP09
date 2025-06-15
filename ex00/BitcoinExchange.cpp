/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:05:44 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2025/06/16 01:33:12 by ribana-b         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>	// For std::cout
#include <fstream>	// For std::ifstream
#include <cstddef>	// For std::size_t
#include <string>	// For std::string
#include <sstream>	// For std::stringstream
#include <ctime>	// For std::time_t, std::time, std::strptime, std::localtime
#include <cstring>	// For std::memset
#include <utility>	// For std::pair
#include <cstdlib>	// For std::atof

// Helper macro to turn off OCF messages
#ifdef QUIET
# define OCF_MESSAGE(X)
#else
# define OCF_MESSAGE(X) std::cout << (X) << std::endl
#endif

const std::string BitcoinExchange::m_DefaultDatabasename = "data.csv";

BitcoinExchange::BitcoinExchange(const std::string& databaseName) :
	m_DatabaseName(databaseName),
	m_Database()
{
	OCF_MESSAGE("BitcoinExchange Parameterised constructor called");
}

BitcoinExchange::BitcoinExchange() :
	m_DatabaseName(m_DefaultDatabasename),
	m_Database()
{
	OCF_MESSAGE("BitcoinExchange Default constructor called");
}

BitcoinExchange::~BitcoinExchange()
{
	OCF_MESSAGE("BitcoinExchange Destructor called");
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange&)
{
	OCF_MESSAGE("BitcoinExchange Copy constructor called");
}

BitcoinExchange&	BitcoinExchange::operator=(const BitcoinExchange&)
{
	OCF_MESSAGE("BitcoinExchange Assignment operator called");
	return (*this);
}

char	BitcoinExchange::getSeparator(const std::string& filename) const
{
	char separator = '|';

	std::size_t pos = filename.find_last_of('.');
	if (pos != std::string::npos)
	{
		const std::string extension = filename.substr(pos + 1);
		if (extension == "csv")
		{
			separator = ',';
		}
	}

	return (separator);
}

std::pair<std::string, std::string>
BitcoinExchange::getPairFromLine(const std::string& line, const char separator) const
{
	std::size_t size = 0;
	std::stringstream ss(line);
	std::string item;
	std::string pair[2];

	while (std::getline(ss, item, separator))
	{
		std::size_t start = item.find_first_not_of(" ");
		if (start != std::string::npos)
		{
			item.erase(0, start);
			std::size_t end = item.find_last_not_of(" ");
			item.erase(end + 1);
		}
		if (size < 2)
		{
			pair[size] = item;
		}
		++size;
	}
	if (size > 2)
	{
		throw (InvalidFormatException());
	}

	return (std::make_pair(pair[0], pair[1]));
}

std::time_t	BitcoinExchange::getDate(const std::string& date) const
{
	const std::string format("%Y-%m-%d");
	std::tm tm;

	std::memset(&tm, 0, sizeof(tm));
	if (!strptime(date.c_str(), format.c_str(), &tm))
	{
		throw (InvalidFormatException());
	}

	return (std::mktime(&tm));
}

double	BitcoinExchange::getValue(const std::string& valueString) const
{
	if (valueString.size() == 0 || valueString.size() > 10)
	{
		throw (InvalidNumberException());
	}

	const std::string validChars = "0123456789.";
	bool isPointFound = false;
	for (std::size_t i = 0; i < valueString.size(); ++i)
	{
		if (validChars.find(valueString[i]) == std::string::npos)
		{
			throw (InvalidNumberException());
		}
		if (valueString[i] == '.')
		{
			if (isPointFound)
			{
				throw (InvalidNumberException());
			}
			isPointFound = true;
		}
	}
	double value = std::atof(valueString.c_str());
	return (value);
}

void BitcoinExchange::loadDatabase()
{
	std::ifstream f(m_DatabaseName.c_str());
	if (!f.is_open())
	{
		throw (CouldNotOpenFileException());
	}

	std::string line;
	const char separator = getSeparator(m_DatabaseName);
	std::getline(f, line); // Skip first line
	while (std::getline(f, line))
	{
		std::pair<std::string, std::string> pair = getPairFromLine(line, separator);
		try
		{
			std::time_t date = getDate(pair.first);
			double value = getValue(pair.second);
			m_Database.insert(std::make_pair(date, value));
		}
		catch (const std::exception& e)
		{
			f.close();
			throw;
		}
	}

	if (m_Database.empty())
	{
		throw (std::exception()); // TODO(srvariable): Create EmptyException
	}

	f.close();
}

double	BitcoinExchange::getPercentage(std::time_t date)
{
	if (date < m_Database.begin()->first)
	{
		throw (std::exception()); // TODO(srvariable): Create InvalidDateException
	}

	std::map<std::time_t, double>::iterator it = m_Database.lower_bound(date);
	if (it != m_Database.begin() && date < it->first)
	{
		--it;
	}
	return (m_Database[it->first]);
}

void	BitcoinExchange::exchange(const std::string& filename)
{
	loadDatabase();

	std::ifstream f(filename.c_str());
	if (!f.is_open())
	{
		throw (CouldNotOpenFileException());
	}

	std::string line;
	const char separator = getSeparator(filename);
	std::getline(f, line); // Skip first line
	while (std::getline(f, line))
	{
		std::pair<std::string, std::string> pair = getPairFromLine(line, separator);
		try
		{
			std::time_t date = getDate(pair.first);
			double value = getValue(pair.second);
			if (value < 0 || value > 1000)
			{
				throw (InvalidNumberException());
			}
			double percentage = getPercentage(date);
			std::cout << pair.first << " => " << pair.second << " = " << value * percentage << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}

	f.close();
}

const char*	BitcoinExchange::CouldNotOpenFileException::what() const throw()
{
	return ("Couldn't open the file");
}

const char*	BitcoinExchange::InvalidFormatException::what() const throw()
{
	return ("Invalid format");
}

const char*	BitcoinExchange::InvalidNumberException::what() const throw()
{
	return ("Invalid number");
}
