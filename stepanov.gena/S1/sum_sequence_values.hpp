#ifndef SUM_SEQUENCE_VALUES_HPP
#define SUM_SEQUENCE_VALUES_HPP

#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include "list.hpp"

namespace stepanov
{
  List<size_t> sum_sequence_values(const List<std::pair<std::string, List<size_t>>>& sequences);
}

#endif
