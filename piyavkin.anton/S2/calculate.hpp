#ifndef CALCULATE_HPP
#define CALCULATE_HPP
#include <list.hpp>
#include "queue.hpp"
#include "types.hpp"

namespace piyavkin
{
  void calculate(List< Queue< Postfix > >& postfix, List< long long >& result);
}
#endif
