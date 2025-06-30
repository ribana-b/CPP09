/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:14:04 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2025/06/30 13:41:56 by ribana-b         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>		// For std::cout
#include <cstddef>		// For std::size_t
#include <exception>	// For std::exception

// Helper macro to pretty-print tests
#define PP_TEST(testIndex) do{\
	std::string testName((__func__));\
	std::cout << "\033[38;2;255;128;255m- Test " << (testIndex)\
	<< " (" << testName.substr(4) << "):\033[0m" << std::endl;\
} while(0)

// Helper macro to pretty-print caught exceptions
#define PP_EXCEPTION(exception) do{\
	std::cerr << "\033[31m" << (__FILE__) << ":" << (__LINE__) << "\033[0m"\
	<< ": Exception caught. Reason:\033[0m " << (exception).what() << std::endl;\
} while(0)

void	testNoNumberWithoutOperator(const std::size_t testIndex)
{
	PP_TEST(testIndex);

	const std::string input;

	try
	{
		RPN rpn;
		rpn.eval(input);
	}
	catch (const std::exception& e)
	{
		PP_EXCEPTION(e);
	}
}

void	testNoNumberWithOperator(const std::size_t testIndex)
{
	PP_TEST(testIndex);

	const std::string input("-");

	try
	{
		RPN rpn;
		rpn.eval(input);
	}
	catch (const std::exception& e)
	{
		PP_EXCEPTION(e);
	}
}

void	testOneNumberWithoutOperator(const std::size_t testIndex)
{
	PP_TEST(testIndex);

	const std::string input("1");

	try
	{
		RPN rpn;
		rpn.eval(input);
	}
	catch (const std::exception& e)
	{
		PP_EXCEPTION(e);
	}
}

void	testOneNumberWithOperator(const std::size_t testIndex)
{
	PP_TEST(testIndex);

	const std::string input("1 +");

	try
	{
		RPN rpn;
		rpn.eval(input);
	}
	catch (const std::exception& e)
	{
		PP_EXCEPTION(e);
	}
}

void	testTwoNumbersWithoutOperator(const std::size_t testIndex)
{
	PP_TEST(testIndex);

	const std::string input("1 2");

	try
	{
		RPN rpn;
		rpn.eval(input);
	}
	catch (const std::exception& e)
	{
		PP_EXCEPTION(e);
	}
}

void	testTwoNumbersWithOperator(const std::size_t testIndex)
{
	PP_TEST(testIndex);

	const std::string input("1 2 *");

	try
	{
		RPN rpn;
		rpn.eval(input);
	}
	catch (const std::exception& e)
	{
		PP_EXCEPTION(e);
	}
}

void	testDivisionByZero(const std::size_t testIndex)
{
	PP_TEST(testIndex);

	const std::string input("5 0 /");

	try
	{
		RPN rpn;
		rpn.eval(input);
	}
	catch (const std::exception& e)
	{
		PP_EXCEPTION(e);
	}
}

void	testMultipleCombinations(const std::size_t testIndex)
{
	PP_TEST(testIndex);

	const std::string tests[] = {
		"",
		"1",
		"-",
		"1 2",
		"1 2 -",
		"1 2-",
		"1 2 3",
		"1 2 3 + +",
		"1 2 3+ +",
		"1 2 3++",
		"1 2 3 + + +",
		"1 2+3+",
		"12+3+",
		"1a2+3+",
		"1 2 3+",
	};
	const std::size_t size = sizeof(tests) / sizeof(*tests);
	RPN rpn;
	for (std::size_t i = 0; i < size; ++i)
	{
		try
		{
			std::cout << "-----------------" << std::endl;
			std::cout << "Input: " << tests[i] << std::endl;
			std::cout << "Result: " << rpn.eval(tests[i]) << std::endl;
		}
		catch (const std::exception& e)
		{
			PP_EXCEPTION(e);
		}
	}
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " NUMBER [SYMBOL NUMBER]..." << std::endl;
		return (1);
	}

	std::size_t testIndex = 0;
	testNoNumberWithoutOperator(testIndex++);
	testNoNumberWithOperator(testIndex++);
	testOneNumberWithoutOperator(testIndex++);
	testOneNumberWithOperator(testIndex++);
	testTwoNumbersWithoutOperator(testIndex++);
	testTwoNumbersWithOperator(testIndex++);
	testDivisionByZero(testIndex++);
	testMultipleCombinations(testIndex++);

	std::string input;
	for (int i = 1; i < argc; ++i)
	{
		input += argv[i];
		input += " ";
	}

	try
	{
		RPN rpn;
		std::cout << "-----------------" << std::endl;
		std::cout << "Input: " << input << std::endl;
		std::cout << "Result: " << rpn.eval(input) << std::endl;
	}
	catch (const std::exception& e)
	{
		PP_EXCEPTION(e);
	}

	return (0);
}
