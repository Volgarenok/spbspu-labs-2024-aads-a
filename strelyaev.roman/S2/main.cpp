#include <iostream>
#include <fstream>
#include "queue.hpp"
#include "stack.hpp"
#include "calculations.hpp"
#include "conversion.hpp"

int main(int argc, char * argv[])
{
  using namespace strelyaev;
  Stack< long long > results;
  if (argc == 1)
  {
    while (std::cin.good())
    {
      long long result = 0;
      try
      {
        result = calculateInfixExpression(std::cin);
      }
      catch (const std::length_error& e)
      {
        continue;
      }
      catch (const std::exception& e)
      {
        std::cerr << e.what() << "\n";
        return 1;
      }
      results.push(result);
    }
  }
  else if (argc == 2)
  {
    std::ifstream input_file(argv[1]);
    long long result = calculateInfixExpression(input_file);
    /*while (input_file.good())
    {
      long long result = 0;
      try
      {
        result = calculateInfixExpression(input_file);
      }
      catch (const std::length_error& e)
      {
        continue;
      }
      catch (const std::exception& e)
      {
        std::cerr << e.what() << "\n";
        return 1;
      }
      results.push(result);
    }*/
  }
  else
  {
    std::cerr << "Invalid cmd parameters\n";
    return 1;
  }
  while (false) //(!results.empty())
  {
    std::cout << results.drop();
    if (!results.empty())
    {
      std::cout << " ";
    }
  }
  std::cout << "\n";
}
