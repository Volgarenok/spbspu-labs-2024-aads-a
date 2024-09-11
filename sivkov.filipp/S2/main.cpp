#include <iostream>
#include <fstream>
#include <string>
#include <queue.hpp>
#include "infixToPostfix.hpp"
#include "utilities.hpp"
#include "expressionEvaluation.hpp"
#include "input.hpp"

int main(int argc, char* argv[])
{
  using namespace sivkov;
  Queue< Queue< std::string > > queueOfString;
  std::ifstream file;
  if (argc == 1)
  {
    inputString(std::cin, queueOfString);
  }
  else if (argc == 2)
  {
    file.open(argv[1]);
    inputString(file, queueOfString);
  }
  else
  {
    std::cerr << "Error comand line\n";
    return 2;
  }

  Queue< long long > res;
  Queue< Queue< std::string > > postfix;
  try
  {
    while (!queueOfString.empty())
    {
      postfix.push(infixToPostfix(queueOfString.front()));
      queueOfString.pop();
    }
    while (!postfix.empty())
    {
      res.push(expressionEvaluation(postfix.front()));
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
