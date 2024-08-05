#ifndef PROCESSCOMMANDS_HPP
#define PROCESSCOMMANDS_HPP

#include <iostream>

#include "commands.hpp"

namespace gladyshev
{
  std::ostream& process_commands(std::istream& in, std::ostream& out, mainDic& findic);
}

#endif
