#ifndef INPUTOUTPUT_HPP
#define INPUTOUTPUT_HPP

#include <cstddef>
#include "list.hpp"

void outputNames(List<std::pair<std::string, List<size_t>>>& list);
void outputSums(List<size_t> &numbers);
void input(std::istream& input, List<std::pair<std::string, List<size_t>>>& list);
void outputNums(List<std::pair<std::string, List<size_t>>>& list, List<size_t>& numbers);

#endif
