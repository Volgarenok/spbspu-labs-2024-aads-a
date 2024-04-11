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
  while (!std::cin.eof())
  {
    Queue< detail::ExpressionUnit > infix_queue = parseString(std::cin);
    Queue< detail::ExpressionUnit > post_fix = makePostfix(infix_queue);
    long long result = 0;
    try
    {
      result = calculatePostfix(post_fix);
    }
    catch (const std::invalid_argument& e)
    {
      std::cerr << e.what() << '\n';
      return 0;
    }
    catch (const std::out_of_range& e)
    {
      continue;
    }
    results.push(result);
  }
  while (!results.empty())
  {
    std::cout << results.drop() << "\n";
  }
}
