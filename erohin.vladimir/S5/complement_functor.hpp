#ifndef COMPLEMENT_FUCNTOR
#define COMPLEMENT_FUCNTOR

#include <string>

namespace erohin
{
  struct ComplementFunctor
  {
    long long sum = 0;
    std::string names;
    void operator()(const std::pair< int, std::string > & pair);
  };
}

#endif
