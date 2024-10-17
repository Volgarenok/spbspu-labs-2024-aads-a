#include "convertinfixtopostfix.hpp"
#include <string>
#include <stdexcept>
#include "queue.hpp"
#include "stack.hpp"

namespace
{
  int getOperatorPriority(std::string op)
  {
    if (op == "*" || op == "/" || op == "%")
    {
      return 2;
    }
    else if (op == "+" || op == "-")
    {
      return 1;
    }
    else if (op == "(" || op == ")")
    {
      return 0;
    }
    else
    {
      throw std::logic_error("Invalid operator");
    }
  }

  bool isHigherPriority(std::string op1, std::string op2)
  {
    return getOperatorPriority(op1) >= getOperatorPriority(op2);
  }

  bool isOperator(std::string op)
  {
    return op == "*" || op == "/" || op == "+" || op == "-" || op == "(" || op == ")" || op == "%";
  }
}

agarkov::Queue< std::string > agarkov::convertInfixToPostfix(agarkov::Queue< std::string >& infixQueue)
{
  agarkov::Queue< std::string > postfixQueue;
  agarkov::Stack< std::string > stack;

  return postfixQueue;
}

 
