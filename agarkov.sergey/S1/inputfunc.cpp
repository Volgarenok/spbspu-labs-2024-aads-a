#include "inputfunc.hpp"
#include <string>
#include <istream>
#include <utility>
#include "forwardlist.hpp"

#include <iostream>

std::pair< std::string, agarkov::ForwardList< size_t > > agarkov::inputList(std::istream &in)
{
  std::string name = "";
  in >> name;
  if (name == "")
  {
    throw std::logic_error("Empty name");
  }
  ForwardList< size_t > list;
  size_t num = 0;
  while (in >> num )
  {
    list.push_front(num);
  }
  std::cout << "test2\n";
  return std::make_pair(name, list);
}

agarkov::ForwardList< std::pair < std::string, agarkov::ForwardList< size_t > > > agarkov::inputLists(std::istream& in)
{
  ForwardList< std::pair < std::string, ForwardList< size_t > > > list_of_lists;
  while (in)
  {
    list_of_lists.push_front(inputList(in));
  }
  std::cout << "test1\n";
  return list_of_lists;
}