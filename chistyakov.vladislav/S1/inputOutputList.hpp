#ifndef INPUTOUTPUTLIST_HPP
#define INPUTOUTPUTLIST_HPP

#include <istream>
#include <utility>
#include <string>
#include "list.hpp"

namespace chistyakov
{
  void inputList(std::istream & input, List < std::pair < std::string, List < int > > > & list);
  int maxDigit(List < std::pair < std::string, List < int > > > & list);
  void outPutNames(List < std::pair < std::string, List < int > > > & list);
  void outPutNums(List < std::pair < int, List < int > > > & list);
  void outPutSums(List < std::pair < int, List < int > > > & list);
}

#endif
