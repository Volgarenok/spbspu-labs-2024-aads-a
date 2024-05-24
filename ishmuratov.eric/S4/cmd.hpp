#ifndef CMD_HPP
#define CMD_HPP

#include <iostream>
#include "tree.hpp"

namespace ishmuratov
{
  using dataset_t = AVLTree< int, std::string >;
  using data_t = AVLTree< std::string, dataset_t >;

  void print(const data_t & data, std::istream & input, std::ostream & output);
  void complement(data_t & data, std::istream & input);
  void intersect(data_t & data, std::istream & input);
  void uniond(data_t & data, std::istream & input);
}

#endif
