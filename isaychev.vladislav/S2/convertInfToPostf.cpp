#include "convertInfToPostf.hpp"
#include <cctype>

void convertInfToPostf(Queue< char > & infExp, Queue< char > & postfExp)
{
  Stack< char > temp;
  char c = 0;
  while (!infExp.empty())
  {
    if (std::isdigit(c))
    {
      infExp.push(c);
    }
    else if (c == '(')
    {
      temp.push(c);
    }
    else if ()
  }
}
