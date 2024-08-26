#include "read_dictionaries.hpp"
#include <string>

void nikitov::readDictionaries(Tree< std::string, Tree< size_t, std::string > >& treeOfDictionaries, std::istream& input)
{
  while (!input.eof())
  {
    input.clear();
    std::string nameOfDictionary = {};
    input >> nameOfDictionary;
    Tree< size_t, std::string > dictionary;
    size_t key = {};
    while (input >> key)
    {
      std::string value = {};
      input >> value;
      dictionary.insert({ key, value });
    }

    treeOfDictionaries.insert({ nameOfDictionary, dictionary });
  }
}
