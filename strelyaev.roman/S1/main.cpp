#include <iostream>
#include <utility>
#include "list.hpp"
#include "iterator.hpp"
#include "inputList.hpp"

int main()
{
  using namespace strelyaev;
  List< std::pair< std::string, List < int > > > l;
  try
  {
    makeSequence(std::cin, l);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }

  for (auto it = l.begin(); it != l.end(); it++)
  {
    std::cout << it->first << " ";
  }

  bool all_empty = false;
  List< int > sums;
  while (!all_empty)
  {
    std::cout << "\n";
    all_empty = true;
    int sum = 0;
    for (auto it = l.begin(); it != l.end(); it++)
    {
      if (!it->second.empty())
      {
        all_empty = false;
        std::cout << it->second.front() << " ";
        sum += it->second.front();
        it->second.pop_front();
      }
    }
    if (sum > 0)
    {
      sums.push_back(sum);
    }
  }

  if (sums.empty())
  {
    std::cout << "0\n";
    return 0;
  }
  for (auto it = sums.begin(); it != sums.end(); it++)
  {
    std::cout << *it << " ";
  }
  std::cout << "\n";
}
