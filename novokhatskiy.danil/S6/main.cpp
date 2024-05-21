#include <iostream>
#include <string>
#include <cstdlib>
#include <deque>
#include <list>
#include <algorithm>
#include <iomanip>
#include <stdexcept>
#include <forward_list>
#include "sortings.hpp"

template< class It >
void printSeq(It begin, It end, std::ostream& out)
{
	while (begin != end)
	{
		out << *begin;
		begin++;
		if (begin != end)
		{
			out << ' ';
		}
	}
	out << '\n';
}

template< class T >
void sortSeq(std::string& sort, std::string& type, size_t size, std::ostream& out)
{
	using namespace novokhatskiy;
	std::forward_list< T > forwardList;
	std::list< T > biList;
	std::deque< T > deque;
	for (size_t i = 0; i != size; i++)
	{
		T value;
		if (type == "ints")
		{
			value = std::rand();
		}
		else
		{
			value = static_cast <float> (std::rand() / (static_cast <float> (RAND_MAX / RAND_MAX)));
		}
		forwardList.push_front(value);
		biList.push_back(value);
		deque.push_back(value);
	}
	std::list< T > secondBiList = biList;
	std::deque< T > secondDeque = deque;
	std::deque< T > thirdDeque = deque;
	std::cout << std::setprecision(1) << std::fixed;
	if (sort == "descending")
	{
		doInsertionSort(forwardList.begin(), forwardList.end(), std::greater< T >());
		doInsertionSort(biList.begin(), biList.end(), std::greater< T >());
		doShakerSort(secondBiList.begin(), secondBiList.end(), std::greater< T >());
		doInsertionSort(deque.begin(), deque.end(), std::greater< T >());
		doShakerSort(secondDeque.begin(), secondDeque.end(), std::greater< T >());
		std::sort(thirdDeque.begin(), thirdDeque.end(), std::greater< T >());
	}
	else if (sort == "ascending")
	{
		doInsertionSort(forwardList.begin(), forwardList.end(), std::less< T >());
		doInsertionSort(biList.begin(), biList.end(), std::less< T >());
		doShakerSort(secondBiList.begin(), secondBiList.end(), std::less< T >());
		doInsertionSort(deque.begin(), deque.end(), std::less< T >());
		doShakerSort(secondDeque.begin(), secondDeque.end(), std::less< T >());
		std::sort(thirdDeque.begin(), thirdDeque.end(), std::less< T >());
	}
	else
	{
		throw std::invalid_argument("Incorrect sorting");
	}
	printSeq(forwardList.cbegin(), forwardList.cend(), out);
	printSeq(biList.cbegin(), biList.cend(), out);
	printSeq(secondBiList.cbegin(), secondBiList.cend(), out);
	printSeq(deque.cbegin(), deque.cend(), out);
	printSeq(secondDeque.cbegin(), secondDeque.cend(), out);
	printSeq(thirdDeque.cbegin(), thirdDeque.cend(), out);
}

int main(int argc, char** argv)
{
  using namespace novokhatskiy;
	try
	{
		if (argc != 4)
		{
			std::cerr << "Wrong input arguments\n";
			return 1;
		}
		size_t size = std::stoull(argv[3]);
		std::string sort(argv[1]);
		std::string type(argv[2]);
		if (type == "ints")
		{
			sortSeq< int >(sort, type, size, std::cout);
		}
		else if (type == "floats")
		{
			sortSeq< float >(sort, type, size, std::cout);
		}
		else
		{
			throw std::invalid_argument("Invalid type of sequence");
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}
}
