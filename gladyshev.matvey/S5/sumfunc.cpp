#include "sumfunc.hpp"

#include <stdexcept>
#include <limits>

void gladyshev::Key_summ::operator()(const std::pair< const int, std::string >& value)
{
  bool firstCheck = (result > 0 && value.first > std::numeric_limits< int >::max() - result);
  bool secCheck = ((result < 0 && value.first < 0) && (value.first < std::numeric_limits< int >::min() - result));
  if (firstCheck || secCheck)
  {
    throw std::overflow_error("overflow");
  }
  result += value.first;
  elems += ' ' + value.second;
}
