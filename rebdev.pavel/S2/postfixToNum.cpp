#include "postfixToNum.hpp"

#include <cstddef>

#include "myStack.hpp"
#include "node.hpp"

long long rebdev::convertPostfixToNum(queue< node > & postfixQueue)
{
  long long result = 0;
  Stack< node > mathStack;

  while (postfixQueue.size() > 0)
  {
    node element = postfixQueue.front();
    postfixQueue.pop();

    if (element.getPriority() == 0)
    {
      mathStack.push(element);
    }
    else
    {
      long long numArr[2]{};
      for (size_t i = 0; i < 2; ++i)
      {
        node ok = mathStack.drop();
        numArr[i] = ok.getResult();
      }
      mathStack.push(element.getResult(numArr[1], numArr[0]));
    }
  }

  node ok = mathStack.drop();
  result = ok.getResult();

  return result;
}
