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
}