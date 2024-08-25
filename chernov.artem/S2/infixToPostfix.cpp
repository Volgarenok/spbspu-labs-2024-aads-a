#include "infixToPostfix.hpp"
#include <string>
#include <cstddef>

void chernov::inputInfix(std::istream& in, Queue< queue >& infix_queue)
{
  std::string str = "";
  std::string detail = "";
  while (std::getline(in, str, '\n'))
  {
    queue temp;
    detail = "";
    if (!str.empty())
    {
      for (size_t j = 0; j < str.length(); j++)
      {
        if (!std::isspace(str[j]))
        {
          detail += str[j];
          if (str.length() - 1 == j)
          {
	    temp.push(detail);
          }
        }
        else if (!detail.empty())
        {
          temp.push(detail);
          detail = "";
        }
      }
      infix_queue.push(temp);
    }
  }
}
