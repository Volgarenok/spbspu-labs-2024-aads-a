#include "inputDictionaries.hpp"
#include <istream>

void isaychev::inputDictionaries(std::istream & in, map_t & dicts)
{
  std::string name;
  int key = 0;
  std::string value;
  while (!in.eof())
  {
    in.clear();
    in >> name;
    dicts.insert(std::make_pair(name, dataset_t()));
    while (in >> key >> value)
    {
      (dicts.at(name)).insert(std::make_pair(key, value));
    }
  }
}
