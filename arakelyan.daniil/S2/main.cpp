#include <iostream>
#include <fstream>
#include <exception>
#include <stdexcept>

#include <list/binList.hpp>
#include "queue.hpp"
#include "stack.hpp"
#include "expressionObject.hpp"
#include "inputData.hpp"
#include "transformToPostfix.hpp"
#include "calculateProc.hpp"

int main(int argc, char *argv[])
{
  using namespace arakelyan;
  Queue< Queue< ExpressionObj > > qOfInfQs;

  try
  {
    if (argc == 2)
    {
      std::ifstream inputFile(argv[1]);
      readDataInInfixFormat(inputFile, qOfInfQs);
      if (qOfInfQs.empty())
      {
        std::cout << "\n";
        return 0;
      }
    }
    else
    {
      readDataInInfixFormat(std::cin, qOfInfQs);
    }
  }
  catch (const std::out_of_range &e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }


  Queue< Queue< ExpressionObj > > qOfPostQs;
  try
  {
    while (!qOfInfQs.empty())
    {
      Queue< ExpressionObj > postQ = transformInfixToPostfix(qOfInfQs.front());
      qOfInfQs.pop();
      qOfPostQs.push(postQ);
    }
  }
  catch (const std::logic_error &e)
  {
    std::cout << "Error: " << e.what() << "\n";
    return 1;
  }

  Stack< long long > answQ;
  try
  {
    while (!qOfPostQs.empty())
    {
      calculatePostfixQ(qOfPostQs, answQ);
    }
  }
  catch (const std::exception &e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }


  while (!answQ.empty())
  {
    std::cout << answQ.top();
    answQ.pop();
    if (answQ.size() != 0)
    {
      std::cout << " ";
    }
  }
  std::cout << "\n";
  return 0;
}
