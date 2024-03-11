#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include "forward_list.hpp"
#include <iostream>

namespace spiridonov
{
  using nameList = std::pair<std::string, List<int>>;

  nameList inputLine(std::istream& in)
  {
    nameList result;
    in >> result.first;
    if (result.first == "")
    {
      throw std::invalid_argument("Name is empty");
    }
    int inNum = 0;
    while (in >> inNum)
    {
      result.second.push_back(inNum);
    }
    return result;
  }

  List<nameList> input(std::istream& in)
  {
    List<nameList> Lists;
    while (in)
    {
      Lists.push_back(inputLine(in));
      if (!in.eof())
      {
        in.clear();
      }
    }
    return Lists;
  }

  template <typename T>
  void printListValues(const List<T>& list)
  {
    for (auto it = list.begin(); it != list.end(); ++it)
    {
      std::cout << *it << " ";
    }
    std::cout << '\n';
  }

  template <typename T>
  T sumListValues(const List<T>& list)
  {
    T sum = 0;
    for (auto it = list.begin(); it != list.end(); ++it)
    {
      sum += *it;
    }
    return sum;
  }

}

#endif
