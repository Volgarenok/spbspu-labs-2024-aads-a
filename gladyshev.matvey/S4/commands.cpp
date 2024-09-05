#include "commands.hpp"

#include <iostream>

void gladyshev::print_dictionary(const dic& dictionary)
{
  for (auto it = dictionary.cbegin(); it != dictionary.cend(); ++it)
  {
    std::cout << " " << it->first << " " << it->second;
  }
  std::cout << "\n";
}

void gladyshev::print_dictionaries(const std::string& s, const mainDic& dictionaries)
{
  bool hasDic = false;
  for (auto it = dictionaries.cbegin(); it != dictionaries.cend(); ++it)
  {
    if (s == it->first)
    {
      if (it->second.empty())
      {
        throw std::overflow_error("<EMPTY>");
      }
      hasDic = true;
      std::cout << it->first;
      print_dictionary(it->second);
    }
    if (it->first.empty())
    {
       throw std::overflow_error("<INVALID COMMAND>");
    }
  }
  if (!hasDic)
  {
    throw std::overflow_error("<INVALID COMMAND>");
  }
}

gladyshev::mainDic gladyshev::intersect(const std::string& s, const dic& dict1, const dic& dict2)
{
  dic result;
  mainDic finres;
  for (auto it1 = dict1.cbegin(); it1 != dict1.cend(); ++it1)
  {
    for (auto it2 = dict2.cbegin(); it2 != dict2.cend(); ++it2)
    {
      if (it1->first == it2->first)
      {
        result.insert(it1->first, it1->second);
      }
    }
  }
  finres.insert(s, result);
  return finres;
}
gladyshev::mainDic gladyshev::complement(const std::string& s, const dic& dict1, const dic& dict2)
{
  dic result;
  mainDic finres;
  bool check = true;
  for (auto it1 = dict1.cbegin(); it1 != dict1.cend(); ++it1)
  {
    check = true;
    for (auto it2 = dict2.cbegin(); it2 != dict2.cend(); ++it2)
    {
      if (it1->first == it2->first)
      {
        check = false;
      }
    }
    if (check)
    {
      result.insert(it1->first, it1->second);
    }
  }
  finres.insert(s, result);
  return finres;
}
gladyshev::mainDic gladyshev::union_dictionaries(const std::string& s, const dic& dict1, const dic& dict2)
{
  dic result = dict1;
  mainDic finres;
  for (auto it2 = dict2.cbegin(); it2 != dict2.cend(); ++it2)
  {
    if (result.find(it2->first) == result.end())
    {
      result.insert(it2->first, it2->second);
    }
  }
  finres.insert(s, result);
  return finres;
}
gladyshev::dic gladyshev::findName(const mainDic& dictionaries, const std::string& name)
{
  auto it = dictionaries.find(name);
  if (it != dictionaries.cend())
  {
    return it->second;
  }
  else
  {
    throw std::out_of_range("bad");
  }
}
