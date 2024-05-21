#ifndef COMPLEMENT_FUCNTOR
#define COMPLEMENT_FUCNTOR

#include <string>

namespace erohin
{
  struct ComplementFunctor
  {
    int sum = 0;
    std::string names;
    ComplementFunctor operator()(const std::pair< int, std::string > & pair);
  };
}

#endif
