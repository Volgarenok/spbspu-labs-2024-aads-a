#include <iostream>
#include <fstream>
#include "parser.hpp"
#include "queue.hpp"

int main(int argc, char* argv[])
{
  if (argc > 2)
  {
    std::cerr << "Usage: " << argv[0] << "[filename]" << "\n";
    return 1;
  }
  std::ifstream file;
  if (argc == 2)
  {
    file.open(argv[1]);
    if (!file.is_open())
    {
      std::cerr << "Error opening file: " << argv[1] << "\n";
      return 1;
    }
  }

  std::string expression = "";
  spiridonov::Parser parser;
  spiridonov::Queue< int > results;

  while ((argc == 1 && std::getline(std::cin, expression)) ||
    (argc == 2 && std::getline(file, expression)))
  {
    try
    {
      int result = parser.parseExpression(expression);
      results.push(result);
    }
    catch (const std::exception& e)
    {
      std::cerr << "Error: " << e.what() << "\n";
      return 1;
    }
  }

  if (argc == 2)
  {
    file.close();
  }

  while (!results.isEmpty())
  {
    std::cout << results.getTop() << " ";
    results.pop();
  }

  std::cout << "\n";

  return 0;
}
