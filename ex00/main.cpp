/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 10:53:00 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2025/06/15 23:55:02 by ribana-b         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>	// For std::cout

// Helper macro to pretty-print caught exceptions
#define PP_EXCEPTION(exception) do{\
	std::cerr << "\033[31m" << (__FILE__) << ":" << (__LINE__) << "\033[0m"\
	<< ": Exception caught. Reason:\033[0m " << (exception).what() << std::endl;\
} while(0)

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		const std::string programName = argv[0];
		std::cerr << "Usage: " << programName << " FILE [database...]" << std::endl;
		return (1);
	}

	if (argc == 2)
	{
		try
		{
			BitcoinExchange btc;
			const std::string filename = argv[1];
			std::cout << "Exchange for \033[1;33m" << filename << "\033[0m" << std::endl;
			btc.exchange(filename);
		}
		catch (const std::exception& e)
		{
			PP_EXCEPTION(e);
		}
	}
	else
	{
		try
		{
			const std::string databaseName = argv[argc - 1];
			BitcoinExchange btc(databaseName);
			for (int i = 1; i < argc - 1; ++i)
			{
				const std::string filename = argv[i];
				std::cout << "Exchange for \033[1;33m" << filename << "\033[0m" << std::endl;
				try
				{
					btc.exchange(filename);
				}
				catch (const std::exception& e)
				{
					PP_EXCEPTION(e);
				}
			}
		}
		catch (const std::exception& e)
		{
			PP_EXCEPTION(e);
		}
	}

	return (0);
}
