#include "read_dictionaries.hpp"
#include <string>

#include <iostream>

void nikitov::readDictionaries(std::map< std::string, std::map< size_t, std::string > >& treeOfDictionaries, std::istream& input)
{
  while(!input.eof())
  {
    input.clear();
    std::string nameOfDictionary = {};
    input >> nameOfDictionary;

    std::map< size_t, std::string > dictionary;
    size_t key = {};
    while(input >> key)
    {
      std::string value = {};
      input >> value;
      dictionary.insert({ key, value });
    }

    treeOfDictionaries.insert({ nameOfDictionary, dictionary });
  }
}