#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>

#include "dictionaryCollection.hpp"

using DictCol = belokurskaya::DictionaryCollection&;
using Str = const std::string&;

namespace belokurskaya
{
  namespace cmds
  {
    void complement(DictCol dictionaries, std::istream& in);
    void intersect(DictCol dictionaries, std::istream& in);
    void unionD(DictCol dictionaries, std::istream& in);
    void print(DictCol dictionaries, std::istream& in);

    namespace subcmds
    {
      void complementDicts(DictCol dictionaries, Str new_name, Str first_name, Str second_name);
      void intersectDicts(DictCol dictionaries, Str new_name, Str first_name, Str second_name);
      void unionDicts(DictCol dictionaries, Str new_name, Str first_name, Str second_name);
      void printCommand(DictCol dictionaries, Str name);
      void validateDictionaries(DictCol dictionaries, Str name1, Str name2);
      void printDictionary(const Dictionary& dict, Str name);
    }
  }
}

#endif
