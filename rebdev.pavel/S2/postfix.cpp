#include "postfix.hpp"

#include <stack>
#include <stdexcept>

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

    std::string strPart;
    strPart.assign(str, lastIndex, (index - lastIndex));

    if (((strPart.size()) == 1) && (!isdigit(strPart[0])))
    {
      if (strPart[0] == ')')
      {
        while (!mathStack.top().leftBracket())
        {
          queue.push(mathStack.top());
          mathStack.pop();
        }
        mathStack.pop();
      }
      else if (strPart[0] == '(')
      {
        mathStack.push(token{strPart[0]});
      }
      else
      {
        token operTok(strPart[0]);
        if (!mathStack.empty())
        {
          while (mathStack.top().priority() >= operTok.priority())
          {
            queue.push(mathStack.top());
            mathStack.pop();

            if (mathStack.empty())
            {
              break;
            }
          }
        }
        mathStack.push(operTok);
      }
    }
    else if (strPart.size() >= 1)
    {
      queue.push(token{std::stoll(strPart)});
    }

    lastIndex = index + 1;
  }
  while (!mathStack.empty())
  {
    queue.push(mathStack.top());
    mathStack.pop();
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
      if (resultStack.size() < 3)
      {
        throw std::logic_error("Uncorrect mathematical expression!");
      }
      auto oper = resultStack.top();
      resultStack.pop();
      auto second = resultStack.top();
      resultStack.pop();
      auto first = resultStack.top();
      resultStack.pop();
      resultStack.push(oper(first, second));
    }
  }
  return resultStack.top().getNum();
}
