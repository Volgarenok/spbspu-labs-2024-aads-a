#ifndef INPUT_DICT_HPP
#define INPUT_DICT_HPP

#include <istream>
#include <tree.hpp>

namespace namestnikov
{
  Tree< int, std::string > inputDict(std::istream & in);
}

#endif
