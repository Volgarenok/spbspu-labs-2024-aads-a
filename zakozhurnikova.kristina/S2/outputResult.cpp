#include "outputResult.hpp"
#include "iostream"

void outputResult(zakozhurnikova::Stack< ll >& result)
{
  long long quantity = 0;
  while(!result.empty())
  {
    std::cout << result.top();
    result.drop();
    if(quantity != 0 && !result.empty())
    {
      std::cout << " ";
    }
    ++quantity;
  }
}
