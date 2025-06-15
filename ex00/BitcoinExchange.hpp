/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:05:44 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2025/06/16 00:50:26 by ribana-b         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

/* @------------------------------------------------------------------------@ */
/* |                            Include Section                             | */
/* @------------------------------------------------------------------------@ */

#include <string>		// For std::string
#include <exception>	// For std::exception
#include <ctime>		// For std::time_t
#include <map>			// For std::map

/* @------------------------------------------------------------------------@ */
/* |                             Class Section                              | */
/* @------------------------------------------------------------------------@ */

class BitcoinExchange
{
	public:
		BitcoinExchange(const std::string& databaseName);
		BitcoinExchange();
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange&);
		BitcoinExchange&	operator=(const BitcoinExchange&);

		void	exchange(const std::string& filename);

		class CouldNotOpenFileException : public std::exception
		{
			public:
				const char*	what() const throw();
		};

		class InvalidFormatException : public std::exception
		{
			public:
				const char*	what() const throw();
		};

		class InvalidNumberException : public std::exception
		{
			public:
				const char*	what() const throw();
		};

	private:
		const static std::string m_DefaultDatabasename;

		const std::string m_DatabaseName;
		std::map<std::time_t, double> m_Database;

		char								getSeparator(const std::string& filename) const;
		std::pair<std::string, std::string>	getPairFromLine(const std::string& line, const char separator) const;
		std::time_t							getDate(const std::string& date) const;
		double								getValue(const std::string& value) const;
		void								loadDatabase();
		double								getPercentage(std::time_t date);
};

#endif
