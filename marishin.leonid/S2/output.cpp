#include "output.hpp"
#include <iostream>

void marishin::output(std::ostream& out, Stack< long long >& value)
{
  if (!value.empty())
  {
    out << value.top();
    value.drop();
  }
  while (!value.empty())
  {
    out << " ";
    out << value.top();
    value.drop();
  }
}
