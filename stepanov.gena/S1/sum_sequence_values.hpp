#ifndef SUM_SEQUENCE_VALUES_HPP
#define SUM_SEQUENCE_VALUES_HPP

#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include "list.hpp"

namespace stepanov
{
  void sum_sequence_values(const std::vector<std::pair<std::string, List<size_t>>>& sequences);
}

#endif
