#ifndef INPUTDATA_HPP
#define INPUTDATA_HPP

#include <iosfwd>
#include "queue.hpp"

namespace arakelyan
{
  void readData(std::istream &input, Queue< long long > &someQ);
}
#endif
