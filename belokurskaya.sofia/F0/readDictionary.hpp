#ifndef READ_DICTIONARY_HPP
#define READ_DICTIONARY_HPP

#include <fstream>
#include <sstream>
#include <unordered_map>

#include "eng-rusDictionary.hpp"

namespace belokurskaya
{
  BinarySearchTree< std::string, EngRusDict > ReadEngRusDictFromFile(const std::string& pathToFile);
}

#endif
