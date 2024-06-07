#ifndef INPUT_HPP
#define INPUT_HPP

#include <iostream>
#include <tree.hpp>
#include <bdlist.hpp>

namespace ishmuratov
{
  using value_t = List< std::string >;
  using unit_t = AVLTree< std::string, value_t >;
  using dict_t = AVLTree< std::string, unit_t >;

  void input_dictionary(dict_t & dictionaries, std::istream & input);
  void print_help(std::ostream & output);
}

#endif
