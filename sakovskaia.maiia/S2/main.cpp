#include <iostream>
#include <fstream>
#include <string>
#include "parser.hpp"

int main()
{
  using namespace sakovskaia;
  std::istream * input = & std::cin;
  std::ifstream file;
  std::string filename;
  if (argc > 2)
  {
    std::cerr << "Usage: " << argv[0] << " [filename]" << std::endl;
    return 1;
  }
  if (argc == 2)
  {
    filename = argv[1];
    file.open(filename);
    if (!file.is_open())
    {
      std::cerr << "Could not open file: " << filename << std::endl;
      return 1;
    }
    input = & file;
  }
  Queue< int > results;
  try
  {
    std::string line;
    while (std::getline(* input, line))
    {
      if (line.empty())
      {
        continue;
      }
      Queue< std::string > postfix = infix_to_postfix(line);
      int result = evaluate_postfix(postfix);
      results.push(result);
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
