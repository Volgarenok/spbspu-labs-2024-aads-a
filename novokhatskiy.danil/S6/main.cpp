#include <iostream>
#include <string>
#include <cstdlib>
#include <deque>
#include <list>
#include <forward_list.hpp>
#include "sortings.hpp"

template< class T >
void sortSeq(std::string& sort, std::string& type, size_t size, std::ostream& out)
{
	novokhatskiy::ForwardList< T > forwardList;
	std::list< T > biList;
	std::deque< T > deque;

	
}

int getInt()
{
	return std::rand() % 100;
}

float getFloat()
{
	return static_cast<float>(std::rand() / 1.2);
}

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

int main(int argc, char** argv)
{
  using namespace novokhatskiy;
	try
	{
		std::list< int > f1;
		for (size_t i = 0; i < 5; i++)
		{
			f1.push_front(getInt());
		}
		std::cout << "BEFORE SORT: ";
		for (auto i = f1.cbegin(); i != f1.cend(); i++)
		{
			std::cout << *i << ' ';
		}
		std::cout << '\n' << "SHAKER SORT: ";
		doShakerSort(f1.begin(), f1.end(), f1.size(), std::greater< int >());
		for (auto i = f1.cbegin(); i != f1.cend(); i++)
		{
			std::cout << *i << ' ';
		}
		std::cout << '\n';
		std::list< int > f2;
		for (size_t i = 0; i < 5; i++)
		{
			f2.push_front(getInt());
		}
		std::cout << "BEFORE SORT: ";
		for (auto i = f2.cbegin(); i != f2.cend(); i++)
		{
			std::cout << *i << ' ';
		}
		std::cout << '\n' << "INSERTION SORT: ";
		doInsertionSort(f2.begin(), f2.end(), std::greater< int >());
		for (auto i = f2.cbegin(); i != f2.cend(); i++)
		{
			std::cout << *i << ' ';
		}
		//size_t size = std::stoll(argv[3]);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}
}
