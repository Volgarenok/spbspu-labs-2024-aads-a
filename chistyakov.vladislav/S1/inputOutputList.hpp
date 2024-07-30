#ifndef INPUTOUTPUTLIST_HPP
#define INPUTOUTPUTLIST_HPP

#include <istream>
#include <utility>
#include <string>
#include <cstddef>
#include "list.hpp"

namespace chistyakov
{
  void inputList(std::istream & input, List < std::pair < std::string, List < size_t > > > & list);
  size_t maxDigit(List < std::pair < std::string, List < size_t > > > & list);
  void outputNames(List < std::pair < std::string, List < size_t > > > & list);
  void outputNums(List < std::pair < size_t, List < size_t > > > & list);
  void outputSums(List < std::pair < size_t, List < size_t > > > & list);
}

#endif
