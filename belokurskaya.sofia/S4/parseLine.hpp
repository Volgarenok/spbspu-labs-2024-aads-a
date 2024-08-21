#ifndef PARSE_LINE_HPP
#define PARSE_LINE_HPP

#include <string>

#include "dictionaryCollection.hpp"

namespace belokurskaya
{
  void parseLine(char* line, std::string& dict_name, Dictionary& dict);
}

#endif
