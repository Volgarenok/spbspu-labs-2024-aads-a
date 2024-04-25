#include "inputfile.hpp"

void piyavkin::inputFile(std::istream& in, map_t& map)
{
  std::string str = "";
  tree_t tree;
  while (in >> str)
  {
    long long key = 0;
    std::string val = "";
    while (in)
    {
      in >> key >> val;
      if (in.bad())
      {
        in.clear();
        break;
      }
    }
    tree.insert(std::pair< long long, std::string >(key, val));
  }
  map.insert(std::pair< std::string, tree_t >(str, tree));
}