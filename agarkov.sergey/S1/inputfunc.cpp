#include "inputfunc.hpp"
#include <string>
#include <istream>
#include <utility>
#include "forwardlist.hpp"
#include "forwardlistiterator.hpp"

agarkov::pair_t agarkov::inputList(std::istream &in)
{
  std::string name = "";
  in >> name;
  if (name == "")
  {
    throw std::logic_error("Empty name");
  }
  ForwardList< size_t > list;
  size_t num = 0;
  auto iter = list.begin();
  while (in >> num )
  {
    if (list.empty())
    {
      list.push_front(num);
      iter = list.begin();
    }
    else
    {
      list.insert_after(iter, num);
      iter++;
    }
  }
  return std::make_pair(name, list);
}

agarkov::ForwardList< agarkov::pair_t > agarkov::inputLists(std::istream& in)
{
  ForwardList< pair_t > list_of_lists;
  auto iter = list_of_lists.begin();
  while (in)
  { 
    if (list_of_lists.empty())
    {
      list_of_lists.push_front(inputList(in));
      iter = list_of_lists.begin();
    }
    else
    {
      list_of_lists.insert_after(iter, inputList(in));
      iter++;
    }
    if (!in.eof())
    {
      in.clear();
    }
  }
  return list_of_lists;
}