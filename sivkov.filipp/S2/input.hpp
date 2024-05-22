#ifndef INPUT_HPP
#define INPUT_HPP

#include <iostream>
#include <string>
#include "queue.hpp"

namespace sivkov
{
  void inputString(std::istream& input, Queue< Queue< std::string > >& queueOfString);
}

#endif
