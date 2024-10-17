#include "applyOperation.hpp"
#include <stdexcept>

int petuhov::applyOperation(int a, int b, char op) {
  switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': 
      if (b == 0) throw std::invalid_argument("Division by zero");
      return a / b;
    default: throw std::invalid_argument("Invalid operator");
  }
}
