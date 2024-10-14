#ifndef READ_SEQUENCESS_HPP
#define READ_SEQUENCESS_HPP

#include <iostream>
#include <vector>
#include <string>
#include "list.hpp"

namespace stepanov
{
  void read_sequences(std::vector<std::pair<std::string, List<size_t>>>& sequences);
}

#endif
