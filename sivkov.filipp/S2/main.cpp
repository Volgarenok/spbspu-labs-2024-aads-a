#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <string>
#include "infixToPostfix.hpp"
#include "utilities.hpp"
#include "calcultPostfix.hpp"

int main(int argc, char* argv[])
{
  std::queue <std::queue< std::string >> postfix;
  std::istream* input;
  std::ifstream file;

  if (argc == 1)
  {
    input = &std::cin;
  }
  else if (argc == 2)
  {
    file.open(argv[1]);
    input = &file;
  }
  else
  {
    std::cerr << "Error comand line\n";
    return 2;
  }

  std::string in = "";
  std::string token = "";
  std::queue< std::string > infix1;
  std::queue<long long> res;
  try
  {
    while (std::getline(*input, in))
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
    while (!postfix.empty())
    {
      res.push(calcult(postfix.front()));
      postfix.pop();
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
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

