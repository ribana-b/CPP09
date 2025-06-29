/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:32:08 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2025/06/29 07:14:13 by ribana-b         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <algorithm>	// For std::upper_bound
#include <iostream>		// For std::cout
#include <limits>		// For std::numeric_limits
#include <vector>		// For std::vector
#include <deque>		// For std::deque
#include <ctime>		// For std::clock_t, std::clock
#include <sstream>		// For std::stringstream

// Helper macro to turn off OCF messages
#ifdef QUIET
# define OCF_MESSAGE(X)
#else
# define OCF_MESSAGE(X) std::cout << (X) << std::endl
#endif

//#include <cmath>
//#define JACOBSTHAL_FORMULA(X) static_cast<std::size_t>(round((pow(2, (X) + 1) + pow(-1, (X))) / 3))

// Precalculated numbers using Jacobsthal formula, limited to X = 32 because
// the value is greater than MAX_INT (2147483647)
const std::size_t JACOBSTHAL_NUMBERS[] = {
	1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 10923, 21845,
	43691, 87381, 174763, 349525, 699051, 1398101, 2796203, 5592405, 11184811,
	22369621, 44739243, 89478485, 178956971, 357913941, 715827883, 1431655765,
	2863311531,
};
const std::size_t JACOBSTHAL_NUMBERS_SIZE = sizeof(JACOBSTHAL_NUMBERS) / sizeof(*JACOBSTHAL_NUMBERS);

PmergeMe::PmergeMe() :
	m_IsTimerFlagSet(true),
	m_Timer(0)
{
	OCF_MESSAGE("PmergeMe Default constructor called");
}

PmergeMe::~PmergeMe()
{
	OCF_MESSAGE("PmergeMe Destructor called");
}

PmergeMe::PmergeMe(const PmergeMe&)
{
	OCF_MESSAGE("PmergeMe Copy constructor called");
}

PmergeMe&	PmergeMe::operator=(const PmergeMe& that)
{
	OCF_MESSAGE("PmergeMe Assignment operator called");

	if (this != &that)
	{
		m_IsTimerFlagSet = that.m_IsTimerFlagSet;
		m_Timer = that.m_Timer;
	}

	return (*this);
}

bool PmergeMe::compareVec(VecIterator left, VecIterator right)
{
	return (*left < *right);
}

bool PmergeMe::compareDeq(DeqIterator left, DeqIterator right)
{
	return (*left < *right);
}

bool PmergeMe::compareLst(LstIterator left, LstIterator right)
{
	return (*left < *right);
}

PmergeMe::VecIterator	PmergeMe::next(VecIterator it, std::size_t n) const
{
	std::advance(it, n);
	return (it);
}

PmergeMe::VecPair::iterator	PmergeMe::next(VecPair::iterator it, std::size_t n) const
{
	std::advance(it, n);
	return (it);
}

PmergeMe::DeqIterator	PmergeMe::next(DeqIterator it, std::size_t n) const
{
	std::advance(it, n);
	return (it);
}

PmergeMe::DeqPair::iterator	PmergeMe::next(DeqPair::iterator it, std::size_t n) const
{
	std::advance(it, n);
	return (it);
}

PmergeMe::LstIterator	PmergeMe::next(LstIterator it, std::size_t n) const
{
	std::advance(it, n);
	return (it);
}

PmergeMe::LstPair::iterator	PmergeMe::next(LstPair::iterator it, std::size_t n) const
{
	std::advance(it, n);
	return (it);
}

void	PmergeMe::swapPairs(VecIterator& currentPair, const std::size_t level) const
{
	VecIterator start = next(currentPair, -level + 1);
	VecIterator end = next(start, level);

	while (start != end)
	{
		std::iter_swap(start, next(start, level));
		++start;
	}
}

void	PmergeMe::swapPairs(DeqIterator& currentPair, const std::size_t level) const
{
	DeqIterator start = next(currentPair, -level + 1);
	DeqIterator end = next(start, level);

	while (start != end)
	{
		std::iter_swap(start, next(start, level));
		++start;
	}
}

void	PmergeMe::swapPairs(LstIterator& currentPair, const std::size_t level) const
{
	LstIterator start = next(currentPair, -level + 1);
	LstIterator end = next(start, level);

	while (start != end)
	{
		std::iter_swap(start, next(start, level));
		++start;
	}
}

