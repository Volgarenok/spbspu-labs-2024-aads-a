#include "evaluatePostfix.hpp"
#include "applyOperation.hpp"
#include "stack.hpp"
#include <string>
#include <stdexcept>
#include <cstring>

long long petuhov::evaluatePostfix(petuhov::Queue< std::string > &postfix) {
  petuhov::Stack< long long > values;

  while (!postfix.empty()) {
    std::string token = postfix.front();
    postfix.pop();

    if (isdigit(token[0]) || (token.size() > 1 && (token[0] == '-' || token[0] == '+'))) {
      values.push(std::stoll(token));
    } else if (strchr("+-*/%", token[0])) {
      if (values.size() < 2) {
        throw std::invalid_argument("Invalid expression: not enough values");
      }
      long long b = values.top();
      values.pop();
      long long a = values.top();
      values.pop();
      values.push(petuhov::applyOperation(a, b, token[0]));
    } else {
      throw std::invalid_argument("Invalid token in expression");
    }
  }

  if (values.size() != 1) {
    throw std::invalid_argument("Invalid expression");
  }

  return values.top();
}
