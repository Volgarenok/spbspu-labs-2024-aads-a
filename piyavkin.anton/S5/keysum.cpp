#include "keysum.hpp"

void piyavkin::KeySum::operator()(const std::pair< int, std::string >& val)
{
  str = str + " " + val.second;
  key += val.first;
}