void	PmergeMe::sortPairs(std::vector<Int>& sequence, const std::size_t level, const std::size_t nPairs, const bool isOdd) const
{
	VecIterator start = sequence.begin();
	VecIterator end = next(next(start, nPairs * level), isOdd * -level);

	for (VecIterator it = start; it != end; std::advance(it, 2 * level))
	{
		VecIterator currentPair = next(it, level - 1);
		VecIterator nextPair = next(it, 2 * level - 1);
		if (compareVec(nextPair, currentPair))
		{
			swapPairs(currentPair, level);
		}
	}
}

void	PmergeMe::sortPairs(std::deque<Int>& sequence, const std::size_t level, const std::size_t nPairs, const bool isOdd) const
{
	DeqIterator start = sequence.begin();
	DeqIterator end = next(next(start, nPairs * level), isOdd * -level);

	for (DeqIterator it = start; it != end; std::advance(it, 2 * level))
	{
		DeqIterator currentPair = next(it, level - 1);
		DeqIterator nextPair = next(it, 2 * level - 1);
		if (compareDeq(nextPair, currentPair))
		{
			swapPairs(currentPair, level);
		}
	}
}

void	PmergeMe::sortPairs(std::list<Int>& sequence, const std::size_t level, const std::size_t nPairs, const bool isOdd) const
{
	LstIterator start = sequence.begin();
	LstIterator end = next(next(start, nPairs * level), isOdd * -level);

	for (LstIterator it = start; it != end; std::advance(it, 2 * level))
	{
		LstIterator currentPair = next(it, level - 1);
		LstIterator nextPair = next(it, 2 * level - 1);
		if (compareLst(nextPair, currentPair))
		{
			swapPairs(currentPair, level);
		}
	}
}

void	PmergeMe::customBinaryInsert(VecPair& mainChain, VecPair& pendingChain) const
{
	std::size_t previous = JACOBSTHAL_NUMBERS[0];
	std::size_t nInserts = 0;

	for (std::size_t i = 1; i < JACOBSTHAL_NUMBERS_SIZE; ++i)
	{
		std::size_t current = JACOBSTHAL_NUMBERS[i];
		const std::size_t diff = current - previous;

		if (diff > pendingChain.size())
		{
			break;
		}

		VecPair::iterator pendingIt = next(pendingChain.begin(), diff - 1);
		VecPair::iterator boundIt = next(mainChain.begin(), current + nInserts);
		std::size_t offset = 0;

		for (std::size_t j = 0; j < diff; ++j)
		{
			VecPair::iterator upperIt = std::upper_bound(mainChain.begin(), boundIt, *pendingIt, compareVec);
			VecPair::iterator insertIt = mainChain.insert(upperIt, *pendingIt);
			pendingIt = pendingChain.erase(pendingIt);
			std::advance(pendingIt, -1);
			
			offset += static_cast<std::size_t>(insertIt - mainChain.begin()) == current + nInserts;
			boundIt = next(mainChain.begin(), current + nInserts - offset);
		}

		previous = current;
		nInserts += diff;
	}
}

void	PmergeMe::customBinaryInsert(DeqPair& mainChain, DeqPair& pendingChain) const
{
	std::size_t previous = JACOBSTHAL_NUMBERS[0];
	std::size_t nInserts = 0;

	for (std::size_t i = 1; i < JACOBSTHAL_NUMBERS_SIZE; ++i)
	{
		std::size_t current = JACOBSTHAL_NUMBERS[i];
		const std::size_t diff = current - previous;

		if (diff > pendingChain.size())
		{
			break;
		}

		DeqPair::iterator pendingIt = next(pendingChain.begin(), diff - 1);
		DeqPair::iterator boundIt = next(mainChain.begin(), current + nInserts);
		std::size_t offset = 0;

		for (std::size_t j = 0; j < diff; ++j)
		{
			DeqPair::iterator upperIt = std::upper_bound(mainChain.begin(), boundIt, *pendingIt, compareDeq);
			DeqPair::iterator insertIt = mainChain.insert(upperIt, *pendingIt);
			pendingIt = pendingChain.erase(pendingIt);
			std::advance(pendingIt, -1);
			
			offset += static_cast<std::size_t>(insertIt - mainChain.begin()) == current + nInserts;
			boundIt = next(mainChain.begin(), current + nInserts - offset);
		}

		previous = current;
		nInserts += diff;
	}
}

