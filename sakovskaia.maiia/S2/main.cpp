#include <iostream>
#include <fstream>
#include <string>
#include "parser.hpp"

int main(int argc, char * argv[])
{
  using namespace sakovskaia;
  std::istream * input = & std::cin;
  std::ifstream file;
  if (argc > 2)
  {
    std::cerr << "Usage: " << argv[0] << " [filename]" << std::endl;
    return 1;
  }
  if (argc == 2)
  {
    file.open(argv[1]);
    if (!file.is_open())
    {
      std::cerr << "Could not open file: " << std::endl;
      return 1;
    }
    input = & file;
  }
  Queue< int > results;
  std::string line;
  try
  {
    while (std::getline(* input, line))
    {
      if (line.empty())
      {
        continue;
      }
      Queue< std::string > postfix = infix_to_postfix(line);
      int result = evaluate_postfix(postfix);
      results.push(std::move(result));
    }
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  Stack< int > outputStack;
  while (!results.empty())
  {
    outputStack.push(results.pop());
  }
  while (!outputStack.empty())
  {
    std::cout << outputStack.pop() << " ";
  }
  std::cout << std::endl;
  return 0;
}
