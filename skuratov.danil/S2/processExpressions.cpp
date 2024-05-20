#include "processExpressions.hpp"

void skuratov::printReverse(const Queue< long long int >& queue)
{
  Queue< long long int > temp = queue;
  Stack< long long int > stack;

  while (!temp.empty())
  {
    stack.push(temp.front());
    temp.drop();
  }

  while (!stack.empty())
  {
    std::cout << stack.top() << ' ';
    stack.drop();
  }
}

void skuratov::processExpressions(const Queue< Queue < std::string > >& exp)
{
  Queue< Queue< long long int > > results;

  auto expCopy = exp;
  while (!expCopy.empty())
  {
    try
    {
      auto lineQueue = expCopy.front();
      expCopy.drop();

      std::string expression;
      while (!lineQueue.empty())
      {
        expression += lineQueue.front();
        lineQueue.drop();
      }

      std::string postfixExp = infixToPostfix(expression);
      Queue< long long int > resultQueue;
      evaluatePostfixExpression(postfixExp);
      results.push(resultQueue);
    }
    catch (...)
    {
      throw;
    }
  }

  Queue< long long int > finalResults;
  while (!results.empty())
  {
    if (!results.front().empty())
    {
      finalResults.push(results.front().front());
    }
    results.drop();
  }

  Stack< long long int > reverseStack;
  while (!finalResults.empty())
  {
    reverseStack.push(finalResults.front());
    finalResults.drop();
  }

  while (!reverseStack.empty())
  {
    std::cout << reverseStack.top() << ' ';
    reverseStack.drop();
  }
  std::cout << '\n';
}
