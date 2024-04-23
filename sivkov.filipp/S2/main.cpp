#include <iostream>
#include <fstream>
#include <string>
#include "queue.hpp"
#include "infixToPostfix.hpp"
#include "utilities.hpp"
#include "calcultPostfix.hpp"

int main(int argc, char* argv[])
{
  using namespace sivkov;
  Queue< Queue< std::string > > postfix;
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
  Queue< std::string > infix1;
  Queue< long long > res;
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
  res.reverse();
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

