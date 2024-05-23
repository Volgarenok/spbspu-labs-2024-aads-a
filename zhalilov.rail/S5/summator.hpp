#ifndef SUMMATOR_HPP
#define SUMMATOR_HPP

#include <string>

namespace zhalilov
{
  struct Summator
  {
    void operator()(const std::pair< int, std::string > pair);
    int result_ = 0;
    std::string values_;
  };
}

#endif
