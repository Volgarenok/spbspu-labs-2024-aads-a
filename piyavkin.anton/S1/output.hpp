#ifndef OUTPUT_HPP
#define OUTPUT_HPP
#include <ostream>
#include <cstddef>
#include "list.hpp"

namespace piyavkin
{
  void output(std::ostream& out, const std::pair< std::string, List< unsigned int >* >* pairs, size_t size, size_t max_size_list);
}
#endif
