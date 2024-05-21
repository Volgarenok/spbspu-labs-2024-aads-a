#include "complement_functor.hpp"
#include <string>
#include <limits>
#include <stdexcept>

#include <iostream>

erohin::ComplementFunctor erohin::ComplementFunctor::operator()(const std::pair< int, std::string > & pair)
{
  if (sum > 0 && std::numeric_limits< int >::max() - sum < pair.first)
  {
    throw std::overflow_error("Overflow of number");
  }
  else if (sum < 0 && pair.first < 0 && std::numeric_limits< int >::min() - sum > pair.first)
  {
    throw std::underflow_error("Underflow of number");
  }
  std::cout << sum << " " << pair.first << "\n";
  sum += pair.first;
  names += (' ' + pair.second);
  return *this;
}
