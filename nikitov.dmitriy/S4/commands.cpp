#include "commands.hpp"
#include <istream>

void nikitov::printCmd(const Tree< std::string, Tree< size_t, std::string > >& tree, const std::string& dictName, std::ostream& output)
{
  Tree< size_t, std::string > dict = tree.at(dictName);
  if (dict.empty())
  {
    throw std::logic_error("<EMPTY>");
  }
  output << dictName;
  for (auto i = dict.cbegin(); i != dict.cend(); ++i)
  {
    output << ' ' << (*i).first << ' ' << (*i).second;
  }
  output << '\n';
}

void nikitov::complementCmd(Tree< std::string, Tree< size_t, std::string > >& tree, const std::string& newDictName,
  const std::string& firstDictName, const std::string& secondDictName)
{
  Tree< size_t, std::string > newDict;
  Tree< size_t, std::string > dict1 = tree.at(firstDictName);
  Tree< size_t, std::string > dict2 = tree.at(secondDictName);
  for (auto i = dict1.cbegin(); i != dict1.cend(); ++i)
  {
    try
    {
      dict2.at((*i).first);
    }
    catch (const std::logic_error&)
    {
      newDict.insert({ (*i).first, (*i).second });
    }
  }
  tree[newDictName] = newDict;
}

void nikitov::intersectCmd(Tree< std::string, Tree< size_t, std::string > >& tree, const std::string& newDictName,
  const std::string& firstDictName, const std::string& secondDictName)
{
  Tree< size_t, std::string > newDict;
  Tree< size_t, std::string > dict1 = tree.at(firstDictName);
  Tree< size_t, std::string > dict2 = tree.at(secondDictName);
  for (auto i = dict2.cbegin(); i != dict2.cend(); ++i)
  {
    try
    {
      newDict.insert({ (*i).first, dict1.at((*i).first) });
    }
    catch (const std::logic_error&)
    {
      continue;
    }
  }
  tree[newDictName] = newDict;
}

void nikitov::unionCmd(Tree< std::string, Tree< size_t, std::string > >& tree, const std::string& newDictName,
  const std::string& firstDictName, const std::string& secondDictName)
{
  Tree< size_t, std::string > newDict;
  Tree< size_t, std::string > dict1 = tree.at(firstDictName);
  Tree< size_t, std::string > dict2 = tree.at(secondDictName);
  for (auto i = dict1.cbegin(); i != dict1.cend(); ++i)
  {
    newDict.insert({(*i).first, (*i).second });
  }
  for (auto i = dict2.cbegin(); i != dict2.cend(); ++i)
  {
    newDict.insert({(*i).first, (*i).second });
  }
  tree[newDictName] = newDict;
}
