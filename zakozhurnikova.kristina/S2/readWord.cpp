#include "readWord.hpp"
#include <cctype>

c_iterator_t zakozhurnikova::readWord(c_iterator_t first, c_iterator_t last, std::string& dest)
{
  while(!std::isspace(*first))
  {
    if (first == last)
    {
      return first;
    }
    dest.push_back(*first++);
  }
  return ++first;
}
