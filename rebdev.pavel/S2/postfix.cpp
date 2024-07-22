#include "postfix.hpp"

#include <stack>
#include <iostream> //del

void rebdev::makePostFix(std::string & str, postFixQueue & queue)
{
  size_t lastIndex = 0, index = 0;
  std::stack< token > mathStack;
  while (index < (str.size() - 1))
  {
    index = str.find(' ', lastIndex);
    if (index == std::string::npos)
    {
      index = str.size();
    }
    std::cout << "Start index: " << lastIndex << " " << index << '\n'; //del

    std::string strPart;
    strPart.assign(str, lastIndex, (index - lastIndex));
    if (((strPart.size()) == 1) && (!isdigit(strPart[0])))
    {
      token operTok(strPart[0]);

      if (strPart[0] == ')')
      {
        while (!mathStack.top().leftBracket())
        {
          queue.push(mathStack.top());
          mathStack.pop();
        }
        mathStack.pop();
      }
      else
      {
        if (!mathStack.empty())
        {
          while (mathStack.top().priority() >= operTok.priority())
          {
            queue.push(mathStack.top());
            mathStack.pop();
          }
        }
        mathStack.push(operTok);
      }
    }
    else
    {
      token numTok(std::stoll(strPart));
      queue.push(numTok);
    }

    lastIndex = index + 1;
    std::cout << "end index: " << lastIndex << " " << index << '\n'; //del
  }
}
long long rebdev::postFixToResult(postFixQueue & queue)
{
  std::stack< token > resultStack;
  while (!queue.empty())
  {
    resultStack.push(queue.front());
    queue.pop();
    if (!resultStack.top().isNum())
    {
      auto oper = resultStack.top();
      resultStack.pop();
      auto first = resultStack.top();
      resultStack.pop();
      auto second = resultStack.top();
      resultStack.pop();
      resultStack.push(oper(first, second));
    }
  }
  return resultStack.top().getNum();
}
