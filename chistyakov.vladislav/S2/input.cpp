#include "input.hpp"

void chistyakov::inputExp(Queue< std::string > & queue, const std::string & exp)
{
  std::string number;
  for (size_t i = 0; i < exp.size(); i++)
  {
    if (isdigit(exp[i]))
    {
      number += exp[i];
    }
    else
    {
      if (!number.empty())
      {
        queue.push(number);
        number = "";
      }

      if (exp[i] == ' ')
      {
        continue;
      }
      else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/' || exp[i] == '%' || exp[i] == '(' || exp[i] == ')')
      {
        std::string sign;
        sign += exp[i];
        queue.push(sign);
      }
      else
      {
        std::cerr << "Bad input\n";
      }
    }
  }

  if (!number.empty())
  {
    queue.push(number);
  }
}
