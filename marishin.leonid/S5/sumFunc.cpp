#include "sumFunc.hpp"

marishin::SumFunc::SumFunc()
{}

void marishin::SumFunc::operator()(const std::pair< const int, std::string > & data)
{
  sumNum_(data.first);
  concatString_(data.second);
}

int marishin::SumFunc::getResult() const
{
  return sumNum_.getResult();
}

std::string marishin::SumFunc::getLine() const
{
  return concatString_.getResult();
}
