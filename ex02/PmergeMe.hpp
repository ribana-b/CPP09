/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ribana-b <ribana-b@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:33:03 by ribana-b          #+#    #+# Malaga      */
/*   Updated: 2025/06/29 01:12:46 by ribana-b         ###   ########.com      */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

/* @------------------------------------------------------------------------@ */
/* |                            Include Section                             | */
/* @------------------------------------------------------------------------@ */

#include <list>		// For std::list
#include <vector>	// For std::vector
#include <deque>	// For std::deque
#include <list>		// For std::list
#include <string>	// For std::string

/* @------------------------------------------------------------------------@ */
/* |                             Class Section                              | */
/* @------------------------------------------------------------------------@ */

class PmergeMe
{
	public:
		PmergeMe();
		~PmergeMe();
		PmergeMe(const PmergeMe&);
		PmergeMe&	operator=(const PmergeMe&);

		void	setTimerFlag(const bool value);
		double	getTimer() const;

		static std::vector<int>	getVectorFromInput(const std::string& input);

		void	sort(std::vector<int>& sequence);
		void	sort(std::deque<int>& sequence);
		void	sort(std::list<int>& sequence);

		class Int
		{
			public:
				int m_Value;
				static std::size_t nComps;

				Int(const int n);
				Int();
				~Int();
				Int(const Int& that);
				Int& operator=(const Int& that);

				bool operator<(const Int& that) const;

				operator int() const;
		};

		typedef std::vector<Int>::iterator	VecIterator;
		typedef std::vector<VecIterator>	VecPair;

		typedef std::deque<Int>::iterator	DeqIterator;
		typedef std::deque<DeqIterator>		DeqPair;

	private:
		bool	m_IsTimerFlagSet;
		double	m_Timer;

		static int	getValue(std::string& value);

		static bool			compareVec(VecIterator left, VecIterator right);
		VecIterator			next(VecIterator it, std::size_t n) const;
		VecPair::iterator	next(VecPair::iterator it, std::size_t n) const;
		void				swapPairs(VecIterator& currentPair, const std::size_t level) const;
		void				sortPairs(std::vector<Int>& sequence, const std::size_t level, const std::size_t nPairs, const bool isOdd) const;
		void				customBinaryInsert(VecPair& mainChain, VecPair& pendingChain) const;
		void				mergeInsertSort(std::vector<Int>& sequence, const std::size_t level) const;

		static bool			compareDeq(DeqIterator left, DeqIterator right);
		DeqIterator			next(DeqIterator it, std::size_t n) const;
		DeqPair::iterator	next(DeqPair::iterator it, std::size_t n) const;
		void				swapPairs(DeqIterator& currentPair, const std::size_t level) const;
		void				sortPairs(std::deque<Int>& sequence, const std::size_t level, const std::size_t nPairs, const bool isOdd) const;
		void				customBinaryInsert(DeqPair& mainChain, DeqPair& pendingChain) const;
		void				mergeInsertSort(std::deque<Int>& sequence, const std::size_t level) const;
};

#endif
