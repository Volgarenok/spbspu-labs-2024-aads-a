#include "getInfix.hpp"

#include <string>
#include <istream>

void zhalilov::getInfixFromString(Queue< InfixToken > &queue, const std::string &str)
{
  size_t i = 0;
  size_t tmp = 0;
  long long number = 0;
  while (i < str.size())
  {
    if (!std::isspace(str[i]))
    {
      InfixToken undefinedTkn;
      try
      {
        number = std::stoll(str.substr(i), &tmp);
        undefinedTkn = InfixToken(Operand(number));
        i += tmp;
      }
      catch (...)
      {
        try
        {
          undefinedTkn = InfixToken(Bracket(str[i]));
        }
        catch (...)
        {
          undefinedTkn = InfixToken(BinOperator(str[i]));
        }
      }
      queue.push(undefinedTkn);
    }
    i++;
  }
}

void zhalilov::getInfixesFromStream(Stack< Queue< InfixToken > > &stack, std::istream &in)
{
  std::string str;
  while (std::getline(in, str))
  {
    Queue< InfixToken > temp;
    getInfixFromString(temp, str);
    if (!str.empty())
    {
      stack.push(temp);
    }
  }
}
