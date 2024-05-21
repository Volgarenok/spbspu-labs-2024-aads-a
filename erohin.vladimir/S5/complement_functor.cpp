#include "complement_functor.hpp"
#include <string>

erohin::ComplementFunctor erohin::ComplementFunctor::operator()(const std::pair< int, std::string > &)
{
  return *this;
}
