#include <iostream>
#include <fstream>
#include "queue.hpp"
#include "stack.hpp"
#include "checks.hpp"
#include "infix_operations.hpp"
#include "postfix_operations.hpp"

int main(int argc, char * argv[])
{
  using namespace ishmuratov;
  std::istream * input;
  std::ifstream input_file;

  if (argc == 1)
  {
    input = &std::cin;
  }
  else if (argc == 2)
  {
    input_file.open(argv[1]);
    input = &input_file;
  }
  else
  {
    std::cerr << "Too many arguments!\n";
    return 1;
  }

  Stack< std::string > process_stack;
  Queue< std::string > process_queue;
  Queue< std::string > result_queue;
  Stack< long long int > operands;
  Stack< long long int > results;
  std::string line;

  try
  {
    while (std::getline(*input, line))
    {
      if (!line.empty())
      {
        input_infix(line, process_queue);
        topostfix(process_queue, result_queue);
        calculate_postfix(result_queue, operands);
        results.push(operands.top());
      }
    }
  }
  catch (std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }

  if (!results.empty())
  {
    std::cout << results.drop();
  }
  while (!results.empty())
  {
    std::cout << " " << results.drop();
  }
  std::cout << "\n";
  return 0;
}
