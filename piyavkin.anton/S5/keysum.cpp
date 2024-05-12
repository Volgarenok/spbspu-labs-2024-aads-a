#include "keysum.hpp"

void piyavkin::KeySum::operator()(const std::pair< int, std::string >& val)
{
  str = str + " " + val.second;
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