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

  Queue< Queue< std::string > > expr_queue;
  Stack< long long int > operands;
  Stack< long long int > results;

  try
  {
    if (argc == 1)
    {
      input_infix(std::cin, expr_queue);
    }
    else if (argc == 2)
    {
      std::ifstream input_file;
      input_file.open(argv[1]);
      input_infix(input_file, expr_queue);
    }
    else
    {
      std::cerr << "Too many arguments!\n";
      return 1;
    }
    while (!expr_queue.empty())
    {
      Queue< std::string > process_queue;
      Queue< std::string > result_queue;
      process_queue = expr_queue.back();
      expr_queue.pop();

      to_postfix(process_queue, result_queue);
      calculate_postfix(result_queue, operands);
      results.push(operands.top());
      operands.pop();
    }
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }

  if (!results.empty())
  {
    std::cout << results.top();
    results.pop();
  }
  while (!results.empty())
  {
    std::cout << " " << results.top();
    results.pop();
  }
  std::cout << "\n";
  return 0;
}
