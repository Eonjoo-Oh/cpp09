#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <exception>
#include <stdexcept>
#include <sstream>
#include <ctime>
#include <utility>

class	PmergeMe
{
	private :
		std::vector<int>	_vInput;

		std::vector<int>	_vMainChain;
		std::vector<int>	_vPendingChain;
		std::vector<std::pair<int, int> >	_vPendingPair;

		std::deque<int>		_dMainChain;
		std::deque<int>		_dPendingChain;
		std::deque<std::pair<int, int> >	_dPendingPair;

		clock_t				_vStartTime;
		clock_t				_vEndTime;
		clock_t				_dStartTime;
		clock_t				_dEndTime;
		
		int					_lastElement;
		
		bool				fillInputV(char **argv);
		bool				checkOnlyPositive();
		int					jacobsthal(int n);
		void				printAllElement(std::vector<int> v);

		void				fillChain(std::vector<int> &target, const std::vector<int> &origin, size_t index, size_t span);
		void				groupAndCompare(std::vector<int> &pendinChain);
		void				recursiveSortLargeElement(std::vector<std::pair<int, int> > &v, int start, int end);
		void				fillMainChain(std::vector<int> &mainChain, std::vector<std::pair<int, int> >pendingPair);
		void				binaryInsertSortUsingJacobsthal(std::vector<int> &mainChain, std::vector<std::pair<int, int> > &pendingPair);
		void				binaryInsert(std::vector<int> &mainChain, std::vector<std::pair <int, int> > &pendingPair, int targetIdx);
		//void				binaryInsertSort(std::vector<int> &mainChain, std::vector<int> &pendinChain);
		void				binaryInsertSort(std::vector<int> &mainChain, int target);

		//void				binaryInsert(std::vector<int> &mainChain, std::vector<int> &pendingChain, int targetIdx);
		
		
		//--------------deque
		void				fillChain(std::deque<int> &target, const std::vector<int> &origin, size_t index, size_t span);
		void				groupAndCompare(std::deque<int> &pendingChain);
		void				recursiveSortLargeElement(std::deque<std::pair<int, int> > &d, int start, int end);
		void				fillMainChain(std::deque<int> &mainChain, std::deque<std::pair<int, int> >pendingPair);
		void				binaryInsertSortUsingJacobsthal(std::deque<int> &mainChain, std::deque<std::pair<int, int> > &pendingPair);
		void				binaryInsert(std::deque<int> &mainChain, std::deque<std::pair <int, int> > &pendingPair, int targetIdx);
		void				binaryInsertSort(std::deque<int> &mainChain, int target);
		//void				dFillPendingChain();
		//void				dGroupAndCompare();
		//void				dRecursiveSortLargeElement();
		//void				dBinaryInsertSort();
		//void				removePendingChain(std::vector<int> &pendingChain);

	public :
		PmergeMe();
		PmergeMe(char **argv);
		PmergeMe(const PmergeMe &obj);
		PmergeMe &operator=(const PmergeMe &obj);
		~PmergeMe();

		void	sortVector();
		void	sortDeque();
		void	DisplayResult();
		//test
		void	printvInput() 
		{
			printAllElement(_vInput);
		};
		void	printvPendingChain() 
		{
			printAllElement(_vPendingChain);
		};
		void	printvMainChain() 
		{
			printAllElement(_vMainChain);
		};
		void	printAllDequeElement(std::deque<int> &d)
		{
			for(size_t i = 0; i < d.size(); i++)
			{
				std::cout << d[i] << " ";
			}
		}
		
};