#ifndef OUTPUT_FUNC_HPP 
#define OUTPUT_FUNC_HPP 

#include <ostream>
#include "forwardlist.hpp"

namespace agarkov
{
  using pair_t = std::pair< std::string, ForwardList< size_t > >;
  void outputName(std::ostream& out, const ForwardList< pair_t >& lists);
  void outputNum(std::ostream& out, const ForwardList< pair_t >& lists);
  void outputSum(std::ostream& out, const ForwardList< pair_t >& lists);
}

#endif
