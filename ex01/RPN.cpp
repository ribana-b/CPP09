/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:13:58 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2025/06/18 04:21:19 by ribana-b         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>	// For std::cout
#include <stack>	// For std::stack
#include <string>	// For std::string
#include <cstddef>	// For std::size_t
#include <sstream>	// For std::stringstream

// Helper macro to turn off OCF messages
#ifdef QUIET
# define OCF_MESSAGE(X)
#else
# define OCF_MESSAGE(X) std::cout << (X) << std::endl
#endif

RPN::RPN() :
	m_Stack()
{
	OCF_MESSAGE("RPN Default constructor called");
}

RPN::~RPN()
{
	OCF_MESSAGE("RPN Destructor called");
}

RPN::RPN(const RPN& that) :
	m_Stack(that.m_Stack)
{
	OCF_MESSAGE("RPN Copy constructor called");
}

RPN&	RPN::operator=(const RPN& that)
{
	OCF_MESSAGE("RPN Assignment operator called");

	if (this != &that)
	{
		m_Stack = that.m_Stack;
	}

	return (*this);
}

bool	RPN::isOperator(const char token) const
{
	return (token == '+' || token == '-' || token == '*' || token == '/');
}

long int	RPN::handleOperator(const char token)
{
	if (m_Stack.size() < 2)
	{
		throw (NotEnoughNumbersException());
	}

	long int n2 = m_Stack.top();
	m_Stack.pop();
	long int n1 = m_Stack.top();
	m_Stack.pop();

	long int result = 0;
	switch (token)
	{
		case '+':
			result = n1 + n2;
			break;
		case '-':
			result = n1 - n2;
			break;
		case '*':
			result = n1 * n2;
			break;
		case '/':
			if (n2 == 0)
			{
				throw (DivisionByZeroException());
			}
			result = n1 / n2;
			break;
	}

	if (result < -2147483648 || result > 2147483647)
	{
		throw (NumberOutOfBoundsException());
	}

	return (result);
}

void	RPN::handleNumber(const std::string& line)
{
	if (line.size() == 1 || isOperator(line[1]))
	{
		m_Stack.push(line[0] - '0');
	}
	else
	{
		throw (InvalidNumberException());
	}
}

int	RPN::eval(const std::string& input)
{
	// Cleanup stack
	while (!m_Stack.empty())
	{
		m_Stack.pop();
	}

	const std::string validChars = "0123456789+-*/";
	std::stringstream ss;

	ss << input;
	while (!ss.eof())
	{
		std::string line;
		ss >> line;
		std::size_t size = line.size();
		for (std::size_t i = 0; i < size; ++i)
		{
			if (validChars.find(line[i]) == std::string::npos)
			{
				throw (InvalidCharacterException());
			}
			if (isOperator(line[i]))
			{
				m_Stack.push(handleOperator(line[i]));
			}
			else
			{
				handleNumber(&line[i]);
			}
		}
	}

	if (m_Stack.size() != 1)
	{
		throw (MissingOperatorException());
	}

	return (m_Stack.top());
}

const char*	RPN::MissingOperatorException::what() const throw()
{
	return ("Missing operator");
}

const char*	RPN::NotEnoughNumbersException::what() const throw()
{
	return ("Not enough numbers");
}

const char*	RPN::DivisionByZeroException::what() const throw()
{
	return ("Division by zero");
}

const char*	RPN::NumberOutOfBoundsException::what() const throw()
{
	return ("Number out of bounds");
}

const char*	RPN::InvalidNumberException::what() const throw()
{
	return ("Invalid number");
}

const char*	RPN::InvalidCharacterException::what() const throw()
{
	return ("Invalid character");
}
