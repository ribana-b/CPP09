/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:05:44 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2025/06/30 13:35:22 by ribana-b         ###   ########.com      */
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
				CouldNotOpenFileException(const std::string& filename);
				virtual ~CouldNotOpenFileException() throw();
				virtual const char*	what() const throw();

			private:
				std::string	m_Message;
		};

		class InvalidFormatException : public std::exception
		{
			public:
				InvalidFormatException(const std::string& expected, const std::string& got);
				virtual ~InvalidFormatException() throw();
				virtual const char*	what() const throw();

			private:
				std::string	m_Message;
		};

		class EmptyDatabaseException : public std::exception
		{
			public:
				virtual const char*	what() const throw();
		};

		class InvalidDateException : public std::exception
		{
			public:
				InvalidDateException(const std::string& expected, const std::string& got);
				virtual ~InvalidDateException() throw();
				virtual const char*	what() const throw();

			private:
				std::string	m_Message;
		};

		class RepeatedDateException : public std::exception
		{
			public:
				RepeatedDateException(const std::string& date);
				virtual ~RepeatedDateException() throw();
				virtual const char*	what() const throw();

			private:
				std::string	m_Message;
		};

		class LowDateException : public std::exception
		{
			public:
				LowDateException(const std::tm* expected, const std::tm* got);
				virtual ~LowDateException() throw();
				virtual const char*	what() const throw();

			private:
				std::string m_Message;
		};

		class InvalidNumberException : public std::exception
		{
			public:
				InvalidNumberException(const std::string& expected, const std::string& got);
				virtual ~InvalidNumberException() throw();
				virtual const char*	what() const throw();

			private:
				std::string m_Message;
		};

		class EmptyNumberException : public std::exception
		{
			public:
				virtual const char*	what() const throw();
		};

	private:
		const static std::string		m_DefaultDatabaseName;
		const std::string				m_DatabaseName;
		std::map<std::time_t, double>	m_Database;
		bool							m_IsDatabaseLoaded;

		char								getSeparator(const std::string& filename) const;
		std::pair<std::string, std::string>	getPairFromLine(const std::string& line, const char separator) const;
		std::time_t							getDate(const std::string& date) const;
		double								getValue(const std::string& value) const;
		void								loadDatabase();
		double								getPercentage(std::time_t date);
};

#endif
