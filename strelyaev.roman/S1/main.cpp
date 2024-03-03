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
  a1.push_back(1);
  a1.push_back(1);
  a1.push_back(1);

  List< int > a2;
  a2.push_back(2);
  a2.push_back(2);
  a2.push_back(2);
  a2.push_back(2);

  List< int > a3;

  auto b1 = std::make_pair("First", a1);
  auto b2 = std::make_pair("Second", a2);
  auto b3 = std::make_pair("Third", a3);

  List< std::pair< std::string, List < int > > > l;
  l.push_back(b1);
  l.push_back(b2);
  l.push_back(b3);

  for (auto it = l.begin(); it != l.end(); ++it)
  {
    std::cout << "Outer string: " << it->first << std::endl;
    List<int> inner_list = it->second;
    for (Iterator<int> inner_it = inner_list.begin(); inner_it != inner_list.end(); ++inner_it)
    {
      std::cout << "Inner int: " << *inner_it << std::endl;
    }
  }
}
