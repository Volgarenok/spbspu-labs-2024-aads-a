#include "calculatePostfix.hpp"
#include <utility>
#include <stdexcept>
#include "stack.hpp"
#include "tokenType.hpp"
#include "safeMathFunctions.hpp"
#include "getExpression.hpp"
#include "postfixFromInfix.hpp"

std::pair< long long int, long long int > getTwoFirst(grechishnikov::Stack< long long int >& stack);

long long int grechishnikov::calculatePostfix(const Queue< std::string >& postfix)
{
  Queue< std::string > tempPostfix = postfix;
  Stack< long long int > calcStack;
  while (!tempPostfix.empty())
  {
    if (!isOperator(tempPostfix.top()))
    {
      calcStack.push(std::stoll(tempPostfix.top()));
      tempPostfix.pop();
    }
    else
    {
      auto firstTwo = getTwoFirst(calcStack);
      if (tempPostfix.top() == "+")
      {
        calcStack.push(addTwo(firstTwo.first, firstTwo.second));
      }
      if (tempPostfix.top() == "-")
      {
        calcStack.push(subtractTwo(firstTwo.first, firstTwo.second));
      }
      if (tempPostfix.top() == "*")
      {
        calcStack.push(multiplyTwo(firstTwo.first, firstTwo.second));
      }
      if (tempPostfix.top() == "/")
      {
        calcStack.push(divideTwo(firstTwo.first, firstTwo.second));
      }
      if (tempPostfix.top() == "%")
      {
        calcStack.push(modTwo(firstTwo.first, firstTwo.second));
      }
      tempPostfix.pop();
    }
  }
  if (calcStack.size() != 1)
  {
    throw std::logic_error("Mathematical expression is incorrect");
  }
  return calcStack.top();
}

grechishnikov::Stack< long long int > grechishnikov::calculateExpressions(std::istream& in)
{
  std::string str;
  Stack< long long > res;
  while (!in.eof())
  {
    getline(in, str);
    if (in.eof() || str == "")
    {
      continue;
    }
    Queue< std::string > initExpr;
    Queue< std::string > postExpr;
    initExpr = getExpression(str);
    postExpr = postfixFromInfix(initExpr);
    res.push(calculatePostfix(postExpr));
  }
  return res;
}


std::pair< long long int, long long int > getTwoFirst(grechishnikov::Stack< long long int >& stack)
{
  if (stack.size() < 2)
  {
    throw std::logic_error("Not enough elements for the operation");
  }
  long long int second = stack.top();
  stack.pop();
  long long int first = stack.top();
  stack.pop();
  return std::pair< long long int, long long int >{ first, second };
}
