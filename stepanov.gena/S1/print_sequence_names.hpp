#ifndef PRINT_SEQUENCE_NAMES_HPP
#define PRINT_SEQUENCE_NAMES_HPP

#include <iostream>
#include <vector>
#include <string>
#include "list.hpp"

namespace stepanov
{
  void print_sequence_names(const List<std::pair<std::string, List<size_t>>>& sequences);
}


#endif
