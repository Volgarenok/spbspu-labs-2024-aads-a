#ifndef INPUT_HPP
#define INPUT_HPP
#include <istream>
#include "queue.hpp"
#include "types.hpp"

namespace piyavkin
{
  void input(std::istream& in, List< Queue< InputType > >& queues);
}
#endif
