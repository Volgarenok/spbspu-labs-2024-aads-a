#ifndef CMD_HPP
#define CMD_HPP

#include <iostream>
#include <map>
#include <list>

namespace ishmuratov
{
  using dataset_t = std::map< int, std::string >;
  using data_t = std::map< std::string, dataset_t >;

  void print(data_t & data, std::istream & input, std::ostream & output);
  void complement(data_t & data, std::istream & input, std::ostream & output);
  void intersect(data_t & data, std::istream & input, std::ostream & output);
  void uniond(data_t & data, std::istream & input, std::ostream & output);
}

#endif
