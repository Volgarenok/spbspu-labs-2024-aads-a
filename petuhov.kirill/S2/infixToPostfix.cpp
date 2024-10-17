#include "infixToPostfix.hpp"
#include "precedence.hpp"
#include "stack.hpp"
#include <string>
#include <cstring>
#include <cctype>
#include <stdexcept>

petuhov::Queue< std::string > petuhov::infixToPostfix(const std::string &expression) {
  petuhov::Stack< char > operators;
  petuhov::Queue< std::string > output;
  std::string token;

  for (size_t i = 0; i < expression.size(); ++i) {
    if (isspace(expression[i])) {
      continue;
    } else if (expression[i] == '(') {
      operators.push(expression[i]);
    } else if (expression[i] == ')') {
      while (!operators.empty() && operators.top() != '(') {
        output.push(std::string(1, operators.top()));
        operators.pop();
      }
      if (operators.empty() || operators.top() != '(') {
        throw std::invalid_argument("Mismatched parentheses");
      }
      operators.pop();
    } else if (strchr("+-*/%", expression[i])) {
      char op = expression[i];
      while (!operators.empty() && precedence(operators.top()) >= precedence(op) && operators.top() != '(') {
        output.push(std::string(1, operators.top()));
        operators.pop();
      }
      operators.push(op);
    } else if (isdigit(expression[i])) {
      token.clear();
      while (i < expression.size() && isdigit(expression[i])) {
        token += expression[i++];
      }
      --i;
      output.push(token);
    } else {
      throw std::invalid_argument("Invalid character in expression");
    }
  }

  while (!operators.empty()) {
    if (operators.top() == '(' || operators.top() == ')') {
      throw std::invalid_argument("Mismatched parentheses");
    }
    output.push(std::string(1, operators.top()));
    operators.pop();
  }

  return output;
}
