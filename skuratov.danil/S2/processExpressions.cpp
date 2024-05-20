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

void skuratov::processExpressions(const List< std::string >& exp)
{
  List< Queue< long long int > > results;

  for (auto it = exp.cbegin(); it != exp.cend(); ++it)
  {
    try
    {
      std::string postfixExp = infixToPostfix(*it);
      Queue< long long int > resultQueue;
      evaluatePostfixExpression(postfixExp, resultQueue);
      results.pushBack(resultQueue);
    }
    catch (...)
    {
      throw;
    }
  }

  List< long long int > finalResults;
  for (auto it = results.cbegin(); it != results.cend(); ++it)
  {
    if (!it->empty())
    {
      finalResults.pushBack(it->front());
    }
  }

  Stack< long long int > reverseStack;
  for (auto it = finalResults.cbegin(); it != finalResults.cend(); ++it)
  {
    reverseStack.push(*it);
  }

  bool isFirstResult = true;
  while (!reverseStack.empty())
  {
    if (!isFirstResult)
    {
      std::cout << ' ';
    }
    std::cout << reverseStack.top();
    reverseStack.drop();
    isFirstResult = false;
  }
  std::cout << '\n';
}
