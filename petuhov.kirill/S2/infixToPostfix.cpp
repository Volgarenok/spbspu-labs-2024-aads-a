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
  bool expectUnary = true;

  for (size_t i = 0; i < expression.size(); ++i) {
    if (isspace(expression[i])) {
      continue;
    } else if (expression[i] == '(') {
      operators.push(expression[i]);
      expectUnary = true;
    } else if (expression[i] == ')') {
      while (!operators.empty() && operators.top() != '(') {
        output.push(std::string(1, operators.top()));
        operators.pop();
      }
      if (operators.empty() || operators.top() != '(') {
        throw std::invalid_argument("Mismatched parentheses");
      }
      operators.pop();
      expectUnary = false;
    } else if (strchr("+-*/%", expression[i])) {
      char op = expression[i];
      if (expectUnary && op == '-') {
        token = "-";
        ++i;
        while (i < expression.size() && isspace(expression[i])) ++i;
        if (i < expression.size() && isdigit(expression[i])) {
          while (i < expression.size() && isdigit(expression[i])) {
            token += expression[i++];
          }
          --i;
          output.push(token);
          expectUnary = false;
        } else if (i < expression.size() && expression[i] == '(') {
          operators.push('~');
          --i;
        } else {
          throw std::invalid_argument("Invalid unary minus usage");
        }
      } else {
        while (!operators.empty() && precedence(operators.top()) >= precedence(op)) {
          output.push(std::string(1, operators.top()));
          operators.pop();
        }
        operators.push(op);
        expectUnary = true;
      }
    } else if (isdigit(expression[i])) {
      token.clear();
      while (i < expression.size() && isdigit(expression[i])) {
        token += expression[i++];
      }
      --i;
      output.push(token);
      expectUnary = false;
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
