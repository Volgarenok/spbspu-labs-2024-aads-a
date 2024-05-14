#include "keysum.hpp"
#include <limits>
#include <stdexcept>

bool isOverflow(int lhs, int rhs)
{
  int min = std::numeric_limits< int >::min();
  int max = std::numeric_limits< int >::max();
  return (lhs > 0 && max - lhs < rhs) || (lhs < 0 && rhs < 0 && min - lhs > rhs);
}

piyavkin::KeySum::KeySum():
  key_(0),
  str_()
{}

void piyavkin::KeySum::operator()(const std::pair< int, std::string >& val)
{
  if (val.second != "")
  {
    str_ += " " + val.second;
  }
  if (isOverflow(key_, val.first))
  {
    throw std::overflow_error("Owerflow");
  }
  key_ += val.first;
}

int piyavkin::KeySum::getKey() const
{
  return key_;
}

std::string piyavkin::KeySum::getVal() const
{
  return str_;
}
