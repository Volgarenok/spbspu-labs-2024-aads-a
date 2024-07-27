#include "outputRes.hpp"
#include <iostream>

void vyzhanov::outputResult(std::ostream& out, Stack< long long >& result)
{
  if (!result.empty())
  {
    out << result.top();
    result.pop();
  }
  while (!result.empty())
  {
    out << " ";
    out << result.top();
    result.pop();
  }
}
