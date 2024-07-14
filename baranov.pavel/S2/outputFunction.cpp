#include "outputFunction.hpp"

void baranov::printResults(std::ostream & out, Stack< long long int > & results)
{
  if (results.empty())
  {
    return;
  }
  out << results.top();
  results.pop();
  while (!results.empty())
  {
    out << ' ' << results.top();
    results.pop();
  }
}

