#ifndef SUMFUNC_HPP
#define SUMFUNC_HPP

#include <string>

namespace gladyshev
{
  struct Key_summ
  {
    void operator()(const std::pair< const int, std::string > & value);
    int result = 0;
    std::string elems;
  };
}

#endif
