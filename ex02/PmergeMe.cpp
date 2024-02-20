#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(char **argv)
{
	if (!fillInputV(argv))
		throw std::runtime_error("Error: invalid argument input");
	if (!checkOnlyPositive())
		throw std::runtime_error("Error: only positive number can be entered");
}

PmergeMe::PmergeMe(const PmergeMe &obj) 
{
	*this = obj;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &obj)
{
	(void)obj;
	return (*this);
}

PmergeMe::~PmergeMe() {}

//---------------------consturctor utils
bool	PmergeMe::fillInputV(char **argv)
{
	for(int i = 1; argv[i]; i++)
	{
		std::istringstream	iss(argv[i]);
		std::string			token;
	
		while (iss >> token)
		{
			int					num;
			std::istringstream	tokenStream(token);

			if (!(tokenStream >> num))
				return (false);
			_vInput.push_back(num);
		}
	}
	return (true);
}

bool	PmergeMe::checkOnlyPositive()
{
	for(size_t i = 0; i < _vInput.size(); i++)
	{
		if (_vInput[i] < 0)
			return (false);
	}
	return (true);
}

//------------------------sortVector
void	PmergeMe::SortVector()
{
	_vStartTime = clock();
	fillChain(_vPendingChain, _vInput, 0, 1);
	groupAndCompare(_vPendingChain);
	fillChain(_vMainChain, _vPendingChain, 1, 2);

	std::cout << "first pending: ";
	printvPendingChain();

	std::cout << std::endl << "first main: ";
	printvMainChain();
	
	recursiveSortLargeElement(_vMainChain, 0, static_cast<int>(_vMainChain.size()) - 1);
	
	std::cout << std::endl <<"after recursive main: ";
	printvMainChain();

	std::cout << std::endl << "pending: ";
	printvPendingChain();

	binaryInsertSort(_vMainChain, _vPendingChain);
	std::cout << std::endl;
	printvMainChain();
	_vEndTime = clock();
}

void	PmergeMe::fillChain(std::vector<int> &target, const std::vector<int> &origin, size_t index, size_t span)
{
	while (index < origin.size())
	{
		target.push_back(origin[index]);
		index += span;
	}
}

void	PmergeMe::groupAndCompare(std::vector<int> &pendingChain)
{
	for(size_t i = 0; i < pendingChain.size(); i += 2)
	{
		int	temp;

		if (i + 1 == pendingChain.size())
			break ;
		if (pendingChain[i] > pendingChain[i + 1])
		{
			temp = pendingChain[i];
			pendingChain[i] = pendingChain[i + 1];
			pendingChain[i + 1] = temp;
		}//이걸 함수로 빼려면 레퍼런스? 굳이 안빼는게 더 직관적인것 같기도 일단 구현해보기?
	}
}

void PmergeMe::recursiveSortLargeElement(std::vector<int>& v, int start, int end)
{
	if (start >= end) 
		return ;

	int mid = (start + end) / 2;

	recursiveSortLargeElement(v, start, mid);
	recursiveSortLargeElement(v, mid + 1, end);

	std::vector<int> temp(end + 1);
	int tempIndex;
	int i, j;

	tempIndex = 0;
	i = start;
	j = mid + 1;

	while(i <= mid && j <= end)
	{
		if(v[i] < v[j])
			temp[tempIndex++] = v[i++];
		else
			temp[tempIndex++] = v[j++];
	}

	while(i <= mid)
		temp[tempIndex++] = v[i++];
	while(j <= end)
		temp[tempIndex++] = v[j++];

	for(int k = start, tempIndex = 0 ; k <= end ; k++, tempIndex++)
	{
		v[k] = temp[tempIndex];
	}
}

int PmergeMe::jacobsthal(int n) {
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    else
        return jacobsthal(n - 1) + 2 * jacobsthal(n - 2);
}

void	PmergeMe::removePendingChain(std::vector<int> &pendingChain)
{
	std::vector<int>	newPendingChain;

	for(size_t i = 0; i < pendingChain.size(); i++)
	{

		if (i % 2 == 0)
		{
			newPendingChain.push_back(pendingChain[i]);
		}
	}
	_vPendingChain = newPendingChain;
	std::cout << std::endl << "new pending: ";
	printvPendingChain();
}

void	PmergeMe::binaryInsertSort(std::vector<int> &mainChain, std::vector<int> &pendingChain)
{

	removePendingChain(pendingChain);
	mainChain.insert(mainChain.begin(), pendingChain[0]);//pendingChain의 0번째를 mainChain의 첫번째에 넣음
	
	int	size = static_cast<int>(pendingChain.size() - 1);
	int	cnt = 1;
	int	beforeJacobsthalNum = 1;
	int	nowJacobsthalNum = 1;
	int	jacobsthalN = 2;
	int	targetIdx = 1;

	while (cnt < size)
	{
		if (cnt == 1)
		{
			targetIdx = 1;
		}
		else
		{
			targetIdx--;
			if (targetIdx <= beforeJacobsthalNum)
			{
				jacobsthalN++;
				beforeJacobsthalNum = nowJacobsthalNum;
				nowJacobsthalNum = jacobsthal(jacobsthalN);
				targetIdx = nowJacobsthalNum;
			}
		}
		binaryInsert(mainChain, pendingChain, targetIdx);
		std::cout << std::endl;
		std::cout << cnt << "main: ";
		printvMainChain();
		cnt++;
	}
}

void	PmergeMe::binaryInsert(std::vector<int> &mainChain, std::vector<int> &pendingChain, int targetIdx)
{
	int	targetValue = pendingChain[targetIdx];

	int left = 0;
	int right = mainChain.size();
	//int insertPosition = -1; // targetValue가 삽입될 위치

	while (left < right)
	{
		int mid = left + (right - left) / 2;

		if (mainChain[mid] <= targetValue)
		{
			left = mid + 1;
		}
		else
		{
			right = mid;
		}
	}

	// 삽입 위치를 찾은 후에 targetValue를 삽입합니다.
	mainChain.insert(mainChain.begin() + left, targetValue);
}

//void	PmergeMe::vRecursiveSortLargeElement()
//{
//	for (int i = 1; i < _vPendingChain.size(); i += 2)
//	{
//		_vMainChain.push_back(_vPendingChain[i]);
//	}


//}
//------------------------sortDeque
/*
void	PmergeMe::SortDeque()
{
	_dStartTime = clock();
	dFillPendingChain();
	dGroupAndCompare();
	dRecursiveSortLargeElement();
	dBinaryInsertSort();
	_dEndTime = clock();
}
*/
//---------------------Display
void	PmergeMe::DisplayResult()
{
	std::cout << "Before : ";
	printAllElement(_vInput);
	std::cout << std::endl;

	std::cout << "After : ";
	printAllElement(_vMainChain);
	std::cout << std::endl;

	std::cout << "Time to process a range of"  << _vInput.size() << " elements with std::vector : ";
	std::cout << (_vStartTime - _vEndTime) * 1000 << " us" << std::endl;
	std::cout << "Time to process a range of"  << _vInput.size() << " elements with std::deque : ";
	std::cout << (_dStartTime - _dEndTime) * 1000 << " us" << std::endl;
}

//-------------------Utils

void	PmergeMe::printAllElement(std::vector<int> v)
{
	for(size_t i = 0; i < v.size(); i++)
	{
		std::cout << v[i];
		if (i < v.size() - 1)
			std::cout << " ";
	}
}

//ㅇㅖ오ㅣ케이스 5 4 3 2 1₩