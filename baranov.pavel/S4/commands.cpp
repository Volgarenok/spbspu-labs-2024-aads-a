#include "commands.hpp"
#include <string>
#include <iostream>

void baranov::print(const treeOfTrees & trees, std::istream & in, std::ostream & out)
{
  std::string dictName;
  in >> dictName;
  const basicTree & tree = trees.at(dictName);
  if (tree.empty())
  {
    out << "<EMPTY>\n";
    return;
  }
  out << dictName;
  for (auto it = tree.cbegin(); it != tree.cend(); ++it)
  {
    out << ' ' << it->first << ' ' << it->second;
  }
  out << '\n';
}

