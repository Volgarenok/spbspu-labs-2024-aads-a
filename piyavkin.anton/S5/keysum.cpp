#include "keysum.hpp"
#include <limits>
#include <stdexcept>

bool isOverflow(int lhs, int rhs)
{
  int min = std::numeric_limits< int >::min();
  int max = std::numeric_limits< int >::max();
  return (lhs > 0 && max - lhs < rhs) || (lhs < 0 && rhs < 0 && min - lhs > rhs);
}

void piyavkin::KeySum::operator()(const std::pair< int, std::string >& val)
{
  str += " " + val.second;
  if (isOverflow(key, val.first))
  {
    throw std::overflow_error("Owerflow");
  }
  key += val.first;
}

int piyavkin::KeySum::getKey() const
{
  return key;
}

std::string piyavkin::KeySum::getVal() const
{
  return str;
}