void	PmergeMe::customBinaryInsert(LstPair& mainChain, LstPair& pendingChain) const
{
	std::size_t previous = JACOBSTHAL_NUMBERS[0];
	std::size_t nInserts = 0;

	for (std::size_t i = 1; i < JACOBSTHAL_NUMBERS_SIZE; ++i)
	{
		std::size_t current = JACOBSTHAL_NUMBERS[i];
		const std::size_t diff = current - previous;

		if (diff > pendingChain.size())
		{
			break;
		}

		LstPair::iterator pendingIt = next(pendingChain.begin(), diff - 1);
		LstPair::iterator boundIt = next(mainChain.begin(), current + nInserts);
		std::size_t offset = 0;

		for (std::size_t j = 0; j < diff; ++j)
		{
			LstPair::iterator upperIt = std::upper_bound(mainChain.begin(), boundIt, *pendingIt, compareLst);
			LstPair::iterator insertIt = mainChain.insert(upperIt, *pendingIt);
			pendingIt = pendingChain.erase(pendingIt);
			std::advance(pendingIt, -1);
			
			std::size_t index = 0;
			for (std::list<LstIterator>::iterator it = mainChain.begin(); it != insertIt; ++it)
			{
				++index;
			}
			offset += index == current + nInserts;
			boundIt = next(mainChain.begin(), current + nInserts - offset);
		}

		previous = current;
		nInserts += diff;
	}
}

void	PmergeMe::mergeInsertSort(std::vector<Int>& sequence, const std::size_t level) const
{
	const std::size_t nPairs = sequence.size() / level;

	if (nPairs < 2)
	{
		return;
	}

	const bool isOdd = nPairs % 2 != 0;

	sortPairs(sequence, level, nPairs, isOdd);

	mergeInsertSort(sequence, 2 * level);

	std::vector<VecIterator> mainChain;
	std::vector<VecIterator> pendingChain;

	mainChain.push_back(next(sequence.begin(), level - 1));
	mainChain.push_back(next(sequence.begin(), 2 * level - 1));

	for (std::size_t i = 4; i <= nPairs; i += 2)
	{
		mainChain.push_back(next(sequence.begin(), i * level - 1));
		pendingChain.push_back(next(sequence.begin(), (i - 1) * level - 1));
	}

	if (isOdd)
	{
		VecIterator last = next(sequence.begin(), nPairs * level);
		VecIterator end = next(last, isOdd * -level);

		pendingChain.push_back(next(end, level - 1));
	}

	customBinaryInsert(mainChain, pendingChain);

	for (long int i = pendingChain.size() - 1; i >= 0; --i)
	{
		std::vector<VecIterator>::iterator currentPending = next(pendingChain.begin(), i);
		std::size_t boundIndex = mainChain.size() - pendingChain.size() + i + isOdd;
		std::vector<VecIterator>::iterator currentBound = next(mainChain.begin(), boundIndex);
		std::vector<VecIterator>::iterator index = std::upper_bound(mainChain.begin(), currentBound, *currentPending, compareVec);
		mainChain.insert(index, *currentPending);
	}

	std::vector<Int> temp;
	temp.reserve(sequence.size());

	for (std::vector<VecIterator>::iterator it = mainChain.begin(); it != mainChain.end(); ++it)
	{
		for (std::size_t i = 0; i < level; ++i)
		{
			VecIterator start = *it;
			std::advance(start, -level + i + 1);
			temp.push_back(*start);
		}
	}

	VecIterator sequenceIt = sequence.begin();
	std::vector<Int>::iterator tempIt = temp.begin();

	while (tempIt != temp.end())
	{
		*sequenceIt = *tempIt;
		++sequenceIt;
		++tempIt;
	}
}

