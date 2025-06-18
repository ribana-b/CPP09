/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:14:17 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2025/06/18 04:20:59 by ribana-b         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

/* @------------------------------------------------------------------------@ */
/* |                            Include Section                             | */
/* @------------------------------------------------------------------------@ */

#include <stack>		// For std::stack
#include <string>		// For std::string
#include <exception>	// For std::exception

/* @------------------------------------------------------------------------@ */
/* |                             Class Section                              | */
/* @------------------------------------------------------------------------@ */

class RPN
{
	public:
		RPN();
		~RPN();
		RPN(const RPN&);
		RPN&	operator=(const RPN&);

		int	eval(const std::string& input);

		class MissingOperatorException : public std::exception
		{
			public:
				const char*	what() const throw();
		};

		class NotEnoughNumbersException : public std::exception
		{
			public:
				const char*	what() const throw();
		};

		class DivisionByZeroException : public std::exception
		{
			public:
				const char*	what() const throw();
		};

		class NumberOutOfBoundsException : public std::exception
		{
			public:
				const char*	what() const throw();
		};

		class InvalidNumberException : public std::exception
		{
			public:
				const char*	what() const throw();
		};

		class InvalidCharacterException : public std::exception
		{
			public:
				const char*	what() const throw();
		};

	private:
		std::stack<int>	m_Stack;

		bool		isOperator(const char token) const;
		long int	handleOperator(const char token);
		void		handleNumber(const std::string& line);
};

#endif
