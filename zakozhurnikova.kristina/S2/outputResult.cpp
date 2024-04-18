#include "outputResult.hpp"
#include "iostream"

void zakozhurnikova::outputResult(std::ostream& out, Stack< ll >& result)
{
  unsigned long long quantity = 0;
  while (!result.empty())
  {
    if (quantity != 0)
    {
      out << " ";
    }
    out << result.top();
    result.drop();
    ++quantity;
  }
  out << '\n';
}
