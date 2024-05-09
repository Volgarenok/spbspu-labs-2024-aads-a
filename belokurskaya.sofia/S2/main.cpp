#include <iostream>
#include <fstream>
#include <string>

#include "stack.hpp"
#include "queue.hpp"
#include "evaluatePostfixExpression.hpp"
#include "infixToPostfix.hpp"

int main(int argc, char* argv[])
{
  using namespace belokurskaya;
  std::istream* input;
  std::ifstream fileInput;

  if (argc < 2)
  {
    input = &std::cin;
  }
  else
  {
    fileInput.open(argv[1]);
    if (!fileInput.is_open())
    {
      std::cerr << "Unable to open input file\n";
      return 1;
    }
    input = &fileInput;
  }

  std::string line;
  while (true)
  {
    if (!std::getline(*input, line))
    {
      break;
    }

    if (line.empty())
    {
      continue;
    }
  }
  return 0;
}
