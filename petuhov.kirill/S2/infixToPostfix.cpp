#include "infixToPostfix.hpp"
#include "precedence.hpp"
#include "stack.hpp"
#include <string>

petuhov::Queue< std::string > petuhov::infixToPostfix(const std::string &expression) {
  petuhov::Stack< char > operators;
  petuhov::Queue< std::string > output;
  std::string token;

  for (size_t i = 0; i < expression.size(); ++i) {
    if (isdigit(expression[i])) {
      token += expression[i];
      while (i + 1 < expression.size() && isdigit(expression[i + 1])) {
        token += expression[++i];
      }
      output.push(token);
      token.clear();
    } else if (expression[i] == '(') {
      operators.push(expression[i]);
    } else if (expression[i] == ')') {
      while (!operators.empty() && operators.top() != '(') {
        output.push(std::string(1, operators.top()));
        operators.pop();
      }
      operators.pop();
    } else if (strchr("+-*/", expression[i])) {
      while (!operators.empty() && precedence(operators.top()) >= precedence(expression[i])) {
        output.push(std::string(1, operators.top()));
        operators.pop();
      }
      operators.push(expression[i]);
    }
  }

  while (!operators.empty()) {
    output.push(std::string(1, operators.top()));
    operators.pop();
  }

  return output;
}
