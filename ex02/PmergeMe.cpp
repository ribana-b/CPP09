/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:32:08 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2025/06/24 22:31:06 by ribana-b         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <algorithm>	// For std::upper_bound
#include <iostream>		// For std::cout
#include <vector>		// For std::vector
#include <ctime>		// For std::clock_t, std::clock

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

bool PmergeMe::compare(VecIterator left, VecIterator right)
{
	return (*left < *right);
}

PmergeMe::VecIterator	PmergeMe::next(VecIterator it, std::size_t n) const
{
	std::advance(it, n);
	return (it);
}

PmergeMe::Pair::iterator	PmergeMe::next(Pair::iterator it, std::size_t n) const
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

void	PmergeMe::sortPairs(std::vector<Int>& sequence, const std::size_t level, const std::size_t nPairs, const bool isOdd) const
{
	VecIterator start = sequence.begin();
	VecIterator end = next(next(start, nPairs * level), isOdd * -level);

	for (VecIterator it = start; it != end; std::advance(it, 2 * level))
	{
		VecIterator currentPair = next(it, level - 1);
		VecIterator nextPair = next(it, 2 * level - 1);
		if (compare(nextPair, currentPair))
		{
			swapPairs(currentPair, level);
		}
	}
}

void	PmergeMe::customBinaryInsert(Pair& mainChain, Pair& pendingChain) const
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

		std::vector<VecIterator>::iterator pendingIt = next(pendingChain.begin(), diff - 1);
		std::vector<VecIterator>::iterator boundIt = next(mainChain.begin(), current + nInserts);
		std::size_t offset = 0;

		for (std::size_t j = 0; j < diff; ++j)
		{
			Pair::iterator upperIt = std::upper_bound(mainChain.begin(), boundIt, *pendingIt, compare);
			Pair::iterator insertIt = mainChain.insert(upperIt, *pendingIt);
			pendingIt = pendingChain.erase(pendingIt);
			std::advance(pendingIt, -1);
			
			offset += static_cast<std::size_t>(insertIt - mainChain.begin()) == current + nInserts;
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
		std::vector<VecIterator>::iterator index = std::upper_bound(mainChain.begin(), currentBound, *currentPending, compare);
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

std::vector<int>	getVectorFromInput(const std::string&)
{
	// TODO(srvariable): Parse input
	std::vector<int> result;

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

void	PmergeMe::sort(std::deque<int>&)
{
	// TODO(srvariable): Implement MIS for std::deque
}

void	PmergeMe::sort(std::list<int>&)
{
	// TODO(srvariable): Implement MIS for std::list
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
