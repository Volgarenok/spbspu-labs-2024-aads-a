#include "manageData.h"

namespace stepanov
{
  int manageExpression::checkOperatorsPriority(Token token) const
  {
    while (true)
    {
      switch (token.getOperator())
      {
        case '%' :
          return 1;
        case '/':
          return 1;
        case '*':
          return 1;
        case '+':
          return 2;
        case '-':
          return 2;
      }
      return 0;
    }
  }

}
