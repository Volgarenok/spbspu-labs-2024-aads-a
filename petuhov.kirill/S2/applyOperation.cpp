#include "applyOperation.hpp"
#include <stdexcept>
#include <limits>

int petuhov::applyOperation(long long a, long long b, char op) {
  switch (op) {
    case '+': 
      if (a > 0 && b > 0 && a > std::numeric_limits<long long>::max() - b) 
        throw std::overflow_error("Overflow in addition");
      return a + b;
    case '-':
      if (a < 0 && b > 0 && a < std::numeric_limits<long long>::min() + b)
        throw std::underflow_error("Underflow in subtraction");
      return a - b;
    case '*': return a * b;
    case '/':
      if (b == 0) throw std::invalid_argument("Division by zero");
      return a / b;
    case '%':
      if (b == 0) throw std::invalid_argument("Modulo by zero");
      return a % b;
    default: throw std::invalid_argument("Invalid operator");
  }
}
