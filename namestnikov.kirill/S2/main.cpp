#include <iostream>
#include <fstream>
#include <string>
#include "stack.hpp"
#include "queue.hpp"
#include "convert_to_postfix.hpp"
#include "calculate_postfix_expression.hpp"
#include "input_expressions.hpp"
#include "data_types.hpp"

int main(int argc, char * argv[])
{
  using namespace namestnikov;
  Stack < Queue< namestnikov::Key > > infixes;
  Stack< long long > results;
  Stack< Queue< namestnikov::Key > > postfixes;
  try
  {
    if (argc == 1)
    {
      inputExpressions(std::cin, infixes);
    }
    else if (argc == 2)
    {
      std::ifstream in(argv[1]);
      if (!in.is_open())
      {
        std::cerr << "Can not open file\n";
        return 1;
      }
      inputExpressions(in, infixes);
      in.close();
    }
    else
    {
      std::cerr << "Wrong count of parameters\n";
      return 1;
    }
    while (!infixes.empty())
    {
      Queue< namestnikov::Key > expression;
      convertToPostfix(infixes.top(), expression);
      postfixes.push(expression);
      infixes.pop();
    }
    while (!postfixes.empty())
    {
      results.push(calculatePostfixExpression(postfixes.top()));
      postfixes.pop();
    }
    while (!results.empty())
    {
      (results.size() != 1) ? std::cout << results.top() << " " : std::cout << results.top() << "\n";
      results.pop();
    }
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
