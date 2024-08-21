#ifndef COMMAND_COLLECTION_HPP
#define COMMAND_COLLECTION_HPP

#include <iostream>

#include "dictionaryCollection.hpp"

using DictCol = belokurskaya::DictionaryCollection&;
using Str = const std::string&;

namespace belokurskaya
{
  namespace cmds
  {
    void complement(DictCol& dictionaries, std::istream& in, std::ostream& out);
    void intersect(DictCol& dictionaries, std::istream& in, std::ostream& out);
    void unionDicts(DictCol& dictionaries, std::istream& in, std::ostream& out);
    void printCommand(DictCol& dictionaries, std::istream& in, std::ostream& out);
    namespace subcmds
    {
      void validateDictionaries(DictCol& dictionaries, Str name1, Str name2);
      void printDictionary(const Dictionary& dict, Str name);
    }
  } 
}

#endif
