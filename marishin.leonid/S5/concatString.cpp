#include "concatString.hpp"

marishin::ConcatString::ConcatString():
  result_("")
{}

void marishin::ConcatString::operator()(const std::string & str)
{
  result_ += " " + str;
}

std::string marishin::ConcatString::getResult() const
{
  return result_;
}
