#ifndef INPUTOUTPUTLIST_HPP
#define INPUTOUTPUTLIST_HPP

#include <istream>
#include <utility>
#include <string>
#include "list.hpp"

namespace chistyakov
{
  void inputList(std::istream & input, List < std::pair < std::string, List < std::size_t > > > & list);
  std::size_t maxDigit(List < std::pair < std::string, List < std::size_t > > > & list);
  void outPutNames(List < std::pair < std::string, List < std::size_t > > > & list);
  void outPutNums(List < std::pair < std::size_t, List < std::size_t > > > & list);
  void outPutSums(List < std::pair < std::size_t, List < std::size_t > > > & list);
}

#endif
