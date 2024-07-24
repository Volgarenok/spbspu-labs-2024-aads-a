#include "commands.hpp"
#include <stdexcept>

void novokhatskiy::unionCmd(mainMap &dict, std::istream &in)
{
  std::string resName = {};
  std::string first = {};
  std::string second = {};
  in >> resName >> first >> second;
  map resDict;
  map dict1 = dict.at(first);
  map dict2 = dict.at(second);
  for (auto i = dict1.cbegin(); i != dict1.cend(); i++)
  {
    resDict.insert(*i);
  }
  for (auto i = dict2.cbegin(); i != dict2.cend(); i++)
  {
    if (resDict.find((*i).first) == resDict.cend())
    {
      resDict.insert(*i);
    }
  }
  dict[resName] = resDict;
}

void novokhatskiy::intersectCmd(mainMap &dict, std::istream &in)
{
  std::string resName = {};
  std::string first = {};
  std::string second = {};
  in >> resName >> first >> second;
  map resDict;
  map dict1 = dict.at(first);
  map dict2 = dict.at(second);
  auto begin = dict1.cbegin();
  auto end = dict1.cend();
  while (begin != end)
  {
    if (dict2.find(begin->first) != dict2.cend())
    {
      resDict.insert(*begin);
    }
    begin++;
  }
  if (dict.find(resName) != dict.cend())
  {
    dict.at(resName).clear();
    dict.at(resName) = std::move(resDict);
  }
  else
  {
    dict.insert(std::make_pair(std::move(resName), std::move(resDict)));
  }
}

void novokhatskiy::complement(mainMap &dict, std::istream &in)
{
  std::string resName = {};
  std::string first = {};
  std::string second = {};
  in >> resName >> first >> second;
  map resDict;
  map dict1 = dict.at(first);
  map dict2 = dict.at(second);

  auto begin = dict1.cbegin();
  auto end = dict1.cend();
  while (begin != end)
  {
    if (dict2.find(begin->first) == dict2.cend())
    {
      resDict.insert(*begin);
    }
    begin++;
  }
  begin = dict2.cbegin();
  end = dict2.cend();
  while (begin != end)
  {
    if (dict1.find(begin->first) == dict1.cend())
    {
      resDict.insert(*begin);
    }
    begin++;
  }
  if (dict.find(resName) != dict.cend())
  {
    dict.at(resName).clear();
    dict.at(resName) = std::move(resDict);
  }
  else
  {
    dict.insert(std::make_pair(std::move(resName), std::move(resDict)));
  }
}

void novokhatskiy::print(const mainMap &dict, std::istream &in, std::ostream &out)
{
  std::string nameOfDict = {};
  in >> nameOfDict;
  map tmp = dict.at(nameOfDict);
  if (tmp.empty())
  {
    throw std::logic_error("<EMPTY>");
  }
  out << nameOfDict;
  for (auto i = tmp.cbegin(); i != tmp.cend(); i++)
  {
    out << ' ' << (*i).first << ' ' << (*i).second;
  }
  out << '\n';
}
