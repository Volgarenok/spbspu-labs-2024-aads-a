#include "commands.hpp"
#include <istream>
#include <map>

void nikitov::printCmd(const std::map< std::string, std::map< size_t, std::string > >& tree, std::istream& input, std::ostream& output)
{
  std::string nameOfDict = {};
  input >> nameOfDict;

  std::map< size_t, std::string > dict = tree.at(nameOfDict);
  if (dict.empty())
  {
    throw std::logic_error("<EMPTY>");
  }
  output << nameOfDict;
  for (auto i = dict.cbegin(); i != dict.cend(); ++i)
  {
    output << ' ' << (*i).first << ' ' << (*i).second;
  }
  output << '\n';
}

void nikitov::unionCmd(std::map< std::string, std::map< size_t, std::string > >& tree, std::istream& input)
{
  std::string newDictName = {};
  input >> newDictName;
  std::string firstDictName = {};
  input >> firstDictName;
  std::string secondDictName = {};
  input >> secondDictName;

  std::map< size_t, std::string > newDict;
  std::map< size_t, std::string > dict1 = tree.at(firstDictName);
  std::map< size_t, std::string > dict2 = tree.at(secondDictName);
  for (auto i = dict1.cbegin(); i != dict1.cend(); ++i)
  {
    newDict.insert({(*i).first, (*i).second });
  }
  for (auto i = dict2.cbegin(); i != dict2.cend(); ++i)
  {
    newDict.insert({(*i).first, (*i).second });
  }
  tree.insert({ newDictName, newDict });
}