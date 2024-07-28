#include "outputRes.hpp"
#include <iostream>

void vyzhanov::outputResult(std::ostream& output, Stack< long long >& results)
{
  if (!results.empty())
  {
    output << results.top();
    results.pop();
  }
  while (!results.empty())
  {
    output << " ";
    output << results.top();
    results.pop();
  }
}
