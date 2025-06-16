/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:05:44 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2025/06/17 00:56:01 by ribana-b         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>		// For std::cout
#include <fstream>		// For std::ifstream
#include <cstddef>		// For std::size_t
#include <string>		// For std::string
#include <sstream>		// For std::stringstream
#include <ctime>		// For std::time_t, std::time, std::strptime, std::localtime
#include <cstring>		// For std::memset
#include <utility>		// For std::pair
#include <cstdlib>		// For std::atof
#include <exception>	// For std::exception

// Helper macro to turn off OCF messages
#ifdef QUIET
# define OCF_MESSAGE(X)
#else
# define OCF_MESSAGE(X) std::cout << (X) << std::endl
#endif

const std::string BitcoinExchange::m_DefaultDatabaseName = "data.csv";

BitcoinExchange::BitcoinExchange(const std::string& databaseName) :
	m_DatabaseName(databaseName),
	m_Database(),
	m_IsDatabaseLoaded(false)
{
	OCF_MESSAGE("BitcoinExchange Parameterised constructor called");
}

BitcoinExchange::BitcoinExchange() :
	m_DatabaseName(m_DefaultDatabaseName),
	m_Database(),
	m_IsDatabaseLoaded(false)
{
	OCF_MESSAGE("BitcoinExchange Default constructor called");
}

BitcoinExchange::~BitcoinExchange()
{
	OCF_MESSAGE("BitcoinExchange Destructor called");
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& that) :
	m_Database(that.m_Database),
	m_IsDatabaseLoaded(that.m_IsDatabaseLoaded)
{
	OCF_MESSAGE("BitcoinExchange Copy constructor called");
}

BitcoinExchange&	BitcoinExchange::operator=(const BitcoinExchange& that)
{
	OCF_MESSAGE("BitcoinExchange Assignment operator called");

	if (this != &that)
	{
		m_Database = that.m_Database;
		m_IsDatabaseLoaded = that.m_IsDatabaseLoaded;
	}

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
		throw (InvalidFormatException("date, value", line));
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
		throw (InvalidDateException(format + " (Y: >= 0, m: [1-12], d: [1-31])", date));
	}

	return (std::mktime(&tm));
}

double	BitcoinExchange::getValue(const std::string& value) const
{
	if (value.size() == 0)
	{
		throw (EmptyNumberException());
	}

	const std::string validChars = "0123456789.";
	bool isPointFound = false;
	for (std::size_t i = 0; i < value.size(); ++i)
	{
		if (validChars.find(value[i]) == std::string::npos
			|| (value[i] == '.' && isPointFound))
		{
			throw (InvalidNumberException("[0-1000]", value));
		}
		if (value[i] == '.')
		{
			isPointFound = true;
		}
	}

	return (std::atof(value.c_str()));
}

void BitcoinExchange::loadDatabase()
{
	if (m_IsDatabaseLoaded)
	{
		return;
	}

	std::ifstream f(m_DatabaseName.c_str());
	if (!f.is_open())
	{
		throw (CouldNotOpenFileException(m_DatabaseName));
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
			bool isInserted = m_Database.insert(std::make_pair(date, value)).second;
			if (!isInserted)
			{
				m_Database.clear();
				throw (RepeatedDateException(pair.first));
			}
		}
		catch (const std::exception& e)
		{
			f.close();
			throw;
		}
	}
	if (m_Database.empty())
	{
		throw (EmptyDatabaseException());
	}

	m_IsDatabaseLoaded = true;
	f.close();
}

double	BitcoinExchange::getPercentage(std::time_t date)
{
	if (date < m_Database.begin()->first)
	{
		const std::tm *expected = std::localtime(&m_Database.begin()->first);
		const std::tm *got = std::localtime(&date);
		throw (LowDateException(expected, got));
	}
	if (date > (m_Database.rbegin())->first)
	{
		return (m_Database[m_Database.rbegin()->first]);
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
		throw (CouldNotOpenFileException(filename));
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
				throw (InvalidNumberException("[0-1000]", pair.second));
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

BitcoinExchange::CouldNotOpenFileException::CouldNotOpenFileException(const std::string& filename)
{
	std::stringstream ss;
	ss << "Couldn't open file `" << filename << "`";
	m_Message = ss.str();
}

BitcoinExchange::CouldNotOpenFileException::~CouldNotOpenFileException() throw() {}

const char*	BitcoinExchange::CouldNotOpenFileException::what() const throw()
{
	return (m_Message.c_str());
}

BitcoinExchange::InvalidFormatException::InvalidFormatException(const std::string& expected, const std::string& got)
{
	std::stringstream ss;
	ss << "Invalid format. Expected: " << expected << ". Got: " << got;
	m_Message = ss.str();
}

BitcoinExchange::InvalidFormatException::~InvalidFormatException() throw() {}

const char*	BitcoinExchange::InvalidFormatException::what() const throw()
{
	return (m_Message.c_str());
}

const char*	BitcoinExchange::EmptyDatabaseException::what() const throw()
{
	return ("Empty database");
}

BitcoinExchange::InvalidDateException::InvalidDateException(const std::string& expected, const std::string& got)
{
	std::stringstream ss;
	ss << "Invalid date. Expected: " << expected << ". Got: " << got;
	m_Message = ss.str();
}

BitcoinExchange::InvalidDateException::~InvalidDateException() throw() {}

const char*	BitcoinExchange::InvalidDateException::what() const throw()
{
	return (m_Message.c_str());
}

BitcoinExchange::RepeatedDateException::RepeatedDateException(const std::string& date)
{
	std::stringstream ss;
	ss << "Repeated date: " << date;
	m_Message = ss.str();
}

BitcoinExchange::RepeatedDateException::~RepeatedDateException() throw() {}

const char*	BitcoinExchange::RepeatedDateException::what() const throw()
{
	return (m_Message.c_str());
}

BitcoinExchange::LowDateException::LowDateException(const std::tm* expected, const std::tm* got)
{
	std::stringstream ss;
	ss << "Expected date greater or equal than: ";
	ss << 1900 + expected->tm_year << "-" << 1 + expected->tm_mon << "-" << expected->tm_mday;
	ss << ". Got: ";
	ss << 1900 + got->tm_year << "-" << 1 + got->tm_mon << "-" << got->tm_mday;
	m_Message = ss.str();
}

BitcoinExchange::LowDateException::~LowDateException() throw() {}

const char*	BitcoinExchange::LowDateException::what() const throw()
{
	return (m_Message.c_str());
}

BitcoinExchange::InvalidNumberException::InvalidNumberException(const std::string& expected, const std::string& got)
{
	std::stringstream ss;
	ss << "Invalid number. Expected: " << expected << ". Got: " << got;
	m_Message = ss.str();
}

BitcoinExchange::InvalidNumberException::~InvalidNumberException() throw() {}

const char*	BitcoinExchange::InvalidNumberException::what() const throw()
{
	return (m_Message.c_str());
}

const char*	BitcoinExchange::EmptyNumberException::what() const throw()
{
	return ("Empty number");
}
