#include "outputResult.hpp"
#include "iostream"

void zakozhurnikova::outputResult(std::ostream& out, Stack< ll >& result)
{
  if (!result.empty())
  {
    out << result.top();
    result.drop();
  }
  while (!result.empty())
  {
    out << " ";
    out << result.top();
    result.drop();
  }
  out << '\n';
}
