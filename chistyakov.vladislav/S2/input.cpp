#include "input.hpp"

void chistyakov::inputExp(Stack< Queue< std::string > > & result, std::istream & in)
{
  while (in)
  {
    std::string exp;
    std::getline(in, exp);

    if (!in || exp == "")
    {
      continue;
    }

    Queue< std::string > queue;
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

    result.push(queue);
  }
}
