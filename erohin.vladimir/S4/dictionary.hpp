#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <map>
#include <string>

namespace erohin
{
  struct Dictionary
  {
    std::string name;
    std::map< size_t, std::string > data;
  };
}

#endif
