#include "outputFunctions.hpp"

void baranov::printNames(std::ostream & output, ds_t & list)
{
  auto end = list.end();
  for(auto i = list.begin(); i != end; ++i)
  {
    output << i->first;
    output << ' ';
    if (i + 1 == end)
    {
      output << '\n';
    }
  }
}

