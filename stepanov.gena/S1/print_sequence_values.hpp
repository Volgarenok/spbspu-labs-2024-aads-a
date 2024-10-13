#ifndef PRINT_SEQUENCE_VALUES_HPP
#define PRINT_SEQUENCE_VALUES_HPP

#include <iostream>
#include <string>
#include <vector>
#include "list.hpp"

namespace stepanov
{
  void print_sequence_values(const std::vector<std::pair<std::string, List<size_t>>>& sequences);
}

#endif
