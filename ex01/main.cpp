/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:14:04 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2025/06/18 04:30:53 by ribana-b         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>	// For std::cout
#include <cstddef>	// For std::size_t

// Helper macro to pretty-print caught exceptions
#define PP_EXCEPTION(exception) do{\
	std::cerr << "\033[31m" << (__FILE__) << ":" << (__LINE__) << "\033[0m"\
	<< ": Exception caught. Reason:\033[0m " << (exception).what() << std::endl;\
} while(0)

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " NUMBER [SYMBOL NUMBER]..." << std::endl;
		return (1);
	}

	std::string input;
	for (int i = 1; i < argc; ++i)
	{
		input += argv[i];
		input += " ";
	}

	RPN rpn;

	try
	{
		std::cout << "Result: " << rpn.eval(input) << std::endl;
	}
	catch (const std::exception& e)
	{
		PP_EXCEPTION(e);
	}

	std::string tests[] = {
		"",
		"1",
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
	std::size_t size = sizeof(tests) / sizeof(*tests);
	for (std::size_t i = 0; i < size; ++i)
	{
		try
		{
			std::cout << "-----------------" << std::endl;
			std::cout << "Testing: " << tests[i] << std::endl;
			std::cout << "Result: " << rpn.eval(tests[i]) << std::endl;
		}
		catch (const std::exception& e)
		{
			PP_EXCEPTION(e);
		}
	}

	return (0);
}