void	PmergeMe::mergeInsertSort(std::deque<Int>& sequence, const std::size_t level) const
{
	const std::size_t nPairs = sequence.size() / level;

	if (nPairs < 2)
	{
		return;
	}

	const bool isOdd = nPairs % 2 != 0;

	sortPairs(sequence, level, nPairs, isOdd);

	mergeInsertSort(sequence, 2 * level);

	std::deque<DeqIterator> mainChain;
	std::deque<DeqIterator> pendingChain;

	mainChain.push_back(next(sequence.begin(), level - 1));
	mainChain.push_back(next(sequence.begin(), 2 * level - 1));

	for (std::size_t i = 4; i <= nPairs; i += 2)
	{
		mainChain.push_back(next(sequence.begin(), i * level - 1));
		pendingChain.push_back(next(sequence.begin(), (i - 1) * level - 1));
	}

	if (isOdd)
	{
		DeqIterator last = next(sequence.begin(), nPairs * level);
		DeqIterator end = next(last, isOdd * -level);

		pendingChain.push_back(next(end, level - 1));
	}

	customBinaryInsert(mainChain, pendingChain);

	for (long int i = pendingChain.size() - 1; i >= 0; --i)
	{
		std::deque<DeqIterator>::iterator currentPending = next(pendingChain.begin(), i);
		std::size_t boundIndex = mainChain.size() - pendingChain.size() + i + isOdd;
		std::deque<DeqIterator>::iterator currentBound = next(mainChain.begin(), boundIndex);
		std::deque<DeqIterator>::iterator index = std::upper_bound(mainChain.begin(), currentBound, *currentPending, compareDeq);
		mainChain.insert(index, *currentPending);
	}

	std::deque<Int> temp;

	for (std::deque<DeqIterator>::iterator it = mainChain.begin(); it != mainChain.end(); ++it)
	{
		for (std::size_t i = 0; i < level; ++i)
		{
			DeqIterator start = *it;
			std::advance(start, -level + i + 1);
			temp.push_back(*start);
		}
	}

	DeqIterator sequenceIt = sequence.begin();
	std::deque<Int>::iterator tempIt = temp.begin();

	while (tempIt != temp.end())
	{
		*sequenceIt = *tempIt;
		++sequenceIt;
		++tempIt;
	}
}

void	PmergeMe::mergeInsertSort(std::list<Int>& sequence, const std::size_t level) const
{
	const std::size_t nPairs = sequence.size() / level;

	if (nPairs < 2)
	{
		return;
	}

	const bool isOdd = nPairs % 2 != 0;

	sortPairs(sequence, level, nPairs, isOdd);

	mergeInsertSort(sequence, 2 * level);

	std::list<LstIterator> mainChain;
	std::list<LstIterator> pendingChain;

	mainChain.push_back(next(sequence.begin(), level - 1));
	mainChain.push_back(next(sequence.begin(), 2 * level - 1));

	for (std::size_t i = 4; i <= nPairs; i += 2)
	{
		mainChain.push_back(next(sequence.begin(), i * level - 1));
		pendingChain.push_back(next(sequence.begin(), (i - 1) * level - 1));
	}

	if (isOdd)
	{
		LstIterator last = next(sequence.begin(), nPairs * level);
		LstIterator end = next(last, isOdd * -level);

		pendingChain.push_back(next(end, level - 1));
	}

	customBinaryInsert(mainChain, pendingChain);

	for (long int i = pendingChain.size() - 1; i >= 0; --i)
	{
		std::list<LstIterator>::iterator currentPending = next(pendingChain.begin(), i);
		std::size_t boundIndex = mainChain.size() - pendingChain.size() + i + isOdd;
		std::list<LstIterator>::iterator currentBound = next(mainChain.begin(), boundIndex);
		std::list<LstIterator>::iterator index = std::upper_bound(mainChain.begin(), currentBound, *currentPending, compareLst);
		mainChain.insert(index, *currentPending);
	}

	std::list<Int> temp;

	for (std::list<LstIterator>::iterator it = mainChain.begin(); it != mainChain.end(); ++it)
	{
		for (std::size_t i = 0; i < level; ++i)
		{
			LstIterator start = *it;
			std::advance(start, -level + i + 1);
			temp.push_back(*start);
		}
	}

	LstIterator sequenceIt = sequence.begin();
	std::list<Int>::iterator tempIt = temp.begin();

	while (tempIt != temp.end())
	{
		*sequenceIt = *tempIt;
		++sequenceIt;
		++tempIt;
	}
}

int	PmergeMe::getValue(std::string& value)
{
	if (value.size() == 0)
	{
		throw (EmptyNumberException());
	}
	std::size_t i = 0;
	if (value.size() > 1)
	{
		while (value[i] == '0' && value[i + 1] == '0')
		{
			++i;
		}
	}
	value.erase(0, i);
	if (value.size() > 12)
	{
		throw (InvalidNumberException());
	}
	const std::string validChars = "0123456789";
	for (std::size_t i = 0; i < value.size(); ++i)
	{
		if (validChars.find(value[i]) == std::string::npos)
		{
			throw (InvalidNumberException());
		}
	}
	long int convertedValue = std::atol(value.c_str());
	if (convertedValue > std::numeric_limits<int>::max())
	{
		throw (InvalidNumberException());
	}

	return (convertedValue);
}

