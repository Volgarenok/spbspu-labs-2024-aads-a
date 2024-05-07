#ifndef READWORD_HPP
#define READWORD_HPP
#include <string>

using c_iterator_t = std::string::const_iterator;
namespace zakozhurnikova
{
  c_iterator_t readWord(c_iterator_t first, c_iterator_t last, std::string& dest);
}

#endif

