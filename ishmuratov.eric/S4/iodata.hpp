#ifndef IODATA_HPP
#define IODATA_HPP

#include "cmd.hpp"

namespace ishmuratov
{
  void input_dict(data_t & data, std::istream & input);
  void output_dict(data_t & data, std::ostream & output);
}

#endif
