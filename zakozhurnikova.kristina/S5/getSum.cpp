#include "getSum.hpp"
#include <stdexcept>

zakozhurnikova::KeySum::KeySum():
  result_(0),
  line_()
{}

void zakozhurnikova::KeySum::operator()(std::pair< int, std::string > data)
{
  int maxNum = std::numeric_limits< int >::max();
  int minNum = std::numeric_limits< int >::min();
  if ((result_ > 0 && maxNum - result_ < data.first) || (result_ < 0 && data.first < 0 && minNum - result_ > data.first))
  {
    throw std::overflow_error("Error: Addition overflow");
  }
  result_ += data.first;
  line_ += data.second + ' ';
}

int zakozhurnikova::KeySum::getResult() const
{
  return result_;
}

std::string zakozhurnikova::KeySum::getLine() const
{
  return line_;
}
