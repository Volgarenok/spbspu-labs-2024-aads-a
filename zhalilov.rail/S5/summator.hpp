#ifndef SUMMATOR_HPP
#define SUMMATOR_HPP

#include <string>

#include <list/list.hpp>

namespace zhalilov
{
  struct Summator
  {
    void operator()(const std::pair < int, std::string > pair);
    int result_ = 0;
    List < std::string > values_;
  };
}

#endif
