#include "read_dictionaries.hpp"
#include <string>

void nikitov::readDictionaries(std::map< std::string, std::map< size_t, std::string > >& treeOfDictionaries, std::istream& input)
{
  while(!input.eof())
  {
    std::string nameOfDictionary = {};
    input >> nameOfDictionary;

    std::map< size_t, std::string > dictionary;
    size_t key = {};
    std::string value = {};
    while(input >> key)
    {
      input >> value;
      dictionary.insert({ key, value });
    }
    treeOfDictionaries.insert({ nameOfDictionary, dictionary });
  }
}