std::vector<int>	PmergeMe::getVectorFromInput(const std::string& input)
{
	std::vector<int> result;
	std::stringstream ss(input);
	std::string value;

	ss >> value;
	while (!ss.eof())
	{
		std::size_t start = input.find_first_not_of(" ");
		if (start != std::string::npos)
		{
			value.erase(0, start);
			std::size_t end = value.find_last_not_of(" ");
			value.erase(end + 1);
		}
		try
		{
			int convertedValue = getValue(value);
			if (std::find(result.begin(), result.end(), convertedValue) != result.end())
			{
				throw (RepeatedNumberException(convertedValue));
			}
			result.push_back(convertedValue);
		}
		catch (const std::exception& e)
		{
			throw;
		}
		ss >> value;
	}
	return (result);
}

void	PmergeMe::setTimerFlag(const bool value)
{
	m_IsTimerFlagSet = value;
}

double	PmergeMe::getTimer() const
{
	return (m_Timer);
}

void	PmergeMe::sort(std::vector<int>& sequence)
{
	std::vector<Int> newSequence(sequence.begin(), sequence.end());

	if (m_IsTimerFlagSet)
	{
		std::clock_t start = std::clock();
		mergeInsertSort(newSequence, 1);
		std::clock_t end = std::clock();
		m_Timer = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	}
	else
	{
		mergeInsertSort(newSequence, 1);
	}

	std::vector<Int>::iterator newSequenceIt = newSequence.begin();
	std::vector<int>::iterator sequenceIt = sequence.begin();
	while (newSequenceIt != newSequence.end())
	{
		*sequenceIt = *newSequenceIt;
		++sequenceIt;
		++newSequenceIt;
	}
}

void	PmergeMe::sort(std::deque<int>& sequence)
{
	std::deque<Int> newSequence(sequence.begin(), sequence.end());

	if (m_IsTimerFlagSet)
	{
		std::clock_t start = std::clock();
		mergeInsertSort(newSequence, 1);
		std::clock_t end = std::clock();
		m_Timer = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	}
	else
	{
		mergeInsertSort(newSequence, 1);
	}

	std::deque<Int>::iterator newSequenceIt = newSequence.begin();
	std::deque<int>::iterator sequenceIt = sequence.begin();
	while (newSequenceIt != newSequence.end())
	{
		*sequenceIt = *newSequenceIt;
		++sequenceIt;
		++newSequenceIt;
	}
}

void	PmergeMe::sort(std::list<int>& sequence)
{
	std::list<Int> newSequence(sequence.begin(), sequence.end());

	if (m_IsTimerFlagSet)
	{
		std::clock_t start = std::clock();
		mergeInsertSort(newSequence, 1);
		std::clock_t end = std::clock();
		m_Timer = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	}
	else
	{
		mergeInsertSort(newSequence, 1);
	}

	std::list<Int>::iterator newSequenceIt = newSequence.begin();
	std::list<int>::iterator sequenceIt = sequence.begin();
	while (newSequenceIt != newSequence.end())
	{
		*sequenceIt = *newSequenceIt;
		++sequenceIt;
		++newSequenceIt;
	}
}

std::size_t PmergeMe::Int::nComps = 0;

PmergeMe::Int::Int(const int n) :
	m_Value(n)
{
	OCF_MESSAGE("Int constructor called");
}

PmergeMe::Int::Int() :
	m_Value(0)
{
	OCF_MESSAGE("Int Default constructor called");
}

PmergeMe::Int::~Int()
{
	OCF_MESSAGE("Int Destructor called");
}

PmergeMe::Int::Int(const Int& that) :
	m_Value(that.m_Value)
{
	OCF_MESSAGE("Int Copy constructor called");
}

PmergeMe::Int&	PmergeMe::Int::operator=(const Int& that)
{
	OCF_MESSAGE("Int Assignment operator called");
	if (this != &that)
	{
		m_Value = that.m_Value;
	}
	return (*this);
}

bool	PmergeMe::Int::operator<(const Int& that) const
{
	++nComps;
	return (m_Value < that.m_Value);
}

PmergeMe::Int::operator int() const
{
	return (m_Value);
}

const char*	PmergeMe::EmptyNumberException::what() const throw()
{
	return ("Empty number");
}

const char*	PmergeMe::InvalidNumberException::what() const throw()
{
	return ("Invalid number. Must be between 0 and 2147483647");
}

PmergeMe::RepeatedNumberException::RepeatedNumberException(const int number)
{
	std::stringstream ss;
	ss << "Repeated number (" << number << ")";
	m_Message = ss.str();
}

PmergeMe::RepeatedNumberException::~RepeatedNumberException() throw() {}

const char*	PmergeMe::RepeatedNumberException::what() const throw()
{
	return (m_Message.c_str());
}
