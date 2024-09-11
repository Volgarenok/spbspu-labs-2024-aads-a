#ifndef INPUT_HPP
#define INPUT_HPP

#include <string>

using input_it_t = std::string::const_iterator;
namespace marishin
{
  input_it_t input(input_it_t first, input_it_t second, std::string& dest);
}

#endif
