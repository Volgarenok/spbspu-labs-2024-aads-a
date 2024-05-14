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
  Queue< Queue< Key > > infixQueue;
  try
  {
    if (argc == 1)
    {
      inputExpressions(std::cin, infixQueue);
    }
    else if (argc == 2)
    {
      std::ifstream in(argv[1]);
      if (!in.is_open())
      {
        std::cerr << "Can not open the file\n";
        return 1;
      }
      inputExpressions(in, infixQueue);
      if (infixQueue.empty())
      {
        std::cout << "\n";
        return 0;
      }
      in.close();
    }
    else
    {
      std::cerr << "Wrong input arguments\n";
      return 1;
    }
    Stack< long long > results;
    while (!infixQueue.empty())
    {
      Queue< Key > tmp = infixQueue.front();
      infixQueue.pop();
      Queue< Key > res;
      convertToPostfix(tmp, res);
      results.push(calculatePostfixExpression(res));
    }
    std::cout << results.top();
    results.pop();
    while (!results.empty())
    {
      std::cout << " " << results.top();
      results.pop();
    }
    std::cout << "\n";
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
}
