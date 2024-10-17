#include "evaluatePostfix.hpp"
#include "applyOperation.hpp"
#include "stack.hpp"
#include <string>
#include <stdexcept>

int petuhov::evaluatePostfix(petuhov::Queue< std::string > &postfix) {
  petuhov::Stack< int > values;
  
  while (!postfix.empty()) {
    std::string token = postfix.front();
    postfix.pop();

    if (isdigit(token[0])) {
      values.push(std::stoi(token));
    } else if (strchr("+-*/", token[0])) {
      int b = values.top(); values.pop();
      int a = values.top(); values.pop();
      values.push(petuhov::applyOperation(a, b, token[0]));
    }
  }

  if (values.size() != 1) {
    throw std::invalid_argument("Invalid expression");
  }

  return values.top();
}
