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
  if (argc < 2)
  {
    std::cerr << "Invalid command line args\n";
    return 1;
  }

  const std::string inputFileName = argv[1];
  std::ifstream inputFile(inputFileName);
  if (!inputFile.is_open())
  {
    std::cerr << "Unable to open input file\n";
    return 1;
  }

  std::string line;
  while (std::getline(inputFile, line))
  {
    if (line.empty())
    {
      continue;
    }
  }
  return 0;
}
