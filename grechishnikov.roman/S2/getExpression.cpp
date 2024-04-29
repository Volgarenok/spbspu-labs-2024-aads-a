#include "getExpression.hpp"
#include "tokenType.hpp"

grechishnikov::Queue< std::string > grechishnikov::getExpression(const std::string& str)
{
  Queue< std::string > tempQ;
  std::string tempS = "";
  for (size_t pars = 0; pars != str.size(); pars++)
  {
    if (std::isspace(str[pars]))
    {
      if (tempS == "")
      {
        continue;
      }
      tempQ.push(tempS);
      tempS = "";
    }
    else
    {
      tempS.push_back(str[pars]);
    }
  }
  if (tempS != "")
  {
    tempQ.push(tempS);
  }
  return tempQ;
}
