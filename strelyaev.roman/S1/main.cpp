#include <iostream>
#include <utility>
#include "list.hpp"
#include "iterator.hpp"
#include "inputList.hpp"
int main()
{
  using namespace strelyaev;
  List< int > a1;
  a1.push_back(1);
  a1.push_back(2);
  a1.push_back(3);

  List< int > a2;
  a2.push_back(2);
  a2.push_back(2);
  a2.push_back(2);
  a2.push_back(2);

  List< int > a3;

  List< int > a4;
  a4.push_back(4);
  a4.push_back(4);

  auto b1 = std::make_pair("First", a1);
  auto b2 = std::make_pair("Second", a2);
  auto b3 = std::make_pair("Third", a3);
  auto b4 = std::make_pair("Fourth", a4);

  List< std::pair< std::string, List < int > > > l;
  l.push_back(b1);
  l.push_back(b2);
  l.push_back(b3);
  l.push_back(b4);

  for (auto it = l.begin(); it != l.end(); ++it)
  {
    std::cout << it->first << " ";
  }

  std::cout << "\n";

  bool all_empty = false;
  List< int > sums;

  while (!all_empty)
  {
    int i = 0;
    all_empty = true;
    for (auto it = l.begin(); it != l.end(); it++)
    {
      for (auto in_it = it->second.begin(); in_it != it->second.end(); in_it++)
      {
        std::cout << *in_it << " ";
      }
      std::cout << "\n";
    }
    std::cout << "\n";
    sums.push_back(i);
  }
}
