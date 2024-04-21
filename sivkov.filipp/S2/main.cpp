#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <string>
#include "infixToPostfix.hpp"
#include "utilities.hpp"
#include "calcultPostfix.hpp"

int main()
{
  std::string in = "";
  std::queue< std::string > infix1;
  std::string token = "";
  std::stack< std::string > oper;
  std::queue <std::queue< std::string >> postfix;

  while (std::getline(std::cin, in))
  {
    if (in == "")
    {
      continue;
    }
    for (size_t i = 0; i < in.length(); ++i)
    {
      token = "";
      while (i < in.length() && !std::isspace(in[i]))
      {
        token += in[i];
        ++i;
      }
      infix1.push(token);
    }
    postfix.push(infixToPostfix(infix1));
  }

  std::queue<long long> res;

  while (!postfix.empty())
  {
    res.push(calcult(postfix.front()));
    postfix.pop();
  }

  bool second = true;
  while (!res.empty())
  {
    if (!second)
    {
      std::cout << " ";
    }
    second = false;
    std::cout << res.front();
    res.pop();
  }
  std::cout << "\n";
  return 0;
}
