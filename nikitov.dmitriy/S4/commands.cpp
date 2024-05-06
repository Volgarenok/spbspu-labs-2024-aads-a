#include "commands.hpp"
#include <istream>

void nikitov::printCmd(const Tree< std::string, Tree< size_t, std::string > >& tree, std::istream& input, std::ostream& output)
{
  std::string nameOfDict = {};
  input >> nameOfDict;

  Tree< size_t, std::string > dict = tree.at(nameOfDict);
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

void nikitov::inputCmd(Tree< std::string, Tree< size_t, std::string > >& tree, std::istream& input, const std::string& cmd)
{
  std::string newDictName = {};
  input >> newDictName;
  std::string firstDictName = {};
  input >> firstDictName;
  std::string secondDictName = {};
  input >> secondDictName;

  Tree< size_t, std::string > newDict;
  Tree< size_t, std::string > dict1 = tree.at(firstDictName);
  Tree< size_t, std::string > dict2 = tree.at(secondDictName);
  if (cmd == "complement")
  {
    for (auto i = dict1.cbegin(); i != dict1.cend(); ++i)
    {
      try
      {
        dict2.at((*i).first);
      }
      catch(const std::logic_error&)
      {
        newDict.insert({ (*i).first, (*i).second });
      }
    }
  }
  else if (cmd == "intersect")
  {
    for (auto i = dict2.cbegin(); i != dict2.cend(); ++i)
    {
      try
      {
        newDict.insert({ (*i).first, dict1.at((*i).first) });
      }
      catch(const std::logic_error&)
      {
        continue;
      }
    }
  }
  else if (cmd == "union")
  {
    for (auto i = dict1.cbegin(); i != dict1.cend(); ++i)
    {
      newDict.insert({(*i).first, (*i).second });
    }
    for (auto i = dict2.cbegin(); i != dict2.cend(); ++i)
    {
      newDict.insert({(*i).first, (*i).second });
    }
  }
  tree[newDictName] = newDict;
}
