#ifndef COMPLEMENT_FUNCTOR
#define COMPLEMENT_FUNCTOR

#include <string>

namespace erohin
{
  struct ComplementFunctor
  {
    int sum;
    std::string names;
    ComplementFunctor();
    ~ComplementFunctor();
    ComplementFunctor operator()(const std::pair< int, std::string > & pair);
  };
}

#endif
