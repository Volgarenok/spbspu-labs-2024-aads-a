#include <iostream>
#include <utility>
#include "list.hpp"
#include "iterator.hpp"
#include "inputList.hpp"
int main()
{
  using namespace strelyaev;
  List< std::pair< std::string, List < int > > > l;
  makeSequence(std::cin, l);
  for (auto it = l.begin(); it != l.end(); it++)
  {
    std::cout << it->first << " ";
  }
  std::cout << "\n";

  List< int > sums;
  for (int i = 0; i < 4; i++)
  {
    int sum = 0;
    for (auto it = l.begin(); it != l.end(); it++)
    {
      if (!it->second.empty())
      {
        std::cout << it->second.front() << " ";
        sum += it->second.front();
        it->second.pop_front();
      }
    }
    std::cout << "\n";
    sums.push_back(sum);
  }

  for (auto it = sums.begin(); it != sums.end(); it++)
  {
    std::cout << *it << " ";
  }
  std::cout << "\n";
}
