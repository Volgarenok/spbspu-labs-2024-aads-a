#ifndef INPUT_HPP
#define INPUT_HPP
#include <istream>
#include "queue.hpp"
#include "partexpression.hpp"

namespace piyavkin
{
  void input(std::istream& in, List< Queue< char > >& queues); 
}
#endif