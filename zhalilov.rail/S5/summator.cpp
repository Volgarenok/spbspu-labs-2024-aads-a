#include "summator.hpp"

void zhalilov::Summator::operator()(const std::pair < int, std::string > pair)
{
  result_ += pair.first;
  values_ += ' ' + pair.second;
}
