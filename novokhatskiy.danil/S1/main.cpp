#include <iostream>
#include "forward_list.hpp"
#include "forward_list_iterators.hpp"
#include "inputForwardList.hpp"

using namespace novokhatskiy;
using ull = unsigned long long;
void outputForwardList(std::ostream& out, ForwardList<std::pair<std::string, ForwardList< ull > > >& pairs)
{
  if (pairs.empty())
  {
    throw std::invalid_argument("Your list is empty");
  }
  pairs.reverse();
  ForwardIterator< std::pair<std::string, ForwardList< ull > > > iter = pairs.begin();
  for (; iter != pairs.end(); iter++)
  {
    if (std::isalpha(iter->first[0]))
    {
      if (iter != pairs.begin())
      {
        out << ' ';
      }
      out << iter->first;
    }
    else
    {
      std::cout << ' ';
    }
  }
  std::cout << '\n';
  pairs.begin()->second.reverse();
  ForwardList< ull > listOfSums;
  ull sum{};
  for (size_t i = 0; i < pairs.begin()->second.max_size(); i++)
  {
    for (auto j = pairs.begin(); j != pairs.end(); j++)
    {
      if (j != pairs.begin())
      {
        out << ' ';
      }
      out << j->second.front();
      sum += j->second.front();
    }
    out << '\n';
    listOfSums.push_front(sum);
  }
  listOfSums.reverse();
  for (auto i = listOfSums.begin(); i != listOfSums.end(); ++i)
  {
    if (i != listOfSums.begin())
    {
      out << ' ';
    }
    out << *i;
  }
  out << '\n';
}

int main()
{
  ForwardList<int> l;
  for (size_t i = 0; i < 10; i++)
  {
    l.push_front(i);
  }
  for (auto i = l.begin(); i != l.end(); i++)
  {
    std::cout << *i << ' ';
  }
  std::cout << std::endl;
  l.reverse();
  l.print();
  ForwardList<int> q { 1,2,3,4 };
  q.print();
  ForwardList<std::pair<std::string, ForwardList< unsigned long long > > > pairs;
  inputForwardList(pairs, std::cin);
  outputForwardList(std::cout, pairs);
}
