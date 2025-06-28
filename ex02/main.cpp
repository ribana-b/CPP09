/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:14:04 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2025/06/29 01:19:38 by ribana-b         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>		// For std::cout
#include <vector>		// For std::vector
#include <deque>		// For std::deque
#include <iomanip>		// For std::setprecision
#include <algorithm>	// For std::sort
#include <ctime>		// For std::clock_t std::clock
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

void	testVectorSortFromParameters(std::size_t testIndex, const std::vector<int> vectorFromInput)
{
	PP_TEST(testIndex);
	PmergeMe pm;

	{
		std::cout << "MergeInsertion Sort" << std::endl;
		PmergeMe::Int::nComps = 0;
		std::vector<int> vec(vectorFromInput);

		std::cout << "Before:      ";
		for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		pm.sort(vec);
		std::cout << std::fixed << std::setprecision(6);

		std::cout << "After:       ";
		for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << "Size:        " << vec.size() << std::endl;
		std::cout << "Time:        " << pm.getTimer() << std::endl;
		std::cout << "Comparisons: " << PmergeMe::Int::nComps << std::endl;
	}

	{
		std::cout << "Builtin Sort" << std::endl;
		PmergeMe::Int::nComps = 0;
		std::vector<PmergeMe::Int> vec(vectorFromInput.begin(), vectorFromInput.end());

		std::cout << "Before:      ";
		for (std::vector<PmergeMe::Int>::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::clock_t start = std::clock();
		std::sort(vec.begin(), vec.end());
		std::clock_t end = std::clock();

		std::cout << "After:       ";
		for (std::vector<PmergeMe::Int>::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << std::fixed << std::setprecision(6);
		double timer = static_cast<double>(end - start) / CLOCKS_PER_SEC;

		std::cout << "Size:        " << vec.size() << std::endl;
		std::cout << "Time:        " << timer << std::endl;
		std::cout << "Comparisons: " << PmergeMe::Int::nComps << std::endl;
	}
}

void	testVectorSortEmptyVector(std::size_t testIndex)
{
	PP_TEST(testIndex);

	PmergeMe pm;

	{
		std::cout << "MergeInsertion Sort" << std::endl;
		PmergeMe::Int::nComps = 0;
		std::vector<int> vec;

		std::cout << "Before:      ";
		for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		pm.sort(vec);
		std::cout << std::fixed << std::setprecision(6);

		std::cout << "After:       ";
		for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << "Size:        " << vec.size() << std::endl;
		std::cout << "Time:        " << pm.getTimer() << std::endl;
		std::cout << "Comparisons: " << PmergeMe::Int::nComps << std::endl;
	}

	{
		std::cout << "Builtin Sort" << std::endl;
		PmergeMe::Int::nComps = 0;
		std::vector<PmergeMe::Int> vec;

		std::cout << "Before:      ";
		for (std::vector<PmergeMe::Int>::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		std::clock_t start = std::clock();
		std::sort(vec.begin(), vec.end());
		std::clock_t end = std::clock();

		std::cout << "After:       ";
		for (std::vector<PmergeMe::Int>::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << std::fixed << std::setprecision(6);
		double timer = static_cast<double>(end - start) / CLOCKS_PER_SEC;

		std::cout << "Size:        " << vec.size() << std::endl;
		std::cout << "Time:        " << timer << std::endl;
		std::cout << "Comparisons: " << PmergeMe::Int::nComps << std::endl;
	}
}

void	testVectorSortOneNumber(std::size_t testIndex)
{
	PP_TEST(testIndex);
	int arr[] = {
		1
	};
	std::size_t arrSize = sizeof(arr) / sizeof(arr[0]);

	PmergeMe pm;

	{
		std::cout << "MergeInsertion Sort" << std::endl;
		PmergeMe::Int::nComps = 0;
		std::vector<int> vec(arr, arr + arrSize);

		std::cout << "Before:      ";
		for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		pm.sort(vec);
		std::cout << std::fixed << std::setprecision(6);

		std::cout << "After:       ";
		for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << "Size:        " << vec.size() << std::endl;
		std::cout << "Time:        " << pm.getTimer() << std::endl;
		std::cout << "Comparisons: " << PmergeMe::Int::nComps << std::endl;
	}

	{
		std::cout << "Builtin Sort" << std::endl;
		PmergeMe::Int::nComps = 0;
		std::vector<PmergeMe::Int> vec(arr, arr + arrSize);

		std::cout << "Before:      ";
		for (std::vector<PmergeMe::Int>::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		std::clock_t start = std::clock();
		std::sort(vec.begin(), vec.end());
		std::clock_t end = std::clock();

		std::cout << "After:       ";
		for (std::vector<PmergeMe::Int>::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << std::fixed << std::setprecision(6);
		double timer = static_cast<double>(end - start) / CLOCKS_PER_SEC;

		std::cout << "Size:        " << vec.size() << std::endl;
		std::cout << "Time:        " << timer << std::endl;
		std::cout << "Comparisons: " << PmergeMe::Int::nComps << std::endl;
	}
}

void	testVectorSortTwoNumbers(std::size_t testIndex)
{
	PP_TEST(testIndex);
	int arr[] = {
		2, 1
	};
	std::size_t arrSize = sizeof(arr) / sizeof(arr[0]);

	PmergeMe pm;

	{
		std::cout << "MergeInsertion Sort" << std::endl;
		PmergeMe::Int::nComps = 0;
		std::vector<int> vec(arr, arr + arrSize);

		std::cout << "Before:      ";
		for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		pm.sort(vec);
		std::cout << std::fixed << std::setprecision(6);

		std::cout << "After:       ";
		for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << "Size:        " << vec.size() << std::endl;
		std::cout << "Time:        " << pm.getTimer() << std::endl;
		std::cout << "Comparisons: " << PmergeMe::Int::nComps << std::endl;
	}

	{
		std::cout << "Builtin Sort" << std::endl;
		PmergeMe::Int::nComps = 0;
		std::vector<PmergeMe::Int> vec(arr, arr + arrSize);

		std::cout << "Before:      ";
		for (std::vector<PmergeMe::Int>::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		std::clock_t start = std::clock();
		std::sort(vec.begin(), vec.end());
		std::clock_t end = std::clock();

		std::cout << "After:       ";
		for (std::vector<PmergeMe::Int>::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << std::fixed << std::setprecision(6);
		double timer = static_cast<double>(end - start) / CLOCKS_PER_SEC;

		std::cout << "Size:        " << vec.size() << std::endl;
		std::cout << "Time:        " << timer << std::endl;
		std::cout << "Comparisons: " << PmergeMe::Int::nComps << std::endl;
	}
}

void	testVectorSortThreeNumbers(std::size_t testIndex)
{
	PP_TEST(testIndex);
	int arr[] = {
		2, 3, 1
	};
	std::size_t arrSize = sizeof(arr) / sizeof(arr[0]);

	PmergeMe pm;

	{
		std::cout << "MergeInsertion Sort" << std::endl;
		PmergeMe::Int::nComps = 0;
		std::vector<int> vec(arr, arr + arrSize);

		std::cout << "Before:      ";
		for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		pm.sort(vec);
		std::cout << std::fixed << std::setprecision(6);

		std::cout << "After:       ";
		for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << "Size:        " << vec.size() << std::endl;
		std::cout << "Time:        " << pm.getTimer() << std::endl;
		std::cout << "Comparisons: " << PmergeMe::Int::nComps << std::endl;
	}

	{
		std::cout << "Builtin Sort" << std::endl;
		PmergeMe::Int::nComps = 0;
		std::vector<PmergeMe::Int> vec(arr, arr + arrSize);

		std::cout << "Before:      ";
		for (std::vector<PmergeMe::Int>::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		std::clock_t start = std::clock();
		std::sort(vec.begin(), vec.end());
		std::clock_t end = std::clock();

		std::cout << "After:       ";
		for (std::vector<PmergeMe::Int>::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << std::fixed << std::setprecision(6);
		double timer = static_cast<double>(end - start) / CLOCKS_PER_SEC;

		std::cout << "Size:        " << vec.size() << std::endl;
		std::cout << "Time:        " << timer << std::endl;
		std::cout << "Comparisons: " << PmergeMe::Int::nComps << std::endl;
	}
}

void	testVectorSortFourNumbers(std::size_t testIndex)
{
	PP_TEST(testIndex);
	int arr[] = {
		2, 1, 3, 4
	};
	std::size_t arrSize = sizeof(arr) / sizeof(arr[0]);

	PmergeMe pm;

	{
		std::cout << "MergeInsertion Sort" << std::endl;
		PmergeMe::Int::nComps = 0;
		std::vector<int> vec(arr, arr + arrSize);

		std::cout << "Before:      ";
		for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		pm.sort(vec);
		std::cout << std::fixed << std::setprecision(6);

		std::cout << "After:       ";
		for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << "Size:        " << vec.size() << std::endl;
		std::cout << "Time:        " << pm.getTimer() << std::endl;
		std::cout << "Comparisons: " << PmergeMe::Int::nComps << std::endl;
	}

	{
		std::cout << "Builtin Sort" << std::endl;
		PmergeMe::Int::nComps = 0;
		std::vector<PmergeMe::Int> vec(arr, arr + arrSize);

		std::cout << "Before:      ";
		for (std::vector<PmergeMe::Int>::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		std::clock_t start = std::clock();
		std::sort(vec.begin(), vec.end());
		std::clock_t end = std::clock();

		std::cout << "After:       ";
		for (std::vector<PmergeMe::Int>::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << std::fixed << std::setprecision(6);
		double timer = static_cast<double>(end - start) / CLOCKS_PER_SEC;

		std::cout << "Size:        " << vec.size() << std::endl;
		std::cout << "Time:        " << timer << std::endl;
		std::cout << "Comparisons: " << PmergeMe::Int::nComps << std::endl;
	}
}

void	testVectorSortFiveNumbers(std::size_t testIndex)
{
	PP_TEST(testIndex);
	int arr[] = {
		2, 1, 5, 3, 4
	};
	std::size_t arrSize = sizeof(arr) / sizeof(arr[0]);

	PmergeMe pm;

	{
		std::cout << "MergeInsertion Sort" << std::endl;
		PmergeMe::Int::nComps = 0;
		std::vector<int> vec(arr, arr + arrSize);

		std::cout << "Before:      ";
		for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		pm.sort(vec);
		std::cout << std::fixed << std::setprecision(6);

		std::cout << "After:       ";
		for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << "Size:        " << vec.size() << std::endl;
		std::cout << "Time:        " << pm.getTimer() << std::endl;
		std::cout << "Comparisons: " << PmergeMe::Int::nComps << std::endl;
	}

	{
		std::cout << "Builtin Sort" << std::endl;
		PmergeMe::Int::nComps = 0;
		std::vector<PmergeMe::Int> vec(arr, arr + arrSize);

		std::cout << "Before:      ";
		for (std::vector<PmergeMe::Int>::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		std::clock_t start = std::clock();
		std::sort(vec.begin(), vec.end());
		std::clock_t end = std::clock();

		std::cout << "After:       ";
		for (std::vector<PmergeMe::Int>::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << std::fixed << std::setprecision(6);
		double timer = static_cast<double>(end - start) / CLOCKS_PER_SEC;

		std::cout << "Size:        " << vec.size() << std::endl;
		std::cout << "Time:        " << timer << std::endl;
		std::cout << "Comparisons: " << PmergeMe::Int::nComps << std::endl;
	}
}

void	testVectorSortTenNumbers(std::size_t testIndex)
{
	PP_TEST(testIndex);
	int arr[] = {
		5, 7, 10, 9, 8, 6, 4, 3, 2, 1
	};
	std::size_t arrSize = sizeof(arr) / sizeof(arr[0]);

	PmergeMe pm;

	{
		std::cout << "MergeInsertion Sort" << std::endl;
		PmergeMe::Int::nComps = 0;
		std::vector<int> vec(arr, arr + arrSize);

		std::cout << "Before:      ";
		for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		pm.sort(vec);
		std::cout << std::fixed << std::setprecision(6);

		std::cout << "After:       ";
		for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << "Size:        " << vec.size() << std::endl;
		std::cout << "Time:        " << pm.getTimer() << std::endl;
		std::cout << "Comparisons: " << PmergeMe::Int::nComps << std::endl;
	}

	{
		std::cout << "Builtin Sort" << std::endl;
		PmergeMe::Int::nComps = 0;
		std::vector<PmergeMe::Int> vec(arr, arr + arrSize);

		std::cout << "Before:      ";
		for (std::vector<PmergeMe::Int>::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		std::clock_t start = std::clock();
		std::sort(vec.begin(), vec.end());
		std::clock_t end = std::clock();

		std::cout << "After:       ";
		for (std::vector<PmergeMe::Int>::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << std::fixed << std::setprecision(6);
		double timer = static_cast<double>(end - start) / CLOCKS_PER_SEC;

		std::cout << "Size:        " << vec.size() << std::endl;
		std::cout << "Time:        " << timer << std::endl;
		std::cout << "Comparisons: " << PmergeMe::Int::nComps << std::endl;
	}
}

void	testVectorSortThreeThousandNumbers(std::size_t testIndex)
{
	PP_TEST(testIndex);
	int arr[] = {
		3059, 6271, 8138, 5961, 3782, 306, 6649, 2339, 3665, 6360, 6555, 8214, 4328, 9306, 5625, 7854, 193, 2052, 3361, 4995, 1922, 487, 9105, 8208, 317, 7990, 3540, 4921, 4417, 7616, 6988, 2113, 7599, 6065, 4148, 3680, 2120, 6307, 9522, 6827, 8445, 622, 8597, 2618, 3712, 2577, 8991, 6067, 2678, 7323, 8741, 9080, 3302, 3555, 2705, 5954, 6962, 6562, 3874, 8512, 9721, 551, 3051, 7258, 3633, 6477, 2182, 2738, 153, 110, 4786, 2225, 4679, 2349, 35, 1484, 6467, 9922, 6300, 9954, 6766, 4502, 7694, 2163, 1344, 7414, 5569, 4700, 8634, 1739, 6264, 8206, 1424, 9406, 3180, 3723, 5619, 3177, 2554, 1814, 7571, 186, 3582, 9898, 1523, 4782, 3159, 835, 4134, 534, 811, 9738, 8270, 9231, 209, 2877, 4353, 1659, 4072, 2542, 3559, 1810, 9807, 2480, 6519, 4209, 3383, 6296, 7695, 3617, 1944, 8631, 2154, 9112, 9166, 9521, 4277, 4466, 6100, 4314, 7584, 9317, 7171, 1581, 8864, 1486, 710, 5494, 7845, 124, 359, 8411, 2155, 5151, 1809, 9865, 6038, 2578, 1871, 4144, 2012, 2785, 769, 8678, 5804, 3247, 2177, 5570, 3848, 3484, 8227, 5237, 3011, 8122, 1782, 5240, 2510, 3961, 5617, 7480, 3726, 7970, 9412, 247, 1829, 1699, 9005, 6883, 7397, 1789, 5733, 5000, 1413, 8865, 1849, 7482, 9623, 1061, 5023, 5716, 7552, 6835, 7913, 4911, 2166, 1976, 6698, 759, 5239, 327, 755, 5638, 8855, 2917, 4120, 1924, 2169, 3751, 4075, 2408, 7063, 6553, 8918, 9361, 2811, 6537, 7526, 653, 4916, 1816, 3351, 4536, 2624, 8376, 2411, 2793, 7320, 4925, 4648, 1729, 1042, 8877, 6061, 5567, 958, 6552, 2385, 5763, 3280, 3404, 5732, 1734, 6309, 800, 8913, 426, 2938, 2893, 7448, 2736, 8113, 6337, 5191, 7489, 4156, 9761, 6334, 7995, 9258, 233, 8489, 3160, 9218, 5094, 8885, 5449, 895, 8775, 3463, 450, 4776, 4380, 7443, 3130, 3586, 4374, 1072, 744, 3832, 7896, 2523, 5100, 7365, 1725, 1831, 2309, 2159, 1473, 7903, 8450, 8737, 6156, 5989, 6627, 7311, 4868, 9439, 9708, 2204, 2454, 365, 8464, 6008, 3960, 5680, 8163, 713, 1740, 2085, 6667, 2753, 7160, 3941, 6610, 3631, 1537, 4680, 9132, 8487, 8738, 8514, 4661, 8439, 1395, 3892, 2901, 4510, 2452, 5436, 6850, 2606, 7328, 132, 854, 4955, 3763, 9023, 9962, 1968, 216, 9282, 6492, 9390, 9223, 5004, 1437, 4567, 2011, 8852, 7690, 8785, 4627, 4714, 7834, 1101, 5875, 6703, 7343, 6822, 3483, 7602, 2190, 1187, 6723, 1314, 3858, 8070, 4389, 7265, 5681, 4465, 8006, 9660, 6540, 8739, 7439, 9838, 8986, 9504, 2498, 7802, 2272, 7943, 8404, 1131, 1195, 7252, 6821, 4823, 6210, 9880, 6092, 3420, 789, 5212, 4385, 4238, 5157, 8819, 4555, 3676, 3350, 9728, 8187, 6783, 467, 4221, 389, 9477, 3619, 8075, 3523, 2746, 9048, 6725, 1910, 385, 9494, 6011, 1352, 7952, 9382, 3050, 986, 4706, 2548, 4669, 1981, 2071, 3687, 3002, 1275, 2966, 2392, 1526, 1568, 5575, 9843, 4415, 5572, 5613, 4666, 5061, 4611, 8860, 4546, 1283, 767, 24, 6076, 9851, 2869, 1610, 7190, 5492, 8517, 3150, 5555, 4285, 5601, 4844, 8174, 2794, 3436, 4160, 9827, 3797, 220, 1671, 9385, 7399, 7550, 5996, 620, 3321, 1677, 9489, 8413, 5262, 9544, 9965, 7918, 1966, 4917, 3403, 4815, 1450, 7762, 8533, 8682, 1583, 3611, 9141, 2275, 1674, 6459, 4713, 3437, 989, 9163, 4294, 9460, 2056, 1112, 3982, 8022, 1614, 8140, 832, 9408, 5159, 4860, 3122, 9037, 7402, 213, 4431, 985, 7009, 454, 8289, 2571, 9085, 5051, 820, 2333, 4387, 2263, 8204, 9492, 6024, 8194, 2377, 6246, 2040, 7053, 6747, 3962, 5223, 4943, 7708, 5538, 957, 6189, 483, 5092, 1770, 3342, 6913, 6891, 2940, 9753, 1854, 619, 9688, 8222, 9633, 9473, 7976, 8652, 5192, 6472, 4612, 6225, 2395, 9548, 506, 4514, 3809, 41, 4733, 8716, 7147, 5772, 7730, 8410, 905, 7094, 6596, 6396, 1097, 5077, 1092, 9526, 7639, 7546, 2889, 6848, 1479, 9162, 4773, 9358, 7458, 7174, 3811, 6111, 1802, 4684, 4141, 3861, 5929, 2239, 6879, 1914, 3080, 3902, 3291, 7681, 4801, 7937, 954, 257, 9096, 8977, 4885, 9736, 4799, 8089, 5895, 4620, 4990, 1034, 3514, 3537, 13, 641, 6048, 9746, 202, 2456, 4102, 8635, 3013, 562, 4607, 8200, 1268, 9081, 2046, 2131, 5195, 4045, 4753, 1632, 7815, 7851, 6965, 8810, 1493, 2780, 2504, 6118, 263, 3274, 5298, 9911, 7339, 4725, 2865, 5347, 7644, 451, 3303, 6648, 4673, 3841, 9097, 3814, 5442, 3457, 740, 7860, 126, 6880, 4360, 2274, 7031, 6936, 5950, 793, 9158, 818, 4507, 7789, 3181, 488, 5009, 3344, 7225, 7085, 9220, 2035, 7222, 5591, 5371, 3108, 1383, 7548, 5447, 3986, 6630, 8526, 1630, 214, 5445, 3765, 7906, 9854, 643, 5426, 7917, 3315, 5133, 4250, 4473, 3346, 8016, 3749, 7412, 2913, 4096, 7832, 6478, 8836, 9824, 1609, 1783, 8144, 7333, 9508, 5735, 5688, 7518, 9629, 8857, 7981, 7345, 7472, 4245, 4112, 6281, 667, 9939, 530, 6190, 4690, 6700, 1835, 7676, 58, 5956, 7359, 2356, 628, 6260, 6796, 6208, 9344, 9866, 6756, 5269, 2280, 858, 865, 3910, 4549, 7862, 6967, 8331, 57, 7972, 995, 1986, 5219, 5987, 553, 6355, 1198, 955, 7543, 4715, 9777, 6200, 9776, 7812, 2672, 4354, 1135, 7143, 774, 8403, 5119, 5535, 4609, 8521, 1639, 4063, 16, 6352, 1658, 9487, 6465, 1548, 5963, 7004, 6775, 7583, 9000, 3802, 6577, 6861, 9989, 5805, 2789, 4028, 6753, 8360, 4154, 6689, 174, 8501, 6604, 8007, 9822, 6733, 148, 9127, 7185, 2714, 6012, 8198, 9357, 6759, 1612, 7296, 378, 3380, 5943, 2858, 1994, 4802, 3800, 972, 8770, 7478, 6672, 9529, 8306, 6403, 9226, 9793, 2387, 2513, 3963, 8954, 3116, 4694, 32, 6020, 4230, 9088, 6707, 933, 671, 9711, 2549, 9978, 1563, 5460, 210, 4418, 4566, 7936, 222, 9975, 2588, 3999, 3717, 9149, 7779, 3502, 4196, 5453, 1950, 7649, 2765, 9917, 9301, 4488, 883, 4987, 6347, 6740, 636, 4312, 3113, 2146, 6888, 99, 761, 4482, 4701, 2574, 4300, 2332, 4500, 6220, 7634, 8417, 9024, 4450, 8959, 9198, 9648, 542, 7501, 4790, 4902, 4499, 6785, 4827, 6241, 2607, 9103, 5632, 2162, 9588, 4190, 5823, 8578, 6149, 9971, 6466, 3744, 3643, 517, 3632, 4162, 7325, 1459, 6042, 549, 1881, 4908, 8320, 2347, 8049, 3048, 919, 4832, 5850, 1087, 7404, 1117, 3791, 7959, 3852, 1506, 6676, 8246, 3666, 891, 7259, 3905, 5467, 531, 7058, 5652, 9147, 7580, 2218, 5917, 4830, 3254, 286, 1173, 4188, 224, 7182, 6221, 168, 3095, 1175, 932, 2681, 3608, 8582, 2743, 5121, 3142, 8374, 6621, 7919, 6809, 2561, 5614, 9545, 1031, 391, 131, 3377, 3262, 5425, 1255, 9611, 8468, 8039, 7406, 9225, 5380, 2804, 2902, 815, 2051, 8599, 4044, 5560, 2932, 9353, 376, 7018, 4674, 151, 3472, 3100, 3790, 2466, 3783, 6326, 6767, 8751, 4915, 9339, 1154, 3992, 7785, 135, 9152, 2373, 3898, 1161, 571, 5256, 6242, 6970, 4968, 9179, 7340, 434, 8657, 4183, 9891, 8618, 8253, 235, 5306, 2976, 2543, 999, 1046, 5251, 8493, 1137, 5749, 1851, 6545, 8724, 6590, 845, 9752, 8023, 2201, 686, 7169, 9386, 9126, 1204, 4928, 8870, 1083, 6344, 3638, 7, 821, 7368, 6815, 206, 1448, 5479, 6379, 1419, 695, 6586, 1337, 7256, 9619, 1289, 6028, 8472, 1631, 1586, 8276, 9640, 7707, 9695, 8664, 2947, 9430, 2380, 1576, 6572, 8881, 8008, 2245, 2171, 3615, 5992, 5020, 2258, 1005, 556, 2132, 1897, 2129, 2995, 6182, 4284, 2122, 5170, 3720, 241, 7096, 4932, 7737, 5991, 607, 608, 6705, 7271, 7116, 8019, 3200, 3950, 1466, 7042, 9584, 9100, 4877, 9608, 9488, 4176, 3845, 8898, 1665, 9914, 4397, 8157, 3476, 4165, 4972, 629, 6093, 2400, 5730, 2473, 8831, 4898, 9779, 9773, 6164, 1533, 2070, 2491, 8252, 6933, 1792, 2412, 515, 8054, 4878, 22, 5393, 682, 3836, 9552, 9737, 4049, 4246, 3746, 523, 3372, 7212, 4919, 6702, 4438, 8809, 7168, 3622, 3563, 5165, 2847, 4350, 9596, 2635, 642, 4082, 4521, 61, 2828, 3473, 828, 6780, 1339, 9674, 9403, 2700, 3817, 6289, 5171, 1026, 8173, 9084, 1366, 9560, 6832, 9751, 4887, 2254, 8257, 1379, 8486, 9510, 318, 1436, 6399, 9567, 1207, 4271, 1558, 7224, 3598, 4269, 5620, 2894, 7755, 8938, 3921, 8976, 997, 43, 7833, 6882, 8114, 49, 6179, 3014, 5500, 6001, 5430, 7671, 7077, 2435, 1982, 1274, 7502, 7393, 7908, 3034, 6971, 795, 3819, 4865, 4365, 5440, 8912, 7878, 4098, 4681, 9240, 7823, 8766, 5967, 1248, 7134, 5131, 4712, 4542, 6313, 8386, 8789, 9304, 4347, 6989, 5815, 9659, 645, 1819, 4848, 5658, 8355, 7124, 3000, 9577, 586, 2710, 5283, 1445, 217, 2107, 9422, 393, 5977, 3421, 8594, 4769, 1369, 2101, 4857, 2293, 7984, 6235, 4122, 6139, 5095, 1063, 3127, 2989, 244, 3908, 4704, 8801, 9320, 2846, 6746, 1007, 4060, 4123, 4150, 1891, 2860, 7280, 8609, 3628, 7643, 4373, 6132, 8462, 9067, 9065, 9638, 934, 7509, 6278, 1985, 3864, 2751, 9369, 9499, 564, 8178, 172, 6310, 5883, 2017, 4890, 2002, 3354, 4647, 949, 8722, 7084, 8725, 6121, 3400, 1785, 8776, 7192, 3278, 5039, 5081, 316, 405, 6074, 7065, 3694, 297, 4187, 5252, 5871, 7055, 3501, 3229, 9343, 6055, 676, 7656, 2767, 5319, 6600, 6905, 1528, 8266, 3621, 8073, 4351, 1778, 625, 6249, 5584, 778, 8916, 6462, 7234, 6014, 2620, 2983, 1717, 3822, 6916, 6032, 730, 4791, 7269, 7503, 6765, 5901, 3596, 2980, 4066, 1867, 3031, 5580, 4539, 5162, 1478, 3572, 5462, 80, 2091, 1979, 1970, 2975, 7307, 9183, 1517, 6961, 7701, 1800, 4202, 1678, 2559, 9533, 5879, 5079, 1232, 164, 6942, 6144, 3434, 7044, 2969, 3187, 1367, 2111, 1650, 9360, 4525, 4644, 9283, 1002, 2615, 7891, 4279, 2520, 4825, 4922, 963, 6097, 3272, 3799, 4342, 6808, 2158, 9, 6894, 2092, 909, 4849, 7367, 3094, 6834, 267, 7187, 3881, 5561, 965, 3515, 5224, 1923, 8837, 2047, 1032, 2617, 9905, 3590, 9170, 9762, 8917, 7315, 1852, 7156, 3641, 7100, 6369, 5756, 4760, 472, 4794, 3648, 293, 4332, 773, 8730, 2599, 7922, 9454, 6217, 786, 6598, 7284, 9654, 4975, 9315, 9966, 8443, 5066, 9234, 8608, 1904, 817, 9527, 5720, 9266, 7715, 5175, 4515, 9331, 7733, 6743, 8224, 5253, 4642, 8155, 5966, 3109, 7372, 6057, 9820, 3599, 4366, 4688, 1368, 2414, 5773, 5969, 4424, 6231, 6143, 6764, 4453, 541, 7395, 4213, 3995, 2020, 3867, 7484, 9626, 5552, 7465, 5358, 6397, 661, 3786, 5144, 6635, 1023, 3265, 3256, 5402, 9060, 874, 5105, 2508, 2613, 2114, 9188, 7675, 9605, 3674, 3015, 1170, 300, 4215, 52, 3914, 6897, 7535, 4311, 3307, 5148, 7130, 6718, 6978, 1225, 7446, 2478, 6772, 8568, 912, 2937, 8408, 5071, 1622, 6077, 3464, 1410, 1230, 5790, 7196, 6317, 170, 4837, 1125, 5238, 8041, 5208, 8999, 1571, 2014, 7388, 9802, 918, 6248, 1895, 5033, 7181, 9800, 1332, 6597, 758, 8389, 100, 2691, 6727, 9813, 6059, 105, 5177, 6173, 3244, 3803, 9490, 3711, 4621, 5660, 1115, 3338, 5907, 5428, 1578, 3191, 1653, 9043, 6160, 6215, 5526, 8850, 668, 2283, 9921, 372, 2525, 2802, 1315, 1085, 3238, 2539, 5653, 9495, 2663, 1763, 9173, 7895, 500, 4882, 8455, 3326, 2375, 8333, 8895, 5761, 10, 5528, 5607, 3194, 1539, 3012, 5375, 6104, 3719, 3170, 2627, 2042, 3558, 6669, 1633, 4407, 8344, 787, 1205, 7081, 8650, 3856, 5403, 5541, 6298, 5194, 1661, 1917, 5611, 8981, 6593, 4699, 851, 4903, 798, 3243, 7049, 8422, 6345, 8676, 577, 8698, 4469, 8255, 9134, 1350, 2396, 9734, 528, 7385, 8805, 8192, 4874, 2658, 2956, 3075, 9434, 266, 2144, 4632, 6069, 3367, 7183, 9211, 5450, 5687, 8589, 1926, 7961, 6203, 2079, 9119, 7302, 6752, 5594, 4371, 3395, 4923, 9606, 3550, 7074, 7273, 5698, 1728, 554, 8310, 9334, 5049, 2779, 8158, 1291, 6297, 115, 6675, 46, 1954, 3571, 5962, 5742, 7008, 1952, 1391, 7749, 6125, 4395, 6867, 7577, 2142, 7140, 4651, 3618, 3739, 2455, 5602, 8094, 8399, 7511, 6244, 3662, 3296, 7310, 8205, 95, 887, 4936, 584, 1491, 3917, 2016, 5015, 9217, 1695, 939, 4340, 8791, 7193, 971, 8014, 3089, 546, 6116, 3983, 3863, 1641, 4376, 2093, 4935, 6254, 7392, 8111, 6791, 6889, 3304, 1868, 4655, 6187, 7820, 6408, 6488, 1620, 8735, 1048, 2823, 8382, 9515, 3842, 2492, 6437, 6973, 9755, 9036, 6987, 5138, 5744, 6385, 9908, 8793, 6570, 5242, 6041, 3745, 7680, 8612, 2420, 8552, 3155, 2764, 6612, 5593, 9122, 4372, 7034, 9771, 8046, 6479, 1057, 8816, 3844, 1750, 4841, 187, 8308, 5301, 4074, 6995, 6475, 9698, 1832, 1231, 1041, 5808, 7021, 9345, 8164, 5705, 8165, 9685, 7778, 6159, 6800, 9636, 5655, 2232, 8195, 5852, 229, 1737, 6509, 1555, 3115, 1296, 4022, 3651, 4443, 5012, 9952, 9274, 5080, 3285, 8296, 7868, 4532, 6324, 7811, 3266, 4962, 2364, 5055, 6106, 8396, 7873, 7805, 2622, 1082, 9710, 2073, 3263, 2112, 9546, 9683, 2723, 9995, 312, 910, 2394, 812, 8867, 8390, 1303, 8437, 2393, 5502, 2727, 3165, 2977, 2715, 8679, 7045, 1948, 7415, 4738, 74, 4048, 7228, 7250, 715, 3549, 4331, 8760, 4258, 1973, 7477, 3626, 5040, 8299, 6040, 1124, 5830, 3417, 6691, 6730, 8869, 4186, 260, 3513, 9224, 7830, 8071, 9607, 2836, 8798, 2267, 9082, 4359, 3701, 1490, 3477, 9305, 1389, 9066, 3870, 8086, 1420, 5351, 2036, 9378, 4191, 8915, 2660, 7411, 8565, 8000, 6406, 8997, 6429, 5982, 6280, 9576, 8495, 8366, 1644, 6826, 9243, 663, 2801, 1546, 5893, 3073, 5336, 9327, 7199, 1396, 2481, 4742, 2416, 1691, 3330, 1488, 4969, 7206, 8419, 3210, 2758, 6286, 4220, 4472, 6957, 5837, 1433, 8706, 3221, 5437, 1997, 2350, 1963, 4267, 2497, 8784, 3072, 1406, 2739, 9253, 2556, 5902, 5851, 3532, 2752, 1885, 882, 8309, 4767, 6120, 9687, 3579, 8161, 8265, 4626, 9610, 1355, 3275, 8130, 9462, 2984, 2685, 6681, 5791, 8500, 4214, 1759, 4544, 5011, 9594, 2076, 8649, 2863, 698, 8287, 9069, 906, 6426, 5568, 7389, 3663, 5106, 6391, 3931, 856, 8559, 8525, 2358, 6868, 1239, 4041, 3524, 5337, 2084, 3174, 2558, 199, 5295, 8203, 9671, 1877, 3732, 6857, 762, 1462, 8465, 1267, 3077, 8615, 1322, 5116, 9787, 9562, 8461, 6022, 7888, 9381, 1273, 990, 3427, 9148, 3270, 2226, 6599, 4318, 2363, 6442, 3224, 9445, 7337, 7073, 7763, 1374, 810, 8998, 7828, 1607, 6646, 7457, 6270, 9876, 5564, 1261, 1335, 249, 6849, 5818, 36, 4640, 207, 2389, 5695, 4364, 7139, 2677, 2413, 101, 7263, 4850, 4999, 272, 4032, 1860, 7620, 9798, 3547, 5665, 1712, 2730, 2050, 4127, 3980, 4592, 1795, 6230, 5362, 3511, 2630, 3409, 6357, 7043, 6844, 849, 3196, 4116, 1958, 4840, 8328, 8482, 8980, 5741, 8024, 6873, 8680, 3419, 5626, 9852, 8924, 8808, 50, 3153, 8416, 9591, 1327, 2161, 8899, 7910, 7724, 4050, 2517, 4222, 8369, 3700, 8813, 3171, 7318, 6603, 1133, 7920, 5510, 5740, 3601, 609, 8447, 6206, 9340, 9681, 6272, 9677, 5431, 2729, 1663, 223, 4891, 9049, 3645, 9609, 9970, 7567, 6054, 7973, 6291, 1787, 282, 5679, 5885, 3829, 5524, 7925, 3474, 5146, 5124, 3492, 7698, 3076, 9895, 8373, 3734, 1700, 3862, 2978, 6395, 1524, 3685, 3503, 1153, 8823, 2215, 4746, 8902, 1138, 137, 8011, 7980, 5924, 1500, 9203, 4839, 8146, 2666, 9246, 121, 2472, 9587, 490, 8572, 8438, 7957, 7561, 980, 4762, 6303, 3442, 6632, 9924, 1980, 1019, 5378, 4896, 4686, 4831, 7235, 5296, 4004, 5624, 3246, 8045, 7264, 460, 511, 3682, 208, 5829, 7075, 8587, 9095, 3728, 5297, 725, 2440, 9174, 6813, 9008, 4388, 7114, 4410, 2638, 2136, 1669, 9568, 3022, 4189, 4793, 1306, 1702, 7894, 6451, 8076, 2864, 6589, 9679, 158, 298, 332, 238, 2535, 5531, 8463, 8062, 8168, 8108, 8101, 3789, 2170, 707, 4892, 1189, 6890, 370, 5753, 8221, 635, 5673, 4071, 4575, 5586, 2176, 5562, 7421, 27, 9261, 8233, 1853, 1595, 2446, 8556, 7285, 8658, 5097, 1372, 9680, 2353, 1510, 1326, 3565, 4173, 9129, 1310, 5084, 4615, 8845, 9647, 7060, 5540, 4302, 432, 9117, 388, 6946, 897, 1052, 2911, 3408, 7135, 7849, 3507, 9332, 4323, 6576, 480, 1956, 5415, 3656, 5677, 280, 4560, 3834, 212, 7559, 2933, 2453, 5563, 1353, 9661, 3580, 447, 3443, 3039, 1873, 2625, 880, 6919, 6768, 9501, 1323, 9974, 5145, 203, 5126, 1903, 5168, 1535, 8350, 6619, 2424, 6062, 8212, 4143, 1780, 1590, 7723, 4197, 478, 5400, 7655, 6274, 6034, 2043, 9990, 3237, 765, 371, 7029, 2965, 9706, 5792, 3481, 5737, 2761, 9955, 7260, 7494, 4571, 5491, 8908, 4739, 1235, 9897, 9102, 2516, 2439, 1015, 8888, 7313, 7197, 9461, 8936, 1330, 5717, 6636, 6869, 931, 9701, 3518, 3104, 6, 5227, 7531, 7529, 3252, 7593, 3733, 2331, 2560, 7967, 8889, 7632, 5489, 2629, 9902, 2494, 1107, 3005, 8520, 2010, 9583, 6112, 638, 4998, 782, 3459, 8726, 228, 1738, 3667, 5211, 4614, 2968, 141, 1467, 5091, 7964, 6650, 3378, 9524, 9298, 6720, 330, 9288, 7794, 4151, 4913, 3769, 3894, 1311, 6113, 8027, 3613, 5074, 2343, 4088, 163, 9468, 3839, 7390, 3967, 5872, 4025, 6151, 2756, 7495, 2214, 5603, 7841, 8250, 711, 9428, 7971, 3707, 1089, 6609, 8121, 2922, 9702, 2186, 5839, 572, 4982, 8047, 6952, 6080, 9478, 1617, 7679, 5868, 8381, 1530, 7932, 4168, 4811, 6083, 7809, 3145, 2391, 25, 3258, 2033, 9781, 5448, 424, 2720, 6405, 915, 5750, 9104, 8312, 3542, 9767, 2117, 7374, 5662, 9780, 2759, 5949, 4492, 2078, 2386, 9145, 8069, 9028, 2707, 9393, 3509, 7876, 9140, 9641, 5796, 1, 9620, 1848, 592, 8220, 3161, 875, 386, 9467, 8379, 2773, 5102, 4325, 9392, 6114, 156, 2288, 819, 5968, 5263, 6469, 1358, 2694, 6305, 9864, 3381, 3830, 8316, 8474, 9812, 2733, 1094, 421, 3588, 8291, 7587, 3352, 4894, 3730, 3021, 1284, 1176, 1693, 9115, 4155, 6198, 7614, 7369, 6358, 5024, 5385, 2999, 7797, 1155, 5832, 5141, 9493, 8569, 2994, 3129, 9273, 2266, 65, 2096, 6009, 699, 2762, 4280, 4090, 279, 2820, 3027, 1305, 2277, 9172, 3331, 9351, 4362, 254, 9464, 3794, 8332, 4731, 192, 7847, 23, 2514, 5697, 3117, 8930, 2526, 5246, 9789, 8692, 1025, 7204, 5043, 3182, 1229, 9486, 9297, 7059, 6523, 2213, 3846, 746, 3773, 8367, 9920, 9015, 75, 8987, 8151, 4181, 3032, 7564, 8240, 1439, 1055, 8353, 1403, 8685, 2202, 4863, 7960, 3798, 9982, 9774, 2183, 4006, 1030, 3940, 9894, 5529, 5130, 6261, 5684, 1696, 2536, 7221, 7752, 8665, 4324, 876, 9031, 6240, 7238, 9500, 6378, 6794, 5887, 797, 92, 184, 3750, 8456, 2335, 9484, 1996, 4629, 9341, 5781, 6075, 6096, 1145, 9167, 6605, 1243, 5443, 103, 633, 1627, 7382, 471, 7418, 9644, 5627, 6145, 2125, 8470, 7668, 5802, 2360, 8459, 3915, 4964, 5003, 7232, 2118, 9801, 7378, 8145, 2019, 1575, 7079, 1074, 17, 5250, 7052, 2665, 675, 6370, 7405, 5719, 6374, 827, 5059, 6997, 6029, 9778, 7814, 4243, 6257, 4241, 3286, 8067, 5087, 3311, 2284, 8103, 7754, 2611, 8928, 9634, 5861, 1163, 4447, 2711, 6719, 2150, 4633, 73, 4458, 3604, 6015, 4357, 8394, 8268, 8102, 4256, 7646, 4508, 9459, 9936, 3517, 7117, 6482, 9509, 2659, 9630, 3993, 499, 4108, 8641, 1236, 2415, 1746, 3016, 4524, 2298, 621, 805, 2327, 7473, 8473, 2126, 4683, 9018, 5068, 4977, 9227, 5349, 1604, 1998, 5646, 4755, 5892, 6453, 9034, 1262, 5635, 8494, 3328, 3838, 7092, 6239, 5533, 1241, 2376, 3480, 8115, 8377, 8325, 6398, 2269, 9202, 1222, 5911, 8557, 1249, 9086, 1465, 15, 8311, 2726, 45, 2950, 5112, 7066, 4232, 9259, 5294, 2023, 4219, 6631, 7512, 8083, 8506, 7710
	};
	std::size_t arrSize = sizeof(arr) / sizeof(arr[0]);

	PmergeMe pm;

	{
		std::cout << "MergeInsertion Sort" << std::endl;
		PmergeMe::Int::nComps = 0;
		std::vector<int> vec(arr, arr + arrSize);

		std::cout << "Before:      ";
		for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		pm.sort(vec);
		std::cout << std::fixed << std::setprecision(6);

		std::cout << "After:       ";
		for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << "Size:        " << vec.size() << std::endl;
		std::cout << "Time:        " << pm.getTimer() << std::endl;
		std::cout << "Comparisons: " << PmergeMe::Int::nComps << std::endl;
	}

	{
		std::cout << "Builtin Sort" << std::endl;
		PmergeMe::Int::nComps = 0;
		std::vector<PmergeMe::Int> vec(arr, arr + arrSize);

		std::cout << "Before:      ";
		for (std::vector<PmergeMe::Int>::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		std::clock_t start = std::clock();
		std::sort(vec.begin(), vec.end());
		std::clock_t end = std::clock();

		std::cout << "After:       ";
		for (std::vector<PmergeMe::Int>::iterator it = vec.begin(); it != vec.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << std::fixed << std::setprecision(6);
		double timer = static_cast<double>(end - start) / CLOCKS_PER_SEC;

		std::cout << "Size:        " << vec.size() << std::endl;
		std::cout << "Time:        " << timer << std::endl;
		std::cout << "Comparisons: " << PmergeMe::Int::nComps << std::endl;
	}
}

void	testDequeSortFromParameters(std::size_t testIndex, const std::deque<int> dequeFromInput)
{
	PP_TEST(testIndex);
	PmergeMe pm;

	{
		std::cout << "MergeInsertion Sort" << std::endl;
		PmergeMe::Int::nComps = 0;
		std::deque<int> deq(dequeFromInput);

		std::cout << "Before:      ";
		for (std::deque<int>::iterator it = deq.begin(); it != deq.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		pm.sort(deq);
		std::cout << std::fixed << std::setprecision(6);

		std::cout << "After:       ";
		for (std::deque<int>::iterator it = deq.begin(); it != deq.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << "Size:        " << deq.size() << std::endl;
		std::cout << "Time:        " << pm.getTimer() << std::endl;
		std::cout << "Comparisons: " << PmergeMe::Int::nComps << std::endl;
	}

	{
		std::cout << "Builtin Sort" << std::endl;
		PmergeMe::Int::nComps = 0;
		std::deque<PmergeMe::Int> deq(dequeFromInput.begin(), dequeFromInput.end());

		std::cout << "Before:      ";
		for (std::deque<PmergeMe::Int>::iterator it = deq.begin(); it != deq.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::clock_t start = std::clock();
		std::sort(deq.begin(), deq.end());
		std::clock_t end = std::clock();

		std::cout << "After:       ";
		for (std::deque<PmergeMe::Int>::iterator it = deq.begin(); it != deq.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << std::fixed << std::setprecision(6);
		double timer = static_cast<double>(end - start) / CLOCKS_PER_SEC;

		std::cout << "Size:        " << deq.size() << std::endl;
		std::cout << "Time:        " << timer << std::endl;
		std::cout << "Comparisons: " << PmergeMe::Int::nComps << std::endl;
	}
}

void	testDequeSortEmptyDeque(std::size_t testIndex)
{
	PP_TEST(testIndex);

	PmergeMe pm;

	{
		std::cout << "MergeInsertion Sort" << std::endl;
		PmergeMe::Int::nComps = 0;
		std::deque<int> deq;

		std::cout << "Before:      ";
		for (std::deque<int>::iterator it = deq.begin(); it != deq.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		pm.sort(deq);
		std::cout << std::fixed << std::setprecision(6);

		std::cout << "After:       ";
		for (std::deque<int>::iterator it = deq.begin(); it != deq.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << "Size:        " << deq.size() << std::endl;
		std::cout << "Time:        " << pm.getTimer() << std::endl;
		std::cout << "Comparisons: " << PmergeMe::Int::nComps << std::endl;
	}

	{
		std::cout << "Builtin Sort" << std::endl;
		PmergeMe::Int::nComps = 0;
		std::deque<PmergeMe::Int> deq;

		std::cout << "Before:      ";
		for (std::deque<PmergeMe::Int>::iterator it = deq.begin(); it != deq.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		std::clock_t start = std::clock();
		std::sort(deq.begin(), deq.end());
		std::clock_t end = std::clock();

		std::cout << "After:       ";
		for (std::deque<PmergeMe::Int>::iterator it = deq.begin(); it != deq.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << std::fixed << std::setprecision(6);
		double timer = static_cast<double>(end - start) / CLOCKS_PER_SEC;

		std::cout << "Size:        " << deq.size() << std::endl;
		std::cout << "Time:        " << timer << std::endl;
		std::cout << "Comparisons: " << PmergeMe::Int::nComps << std::endl;
	}
}

void	testDequeSortOneNumber(std::size_t testIndex)
{
	PP_TEST(testIndex);
	int arr[] = {
		1
	};
	std::size_t arrSize = sizeof(arr) / sizeof(arr[0]);

	PmergeMe pm;

	{
		std::cout << "MergeInsertion Sort" << std::endl;
		PmergeMe::Int::nComps = 0;
		std::deque<int> deq(arr, arr + arrSize);

		std::cout << "Before:      ";
		for (std::deque<int>::iterator it = deq.begin(); it != deq.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		pm.sort(deq);
		std::cout << std::fixed << std::setprecision(6);

		std::cout << "After:       ";
		for (std::deque<int>::iterator it = deq.begin(); it != deq.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << "Size:        " << deq.size() << std::endl;
		std::cout << "Time:        " << pm.getTimer() << std::endl;
		std::cout << "Comparisons: " << PmergeMe::Int::nComps << std::endl;
	}

	{
		std::cout << "Builtin Sort" << std::endl;
		PmergeMe::Int::nComps = 0;
		std::deque<PmergeMe::Int> deq(arr, arr + arrSize);

		std::cout << "Before:      ";
		for (std::deque<PmergeMe::Int>::iterator it = deq.begin(); it != deq.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		std::clock_t start = std::clock();
		std::sort(deq.begin(), deq.end());
		std::clock_t end = std::clock();

		std::cout << "After:       ";
		for (std::deque<PmergeMe::Int>::iterator it = deq.begin(); it != deq.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << std::fixed << std::setprecision(6);
		double timer = static_cast<double>(end - start) / CLOCKS_PER_SEC;

		std::cout << "Size:        " << deq.size() << std::endl;
		std::cout << "Time:        " << timer << std::endl;
		std::cout << "Comparisons: " << PmergeMe::Int::nComps << std::endl;
	}
}

void	testDequeSortTwoNumbers(std::size_t testIndex)
{
	PP_TEST(testIndex);
	int arr[] = {
		2, 1
	};
	std::size_t arrSize = sizeof(arr) / sizeof(arr[0]);

	PmergeMe pm;

	{
		std::cout << "MergeInsertion Sort" << std::endl;
		PmergeMe::Int::nComps = 0;
		std::deque<int> deq(arr, arr + arrSize);

		std::cout << "Before:      ";
		for (std::deque<int>::iterator it = deq.begin(); it != deq.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		pm.sort(deq);
		std::cout << std::fixed << std::setprecision(6);

		std::cout << "After:       ";
		for (std::deque<int>::iterator it = deq.begin(); it != deq.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << "Size:        " << deq.size() << std::endl;
		std::cout << "Time:        " << pm.getTimer() << std::endl;
		std::cout << "Comparisons: " << PmergeMe::Int::nComps << std::endl;
	}

	{
		std::cout << "Builtin Sort" << std::endl;
		PmergeMe::Int::nComps = 0;
		std::deque<PmergeMe::Int> deq(arr, arr + arrSize);

		std::cout << "Before:      ";
		for (std::deque<PmergeMe::Int>::iterator it = deq.begin(); it != deq.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		std::clock_t start = std::clock();
		std::sort(deq.begin(), deq.end());
		std::clock_t end = std::clock();

		std::cout << "After:       ";
		for (std::deque<PmergeMe::Int>::iterator it = deq.begin(); it != deq.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << std::fixed << std::setprecision(6);
		double timer = static_cast<double>(end - start) / CLOCKS_PER_SEC;

		std::cout << "Size:        " << deq.size() << std::endl;
		std::cout << "Time:        " << timer << std::endl;
		std::cout << "Comparisons: " << PmergeMe::Int::nComps << std::endl;
	}
}

void	testDequeSortThreeNumbers(std::size_t testIndex)
{
	PP_TEST(testIndex);
	int arr[] = {
		2, 3, 1
	};
	std::size_t arrSize = sizeof(arr) / sizeof(arr[0]);

	PmergeMe pm;

	{
		std::cout << "MergeInsertion Sort" << std::endl;
		PmergeMe::Int::nComps = 0;
		std::deque<int> deq(arr, arr + arrSize);

		std::cout << "Before:      ";
		for (std::deque<int>::iterator it = deq.begin(); it != deq.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		pm.sort(deq);
		std::cout << std::fixed << std::setprecision(6);

		std::cout << "After:       ";
		for (std::deque<int>::iterator it = deq.begin(); it != deq.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << "Size:        " << deq.size() << std::endl;
		std::cout << "Time:        " << pm.getTimer() << std::endl;
		std::cout << "Comparisons: " << PmergeMe::Int::nComps << std::endl;
	}

	{
		std::cout << "Builtin Sort" << std::endl;
		PmergeMe::Int::nComps = 0;
		std::deque<PmergeMe::Int> deq(arr, arr + arrSize);

		std::cout << "Before:      ";
		for (std::deque<PmergeMe::Int>::iterator it = deq.begin(); it != deq.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		std::clock_t start = std::clock();
		std::sort(deq.begin(), deq.end());
		std::clock_t end = std::clock();

		std::cout << "After:       ";
		for (std::deque<PmergeMe::Int>::iterator it = deq.begin(); it != deq.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << std::fixed << std::setprecision(6);
		double timer = static_cast<double>(end - start) / CLOCKS_PER_SEC;

		std::cout << "Size:        " << deq.size() << std::endl;
		std::cout << "Time:        " << timer << std::endl;
		std::cout << "Comparisons: " << PmergeMe::Int::nComps << std::endl;
	}
}

void	testDequeSortFourNumbers(std::size_t testIndex)
{
	PP_TEST(testIndex);
	int arr[] = {
		2, 1, 3, 4
	};
	std::size_t arrSize = sizeof(arr) / sizeof(arr[0]);

	PmergeMe pm;

	{
		std::cout << "MergeInsertion Sort" << std::endl;
		PmergeMe::Int::nComps = 0;
		std::deque<int> deq(arr, arr + arrSize);

		std::cout << "Before:      ";
		for (std::deque<int>::iterator it = deq.begin(); it != deq.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		pm.sort(deq);
		std::cout << std::fixed << std::setprecision(6);

		std::cout << "After:       ";
		for (std::deque<int>::iterator it = deq.begin(); it != deq.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << "Size:        " << deq.size() << std::endl;
		std::cout << "Time:        " << pm.getTimer() << std::endl;
		std::cout << "Comparisons: " << PmergeMe::Int::nComps << std::endl;
	}

	{
		std::cout << "Builtin Sort" << std::endl;
		PmergeMe::Int::nComps = 0;
		std::deque<PmergeMe::Int> deq(arr, arr + arrSize);

		std::cout << "Before:      ";
		for (std::deque<PmergeMe::Int>::iterator it = deq.begin(); it != deq.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		std::clock_t start = std::clock();
		std::sort(deq.begin(), deq.end());
		std::clock_t end = std::clock();

		std::cout << "After:       ";
		for (std::deque<PmergeMe::Int>::iterator it = deq.begin(); it != deq.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << std::fixed << std::setprecision(6);
		double timer = static_cast<double>(end - start) / CLOCKS_PER_SEC;

		std::cout << "Size:        " << deq.size() << std::endl;
		std::cout << "Time:        " << timer << std::endl;
		std::cout << "Comparisons: " << PmergeMe::Int::nComps << std::endl;
	}
}

void	testDequeSortFiveNumbers(std::size_t testIndex)
{
	PP_TEST(testIndex);
	int arr[] = {
		2, 1, 5, 3, 4
	};
	std::size_t arrSize = sizeof(arr) / sizeof(arr[0]);

	PmergeMe pm;

	{
		std::cout << "MergeInsertion Sort" << std::endl;
		PmergeMe::Int::nComps = 0;
		std::deque<int> deq(arr, arr + arrSize);

		std::cout << "Before:      ";
		for (std::deque<int>::iterator it = deq.begin(); it != deq.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		pm.sort(deq);
		std::cout << std::fixed << std::setprecision(6);

		std::cout << "After:       ";
		for (std::deque<int>::iterator it = deq.begin(); it != deq.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << "Size:        " << deq.size() << std::endl;
		std::cout << "Time:        " << pm.getTimer() << std::endl;
		std::cout << "Comparisons: " << PmergeMe::Int::nComps << std::endl;
	}

	{
		std::cout << "Builtin Sort" << std::endl;
		PmergeMe::Int::nComps = 0;
		std::deque<PmergeMe::Int> deq(arr, arr + arrSize);

		std::cout << "Before:      ";
		for (std::deque<PmergeMe::Int>::iterator it = deq.begin(); it != deq.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		std::clock_t start = std::clock();
		std::sort(deq.begin(), deq.end());
		std::clock_t end = std::clock();

		std::cout << "After:       ";
		for (std::deque<PmergeMe::Int>::iterator it = deq.begin(); it != deq.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << std::fixed << std::setprecision(6);
		double timer = static_cast<double>(end - start) / CLOCKS_PER_SEC;

		std::cout << "Size:        " << deq.size() << std::endl;
		std::cout << "Time:        " << timer << std::endl;
		std::cout << "Comparisons: " << PmergeMe::Int::nComps << std::endl;
	}
}

void	testDequeSortTenNumbers(std::size_t testIndex)
{
	PP_TEST(testIndex);
	int arr[] = {
		5, 7, 10, 9, 8, 6, 4, 3, 2, 1
	};
	std::size_t arrSize = sizeof(arr) / sizeof(arr[0]);

	PmergeMe pm;

	{
		std::cout << "MergeInsertion Sort" << std::endl;
		PmergeMe::Int::nComps = 0;
		std::deque<int> deq(arr, arr + arrSize);

		std::cout << "Before:      ";
		for (std::deque<int>::iterator it = deq.begin(); it != deq.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		pm.sort(deq);
		std::cout << std::fixed << std::setprecision(6);

		std::cout << "After:       ";
		for (std::deque<int>::iterator it = deq.begin(); it != deq.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << "Size:        " << deq.size() << std::endl;
		std::cout << "Time:        " << pm.getTimer() << std::endl;
		std::cout << "Comparisons: " << PmergeMe::Int::nComps << std::endl;
	}

	{
		std::cout << "Builtin Sort" << std::endl;
		PmergeMe::Int::nComps = 0;
		std::deque<PmergeMe::Int> deq(arr, arr + arrSize);

		std::cout << "Before:      ";
		for (std::deque<PmergeMe::Int>::iterator it = deq.begin(); it != deq.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		std::clock_t start = std::clock();
		std::sort(deq.begin(), deq.end());
		std::clock_t end = std::clock();

		std::cout << "After:       ";
		for (std::deque<PmergeMe::Int>::iterator it = deq.begin(); it != deq.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << std::fixed << std::setprecision(6);
		double timer = static_cast<double>(end - start) / CLOCKS_PER_SEC;

		std::cout << "Size:        " << deq.size() << std::endl;
		std::cout << "Time:        " << timer << std::endl;
		std::cout << "Comparisons: " << PmergeMe::Int::nComps << std::endl;
	}
}

void	testDequeSortThreeThousandNumbers(std::size_t testIndex)
{
	PP_TEST(testIndex);
	int arr[] = {
		3059, 6271, 8138, 5961, 3782, 306, 6649, 2339, 3665, 6360, 6555, 8214, 4328, 9306, 5625, 7854, 193, 2052, 3361, 4995, 1922, 487, 9105, 8208, 317, 7990, 3540, 4921, 4417, 7616, 6988, 2113, 7599, 6065, 4148, 3680, 2120, 6307, 9522, 6827, 8445, 622, 8597, 2618, 3712, 2577, 8991, 6067, 2678, 7323, 8741, 9080, 3302, 3555, 2705, 5954, 6962, 6562, 3874, 8512, 9721, 551, 3051, 7258, 3633, 6477, 2182, 2738, 153, 110, 4786, 2225, 4679, 2349, 35, 1484, 6467, 9922, 6300, 9954, 6766, 4502, 7694, 2163, 1344, 7414, 5569, 4700, 8634, 1739, 6264, 8206, 1424, 9406, 3180, 3723, 5619, 3177, 2554, 1814, 7571, 186, 3582, 9898, 1523, 4782, 3159, 835, 4134, 534, 811, 9738, 8270, 9231, 209, 2877, 4353, 1659, 4072, 2542, 3559, 1810, 9807, 2480, 6519, 4209, 3383, 6296, 7695, 3617, 1944, 8631, 2154, 9112, 9166, 9521, 4277, 4466, 6100, 4314, 7584, 9317, 7171, 1581, 8864, 1486, 710, 5494, 7845, 124, 359, 8411, 2155, 5151, 1809, 9865, 6038, 2578, 1871, 4144, 2012, 2785, 769, 8678, 5804, 3247, 2177, 5570, 3848, 3484, 8227, 5237, 3011, 8122, 1782, 5240, 2510, 3961, 5617, 7480, 3726, 7970, 9412, 247, 1829, 1699, 9005, 6883, 7397, 1789, 5733, 5000, 1413, 8865, 1849, 7482, 9623, 1061, 5023, 5716, 7552, 6835, 7913, 4911, 2166, 1976, 6698, 759, 5239, 327, 755, 5638, 8855, 2917, 4120, 1924, 2169, 3751, 4075, 2408, 7063, 6553, 8918, 9361, 2811, 6537, 7526, 653, 4916, 1816, 3351, 4536, 2624, 8376, 2411, 2793, 7320, 4925, 4648, 1729, 1042, 8877, 6061, 5567, 958, 6552, 2385, 5763, 3280, 3404, 5732, 1734, 6309, 800, 8913, 426, 2938, 2893, 7448, 2736, 8113, 6337, 5191, 7489, 4156, 9761, 6334, 7995, 9258, 233, 8489, 3160, 9218, 5094, 8885, 5449, 895, 8775, 3463, 450, 4776, 4380, 7443, 3130, 3586, 4374, 1072, 744, 3832, 7896, 2523, 5100, 7365, 1725, 1831, 2309, 2159, 1473, 7903, 8450, 8737, 6156, 5989, 6627, 7311, 4868, 9439, 9708, 2204, 2454, 365, 8464, 6008, 3960, 5680, 8163, 713, 1740, 2085, 6667, 2753, 7160, 3941, 6610, 3631, 1537, 4680, 9132, 8487, 8738, 8514, 4661, 8439, 1395, 3892, 2901, 4510, 2452, 5436, 6850, 2606, 7328, 132, 854, 4955, 3763, 9023, 9962, 1968, 216, 9282, 6492, 9390, 9223, 5004, 1437, 4567, 2011, 8852, 7690, 8785, 4627, 4714, 7834, 1101, 5875, 6703, 7343, 6822, 3483, 7602, 2190, 1187, 6723, 1314, 3858, 8070, 4389, 7265, 5681, 4465, 8006, 9660, 6540, 8739, 7439, 9838, 8986, 9504, 2498, 7802, 2272, 7943, 8404, 1131, 1195, 7252, 6821, 4823, 6210, 9880, 6092, 3420, 789, 5212, 4385, 4238, 5157, 8819, 4555, 3676, 3350, 9728, 8187, 6783, 467, 4221, 389, 9477, 3619, 8075, 3523, 2746, 9048, 6725, 1910, 385, 9494, 6011, 1352, 7952, 9382, 3050, 986, 4706, 2548, 4669, 1981, 2071, 3687, 3002, 1275, 2966, 2392, 1526, 1568, 5575, 9843, 4415, 5572, 5613, 4666, 5061, 4611, 8860, 4546, 1283, 767, 24, 6076, 9851, 2869, 1610, 7190, 5492, 8517, 3150, 5555, 4285, 5601, 4844, 8174, 2794, 3436, 4160, 9827, 3797, 220, 1671, 9385, 7399, 7550, 5996, 620, 3321, 1677, 9489, 8413, 5262, 9544, 9965, 7918, 1966, 4917, 3403, 4815, 1450, 7762, 8533, 8682, 1583, 3611, 9141, 2275, 1674, 6459, 4713, 3437, 989, 9163, 4294, 9460, 2056, 1112, 3982, 8022, 1614, 8140, 832, 9408, 5159, 4860, 3122, 9037, 7402, 213, 4431, 985, 7009, 454, 8289, 2571, 9085, 5051, 820, 2333, 4387, 2263, 8204, 9492, 6024, 8194, 2377, 6246, 2040, 7053, 6747, 3962, 5223, 4943, 7708, 5538, 957, 6189, 483, 5092, 1770, 3342, 6913, 6891, 2940, 9753, 1854, 619, 9688, 8222, 9633, 9473, 7976, 8652, 5192, 6472, 4612, 6225, 2395, 9548, 506, 4514, 3809, 41, 4733, 8716, 7147, 5772, 7730, 8410, 905, 7094, 6596, 6396, 1097, 5077, 1092, 9526, 7639, 7546, 2889, 6848, 1479, 9162, 4773, 9358, 7458, 7174, 3811, 6111, 1802, 4684, 4141, 3861, 5929, 2239, 6879, 1914, 3080, 3902, 3291, 7681, 4801, 7937, 954, 257, 9096, 8977, 4885, 9736, 4799, 8089, 5895, 4620, 4990, 1034, 3514, 3537, 13, 641, 6048, 9746, 202, 2456, 4102, 8635, 3013, 562, 4607, 8200, 1268, 9081, 2046, 2131, 5195, 4045, 4753, 1632, 7815, 7851, 6965, 8810, 1493, 2780, 2504, 6118, 263, 3274, 5298, 9911, 7339, 4725, 2865, 5347, 7644, 451, 3303, 6648, 4673, 3841, 9097, 3814, 5442, 3457, 740, 7860, 126, 6880, 4360, 2274, 7031, 6936, 5950, 793, 9158, 818, 4507, 7789, 3181, 488, 5009, 3344, 7225, 7085, 9220, 2035, 7222, 5591, 5371, 3108, 1383, 7548, 5447, 3986, 6630, 8526, 1630, 214, 5445, 3765, 7906, 9854, 643, 5426, 7917, 3315, 5133, 4250, 4473, 3346, 8016, 3749, 7412, 2913, 4096, 7832, 6478, 8836, 9824, 1609, 1783, 8144, 7333, 9508, 5735, 5688, 7518, 9629, 8857, 7981, 7345, 7472, 4245, 4112, 6281, 667, 9939, 530, 6190, 4690, 6700, 1835, 7676, 58, 5956, 7359, 2356, 628, 6260, 6796, 6208, 9344, 9866, 6756, 5269, 2280, 858, 865, 3910, 4549, 7862, 6967, 8331, 57, 7972, 995, 1986, 5219, 5987, 553, 6355, 1198, 955, 7543, 4715, 9777, 6200, 9776, 7812, 2672, 4354, 1135, 7143, 774, 8403, 5119, 5535, 4609, 8521, 1639, 4063, 16, 6352, 1658, 9487, 6465, 1548, 5963, 7004, 6775, 7583, 9000, 3802, 6577, 6861, 9989, 5805, 2789, 4028, 6753, 8360, 4154, 6689, 174, 8501, 6604, 8007, 9822, 6733, 148, 9127, 7185, 2714, 6012, 8198, 9357, 6759, 1612, 7296, 378, 3380, 5943, 2858, 1994, 4802, 3800, 972, 8770, 7478, 6672, 9529, 8306, 6403, 9226, 9793, 2387, 2513, 3963, 8954, 3116, 4694, 32, 6020, 4230, 9088, 6707, 933, 671, 9711, 2549, 9978, 1563, 5460, 210, 4418, 4566, 7936, 222, 9975, 2588, 3999, 3717, 9149, 7779, 3502, 4196, 5453, 1950, 7649, 2765, 9917, 9301, 4488, 883, 4987, 6347, 6740, 636, 4312, 3113, 2146, 6888, 99, 761, 4482, 4701, 2574, 4300, 2332, 4500, 6220, 7634, 8417, 9024, 4450, 8959, 9198, 9648, 542, 7501, 4790, 4902, 4499, 6785, 4827, 6241, 2607, 9103, 5632, 2162, 9588, 4190, 5823, 8578, 6149, 9971, 6466, 3744, 3643, 517, 3632, 4162, 7325, 1459, 6042, 549, 1881, 4908, 8320, 2347, 8049, 3048, 919, 4832, 5850, 1087, 7404, 1117, 3791, 7959, 3852, 1506, 6676, 8246, 3666, 891, 7259, 3905, 5467, 531, 7058, 5652, 9147, 7580, 2218, 5917, 4830, 3254, 286, 1173, 4188, 224, 7182, 6221, 168, 3095, 1175, 932, 2681, 3608, 8582, 2743, 5121, 3142, 8374, 6621, 7919, 6809, 2561, 5614, 9545, 1031, 391, 131, 3377, 3262, 5425, 1255, 9611, 8468, 8039, 7406, 9225, 5380, 2804, 2902, 815, 2051, 8599, 4044, 5560, 2932, 9353, 376, 7018, 4674, 151, 3472, 3100, 3790, 2466, 3783, 6326, 6767, 8751, 4915, 9339, 1154, 3992, 7785, 135, 9152, 2373, 3898, 1161, 571, 5256, 6242, 6970, 4968, 9179, 7340, 434, 8657, 4183, 9891, 8618, 8253, 235, 5306, 2976, 2543, 999, 1046, 5251, 8493, 1137, 5749, 1851, 6545, 8724, 6590, 845, 9752, 8023, 2201, 686, 7169, 9386, 9126, 1204, 4928, 8870, 1083, 6344, 3638, 7, 821, 7368, 6815, 206, 1448, 5479, 6379, 1419, 695, 6586, 1337, 7256, 9619, 1289, 6028, 8472, 1631, 1586, 8276, 9640, 7707, 9695, 8664, 2947, 9430, 2380, 1576, 6572, 8881, 8008, 2245, 2171, 3615, 5992, 5020, 2258, 1005, 556, 2132, 1897, 2129, 2995, 6182, 4284, 2122, 5170, 3720, 241, 7096, 4932, 7737, 5991, 607, 608, 6705, 7271, 7116, 8019, 3200, 3950, 1466, 7042, 9584, 9100, 4877, 9608, 9488, 4176, 3845, 8898, 1665, 9914, 4397, 8157, 3476, 4165, 4972, 629, 6093, 2400, 5730, 2473, 8831, 4898, 9779, 9773, 6164, 1533, 2070, 2491, 8252, 6933, 1792, 2412, 515, 8054, 4878, 22, 5393, 682, 3836, 9552, 9737, 4049, 4246, 3746, 523, 3372, 7212, 4919, 6702, 4438, 8809, 7168, 3622, 3563, 5165, 2847, 4350, 9596, 2635, 642, 4082, 4521, 61, 2828, 3473, 828, 6780, 1339, 9674, 9403, 2700, 3817, 6289, 5171, 1026, 8173, 9084, 1366, 9560, 6832, 9751, 4887, 2254, 8257, 1379, 8486, 9510, 318, 1436, 6399, 9567, 1207, 4271, 1558, 7224, 3598, 4269, 5620, 2894, 7755, 8938, 3921, 8976, 997, 43, 7833, 6882, 8114, 49, 6179, 3014, 5500, 6001, 5430, 7671, 7077, 2435, 1982, 1274, 7502, 7393, 7908, 3034, 6971, 795, 3819, 4865, 4365, 5440, 8912, 7878, 4098, 4681, 9240, 7823, 8766, 5967, 1248, 7134, 5131, 4712, 4542, 6313, 8386, 8789, 9304, 4347, 6989, 5815, 9659, 645, 1819, 4848, 5658, 8355, 7124, 3000, 9577, 586, 2710, 5283, 1445, 217, 2107, 9422, 393, 5977, 3421, 8594, 4769, 1369, 2101, 4857, 2293, 7984, 6235, 4122, 6139, 5095, 1063, 3127, 2989, 244, 3908, 4704, 8801, 9320, 2846, 6746, 1007, 4060, 4123, 4150, 1891, 2860, 7280, 8609, 3628, 7643, 4373, 6132, 8462, 9067, 9065, 9638, 934, 7509, 6278, 1985, 3864, 2751, 9369, 9499, 564, 8178, 172, 6310, 5883, 2017, 4890, 2002, 3354, 4647, 949, 8722, 7084, 8725, 6121, 3400, 1785, 8776, 7192, 3278, 5039, 5081, 316, 405, 6074, 7065, 3694, 297, 4187, 5252, 5871, 7055, 3501, 3229, 9343, 6055, 676, 7656, 2767, 5319, 6600, 6905, 1528, 8266, 3621, 8073, 4351, 1778, 625, 6249, 5584, 778, 8916, 6462, 7234, 6014, 2620, 2983, 1717, 3822, 6916, 6032, 730, 4791, 7269, 7503, 6765, 5901, 3596, 2980, 4066, 1867, 3031, 5580, 4539, 5162, 1478, 3572, 5462, 80, 2091, 1979, 1970, 2975, 7307, 9183, 1517, 6961, 7701, 1800, 4202, 1678, 2559, 9533, 5879, 5079, 1232, 164, 6942, 6144, 3434, 7044, 2969, 3187, 1367, 2111, 1650, 9360, 4525, 4644, 9283, 1002, 2615, 7891, 4279, 2520, 4825, 4922, 963, 6097, 3272, 3799, 4342, 6808, 2158, 9, 6894, 2092, 909, 4849, 7367, 3094, 6834, 267, 7187, 3881, 5561, 965, 3515, 5224, 1923, 8837, 2047, 1032, 2617, 9905, 3590, 9170, 9762, 8917, 7315, 1852, 7156, 3641, 7100, 6369, 5756, 4760, 472, 4794, 3648, 293, 4332, 773, 8730, 2599, 7922, 9454, 6217, 786, 6598, 7284, 9654, 4975, 9315, 9966, 8443, 5066, 9234, 8608, 1904, 817, 9527, 5720, 9266, 7715, 5175, 4515, 9331, 7733, 6743, 8224, 5253, 4642, 8155, 5966, 3109, 7372, 6057, 9820, 3599, 4366, 4688, 1368, 2414, 5773, 5969, 4424, 6231, 6143, 6764, 4453, 541, 7395, 4213, 3995, 2020, 3867, 7484, 9626, 5552, 7465, 5358, 6397, 661, 3786, 5144, 6635, 1023, 3265, 3256, 5402, 9060, 874, 5105, 2508, 2613, 2114, 9188, 7675, 9605, 3674, 3015, 1170, 300, 4215, 52, 3914, 6897, 7535, 4311, 3307, 5148, 7130, 6718, 6978, 1225, 7446, 2478, 6772, 8568, 912, 2937, 8408, 5071, 1622, 6077, 3464, 1410, 1230, 5790, 7196, 6317, 170, 4837, 1125, 5238, 8041, 5208, 8999, 1571, 2014, 7388, 9802, 918, 6248, 1895, 5033, 7181, 9800, 1332, 6597, 758, 8389, 100, 2691, 6727, 9813, 6059, 105, 5177, 6173, 3244, 3803, 9490, 3711, 4621, 5660, 1115, 3338, 5907, 5428, 1578, 3191, 1653, 9043, 6160, 6215, 5526, 8850, 668, 2283, 9921, 372, 2525, 2802, 1315, 1085, 3238, 2539, 5653, 9495, 2663, 1763, 9173, 7895, 500, 4882, 8455, 3326, 2375, 8333, 8895, 5761, 10, 5528, 5607, 3194, 1539, 3012, 5375, 6104, 3719, 3170, 2627, 2042, 3558, 6669, 1633, 4407, 8344, 787, 1205, 7081, 8650, 3856, 5403, 5541, 6298, 5194, 1661, 1917, 5611, 8981, 6593, 4699, 851, 4903, 798, 3243, 7049, 8422, 6345, 8676, 577, 8698, 4469, 8255, 9134, 1350, 2396, 9734, 528, 7385, 8805, 8192, 4874, 2658, 2956, 3075, 9434, 266, 2144, 4632, 6069, 3367, 7183, 9211, 5450, 5687, 8589, 1926, 7961, 6203, 2079, 9119, 7302, 6752, 5594, 4371, 3395, 4923, 9606, 3550, 7074, 7273, 5698, 1728, 554, 8310, 9334, 5049, 2779, 8158, 1291, 6297, 115, 6675, 46, 1954, 3571, 5962, 5742, 7008, 1952, 1391, 7749, 6125, 4395, 6867, 7577, 2142, 7140, 4651, 3618, 3739, 2455, 5602, 8094, 8399, 7511, 6244, 3662, 3296, 7310, 8205, 95, 887, 4936, 584, 1491, 3917, 2016, 5015, 9217, 1695, 939, 4340, 8791, 7193, 971, 8014, 3089, 546, 6116, 3983, 3863, 1641, 4376, 2093, 4935, 6254, 7392, 8111, 6791, 6889, 3304, 1868, 4655, 6187, 7820, 6408, 6488, 1620, 8735, 1048, 2823, 8382, 9515, 3842, 2492, 6437, 6973, 9755, 9036, 6987, 5138, 5744, 6385, 9908, 8793, 6570, 5242, 6041, 3745, 7680, 8612, 2420, 8552, 3155, 2764, 6612, 5593, 9122, 4372, 7034, 9771, 8046, 6479, 1057, 8816, 3844, 1750, 4841, 187, 8308, 5301, 4074, 6995, 6475, 9698, 1832, 1231, 1041, 5808, 7021, 9345, 8164, 5705, 8165, 9685, 7778, 6159, 6800, 9636, 5655, 2232, 8195, 5852, 229, 1737, 6509, 1555, 3115, 1296, 4022, 3651, 4443, 5012, 9952, 9274, 5080, 3285, 8296, 7868, 4532, 6324, 7811, 3266, 4962, 2364, 5055, 6106, 8396, 7873, 7805, 2622, 1082, 9710, 2073, 3263, 2112, 9546, 9683, 2723, 9995, 312, 910, 2394, 812, 8867, 8390, 1303, 8437, 2393, 5502, 2727, 3165, 2977, 2715, 8679, 7045, 1948, 7415, 4738, 74, 4048, 7228, 7250, 715, 3549, 4331, 8760, 4258, 1973, 7477, 3626, 5040, 8299, 6040, 1124, 5830, 3417, 6691, 6730, 8869, 4186, 260, 3513, 9224, 7830, 8071, 9607, 2836, 8798, 2267, 9082, 4359, 3701, 1490, 3477, 9305, 1389, 9066, 3870, 8086, 1420, 5351, 2036, 9378, 4191, 8915, 2660, 7411, 8565, 8000, 6406, 8997, 6429, 5982, 6280, 9576, 8495, 8366, 1644, 6826, 9243, 663, 2801, 1546, 5893, 3073, 5336, 9327, 7199, 1396, 2481, 4742, 2416, 1691, 3330, 1488, 4969, 7206, 8419, 3210, 2758, 6286, 4220, 4472, 6957, 5837, 1433, 8706, 3221, 5437, 1997, 2350, 1963, 4267, 2497, 8784, 3072, 1406, 2739, 9253, 2556, 5902, 5851, 3532, 2752, 1885, 882, 8309, 4767, 6120, 9687, 3579, 8161, 8265, 4626, 9610, 1355, 3275, 8130, 9462, 2984, 2685, 6681, 5791, 8500, 4214, 1759, 4544, 5011, 9594, 2076, 8649, 2863, 698, 8287, 9069, 906, 6426, 5568, 7389, 3663, 5106, 6391, 3931, 856, 8559, 8525, 2358, 6868, 1239, 4041, 3524, 5337, 2084, 3174, 2558, 199, 5295, 8203, 9671, 1877, 3732, 6857, 762, 1462, 8465, 1267, 3077, 8615, 1322, 5116, 9787, 9562, 8461, 6022, 7888, 9381, 1273, 990, 3427, 9148, 3270, 2226, 6599, 4318, 2363, 6442, 3224, 9445, 7337, 7073, 7763, 1374, 810, 8998, 7828, 1607, 6646, 7457, 6270, 9876, 5564, 1261, 1335, 249, 6849, 5818, 36, 4640, 207, 2389, 5695, 4364, 7139, 2677, 2413, 101, 7263, 4850, 4999, 272, 4032, 1860, 7620, 9798, 3547, 5665, 1712, 2730, 2050, 4127, 3980, 4592, 1795, 6230, 5362, 3511, 2630, 3409, 6357, 7043, 6844, 849, 3196, 4116, 1958, 4840, 8328, 8482, 8980, 5741, 8024, 6873, 8680, 3419, 5626, 9852, 8924, 8808, 50, 3153, 8416, 9591, 1327, 2161, 8899, 7910, 7724, 4050, 2517, 4222, 8369, 3700, 8813, 3171, 7318, 6603, 1133, 7920, 5510, 5740, 3601, 609, 8447, 6206, 9340, 9681, 6272, 9677, 5431, 2729, 1663, 223, 4891, 9049, 3645, 9609, 9970, 7567, 6054, 7973, 6291, 1787, 282, 5679, 5885, 3829, 5524, 7925, 3474, 5146, 5124, 3492, 7698, 3076, 9895, 8373, 3734, 1700, 3862, 2978, 6395, 1524, 3685, 3503, 1153, 8823, 2215, 4746, 8902, 1138, 137, 8011, 7980, 5924, 1500, 9203, 4839, 8146, 2666, 9246, 121, 2472, 9587, 490, 8572, 8438, 7957, 7561, 980, 4762, 6303, 3442, 6632, 9924, 1980, 1019, 5378, 4896, 4686, 4831, 7235, 5296, 4004, 5624, 3246, 8045, 7264, 460, 511, 3682, 208, 5829, 7075, 8587, 9095, 3728, 5297, 725, 2440, 9174, 6813, 9008, 4388, 7114, 4410, 2638, 2136, 1669, 9568, 3022, 4189, 4793, 1306, 1702, 7894, 6451, 8076, 2864, 6589, 9679, 158, 298, 332, 238, 2535, 5531, 8463, 8062, 8168, 8108, 8101, 3789, 2170, 707, 4892, 1189, 6890, 370, 5753, 8221, 635, 5673, 4071, 4575, 5586, 2176, 5562, 7421, 27, 9261, 8233, 1853, 1595, 2446, 8556, 7285, 8658, 5097, 1372, 9680, 2353, 1510, 1326, 3565, 4173, 9129, 1310, 5084, 4615, 8845, 9647, 7060, 5540, 4302, 432, 9117, 388, 6946, 897, 1052, 2911, 3408, 7135, 7849, 3507, 9332, 4323, 6576, 480, 1956, 5415, 3656, 5677, 280, 4560, 3834, 212, 7559, 2933, 2453, 5563, 1353, 9661, 3580, 447, 3443, 3039, 1873, 2625, 880, 6919, 6768, 9501, 1323, 9974, 5145, 203, 5126, 1903, 5168, 1535, 8350, 6619, 2424, 6062, 8212, 4143, 1780, 1590, 7723, 4197, 478, 5400, 7655, 6274, 6034, 2043, 9990, 3237, 765, 371, 7029, 2965, 9706, 5792, 3481, 5737, 2761, 9955, 7260, 7494, 4571, 5491, 8908, 4739, 1235, 9897, 9102, 2516, 2439, 1015, 8888, 7313, 7197, 9461, 8936, 1330, 5717, 6636, 6869, 931, 9701, 3518, 3104, 6, 5227, 7531, 7529, 3252, 7593, 3733, 2331, 2560, 7967, 8889, 7632, 5489, 2629, 9902, 2494, 1107, 3005, 8520, 2010, 9583, 6112, 638, 4998, 782, 3459, 8726, 228, 1738, 3667, 5211, 4614, 2968, 141, 1467, 5091, 7964, 6650, 3378, 9524, 9298, 6720, 330, 9288, 7794, 4151, 4913, 3769, 3894, 1311, 6113, 8027, 3613, 5074, 2343, 4088, 163, 9468, 3839, 7390, 3967, 5872, 4025, 6151, 2756, 7495, 2214, 5603, 7841, 8250, 711, 9428, 7971, 3707, 1089, 6609, 8121, 2922, 9702, 2186, 5839, 572, 4982, 8047, 6952, 6080, 9478, 1617, 7679, 5868, 8381, 1530, 7932, 4168, 4811, 6083, 7809, 3145, 2391, 25, 3258, 2033, 9781, 5448, 424, 2720, 6405, 915, 5750, 9104, 8312, 3542, 9767, 2117, 7374, 5662, 9780, 2759, 5949, 4492, 2078, 2386, 9145, 8069, 9028, 2707, 9393, 3509, 7876, 9140, 9641, 5796, 1, 9620, 1848, 592, 8220, 3161, 875, 386, 9467, 8379, 2773, 5102, 4325, 9392, 6114, 156, 2288, 819, 5968, 5263, 6469, 1358, 2694, 6305, 9864, 3381, 3830, 8316, 8474, 9812, 2733, 1094, 421, 3588, 8291, 7587, 3352, 4894, 3730, 3021, 1284, 1176, 1693, 9115, 4155, 6198, 7614, 7369, 6358, 5024, 5385, 2999, 7797, 1155, 5832, 5141, 9493, 8569, 2994, 3129, 9273, 2266, 65, 2096, 6009, 699, 2762, 4280, 4090, 279, 2820, 3027, 1305, 2277, 9172, 3331, 9351, 4362, 254, 9464, 3794, 8332, 4731, 192, 7847, 23, 2514, 5697, 3117, 8930, 2526, 5246, 9789, 8692, 1025, 7204, 5043, 3182, 1229, 9486, 9297, 7059, 6523, 2213, 3846, 746, 3773, 8367, 9920, 9015, 75, 8987, 8151, 4181, 3032, 7564, 8240, 1439, 1055, 8353, 1403, 8685, 2202, 4863, 7960, 3798, 9982, 9774, 2183, 4006, 1030, 3940, 9894, 5529, 5130, 6261, 5684, 1696, 2536, 7221, 7752, 8665, 4324, 876, 9031, 6240, 7238, 9500, 6378, 6794, 5887, 797, 92, 184, 3750, 8456, 2335, 9484, 1996, 4629, 9341, 5781, 6075, 6096, 1145, 9167, 6605, 1243, 5443, 103, 633, 1627, 7382, 471, 7418, 9644, 5627, 6145, 2125, 8470, 7668, 5802, 2360, 8459, 3915, 4964, 5003, 7232, 2118, 9801, 7378, 8145, 2019, 1575, 7079, 1074, 17, 5250, 7052, 2665, 675, 6370, 7405, 5719, 6374, 827, 5059, 6997, 6029, 9778, 7814, 4243, 6257, 4241, 3286, 8067, 5087, 3311, 2284, 8103, 7754, 2611, 8928, 9634, 5861, 1163, 4447, 2711, 6719, 2150, 4633, 73, 4458, 3604, 6015, 4357, 8394, 8268, 8102, 4256, 7646, 4508, 9459, 9936, 3517, 7117, 6482, 9509, 2659, 9630, 3993, 499, 4108, 8641, 1236, 2415, 1746, 3016, 4524, 2298, 621, 805, 2327, 7473, 8473, 2126, 4683, 9018, 5068, 4977, 9227, 5349, 1604, 1998, 5646, 4755, 5892, 6453, 9034, 1262, 5635, 8494, 3328, 3838, 7092, 6239, 5533, 1241, 2376, 3480, 8115, 8377, 8325, 6398, 2269, 9202, 1222, 5911, 8557, 1249, 9086, 1465, 15, 8311, 2726, 45, 2950, 5112, 7066, 4232, 9259, 5294, 2023, 4219, 6631, 7512, 8083, 8506, 7710
	};
	std::size_t arrSize = sizeof(arr) / sizeof(arr[0]);

	PmergeMe pm;

	{
		std::cout << "MergeInsertion Sort" << std::endl;
		PmergeMe::Int::nComps = 0;
		std::deque<int> deq(arr, arr + arrSize);

		std::cout << "Before:      ";
		for (std::deque<int>::iterator it = deq.begin(); it != deq.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		pm.sort(deq);
		std::cout << std::fixed << std::setprecision(6);

		std::cout << "After:       ";
		for (std::deque<int>::iterator it = deq.begin(); it != deq.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << "Size:        " << deq.size() << std::endl;
		std::cout << "Time:        " << pm.getTimer() << std::endl;
		std::cout << "Comparisons: " << PmergeMe::Int::nComps << std::endl;
	}

	{
		std::cout << "Builtin Sort" << std::endl;
		PmergeMe::Int::nComps = 0;
		std::deque<PmergeMe::Int> deq(arr, arr + arrSize);

		std::cout << "Before:      ";
		for (std::deque<PmergeMe::Int>::iterator it = deq.begin(); it != deq.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		std::clock_t start = std::clock();
		std::sort(deq.begin(), deq.end());
		std::clock_t end = std::clock();

		std::cout << "After:       ";
		for (std::deque<PmergeMe::Int>::iterator it = deq.begin(); it != deq.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << std::fixed << std::setprecision(6);
		double timer = static_cast<double>(end - start) / CLOCKS_PER_SEC;

		std::cout << "Size:        " << deq.size() << std::endl;
		std::cout << "Time:        " << timer << std::endl;
		std::cout << "Comparisons: " << PmergeMe::Int::nComps << std::endl;
	}
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " NUMBERS..." << std::endl;
		return (1);
	}

	std::size_t testIndex = 0;

	std::string input;
	for (int i = 1; i < argc; ++i)
	{
		input += argv[i];
		input += " ";
	}

	try
	{
		std::vector<int> v = PmergeMe::getVectorFromInput(input);
		testVectorSortFromParameters(testIndex++, v);
	}
	catch (const std::exception& e)
	{
		PP_EXCEPTION(e);
	}

	testVectorSortEmptyVector(testIndex++);
	testVectorSortOneNumber(testIndex++);
	testVectorSortTwoNumbers(testIndex++);
	testVectorSortThreeNumbers(testIndex++);
	testVectorSortFourNumbers(testIndex++);
	testVectorSortFiveNumbers(testIndex++);
	testVectorSortTenNumbers(testIndex++);
	testVectorSortThreeThousandNumbers(testIndex++);

	testDequeSortEmptyDeque(testIndex++);
	testDequeSortOneNumber(testIndex++);
	testDequeSortTwoNumbers(testIndex++);
	testDequeSortThreeNumbers(testIndex++);
	testDequeSortFourNumbers(testIndex++);
	testDequeSortFiveNumbers(testIndex++);
	testDequeSortTenNumbers(testIndex++);
	testDequeSortThreeThousandNumbers(testIndex++);

	return (0);
}
