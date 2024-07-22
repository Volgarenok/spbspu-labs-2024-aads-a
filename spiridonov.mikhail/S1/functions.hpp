#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <iostream>
#include <climits>
#include "forward_list.hpp"

namespace spiridonov
{
  using nameList = std::pair<std::string, List< size_t >>;

  nameList inputLine(std::istream& in)
  {
    nameList result;
    in >> result.first;
    if (result.first == "")
    {
      throw std::invalid_argument("Name is empty");
    }

    size_t inNum = 0;
    while (in >> inNum)
    {
      if (inNum > INT_MAX)
      {
        throw std::overflow_error("Error: overflow");
      }
      result.second.push_back(inNum);
    }

    return result;
  }

  List<nameList> input(std::istream& in)
  {
    List<nameList> Lists;
    try
    {
      while (in)
      {
        Lists.push_back(inputLine(in));
        if (!in.eof())
        {
          in.clear();
        }
      }
    }
    catch (std::invalid_argument&)
    {
      throw std::invalid_argument("Name is empty");
    }
    catch (std::overflow_error &)
    {
      throw std::overflow_error("Error: overflow");
    }
    return Lists;
  }

  template <typename T>
  void printListValues(const List<T>& list)
  {
    for (auto it = list.begin(); it != list.end(); ++it)
    {
      std::cout << *it;
      if (it + 1 != list.end())
      {
        std::cout << " ";
      }
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
