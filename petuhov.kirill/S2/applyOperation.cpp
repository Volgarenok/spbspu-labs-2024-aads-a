#include "applyOperation.hpp"
#include <stdexcept>
#include <limits>
#include <cmath>

long long petuhov::applyOperation(long long a, long long b, char op) {
  if (op == '+') {
    if ((b > 0 && a > std::numeric_limits< long long >::max() - b) ||
        (b < 0 && a < std::numeric_limits< long long >::min() - b)) {
      throw std::overflow_error("Overflow in addition");
    }
    return a + b;
  }

  if (op == '-') {
    if ((b > 0 && a < std::numeric_limits< long long >::min() + b) ||
        (b < 0 && a > std::numeric_limits< long long >::max() + b)) {
      throw std::underflow_error("Underflow in subtraction");
    }
    return a - b;
  }

  if (op == '*') {
    if (a > 0 && b > 0 && a > std::numeric_limits< long long >::max() / b) {
      throw std::overflow_error("Overflow in multiplication");
    }
    if (a > 0 && b < 0 && b < std::numeric_limits< long long >::min() / a) {
      throw std::underflow_error("Underflow in multiplication");
    }
    if (a < 0 && b > 0 && a < std::numeric_limits< long long >::min() / b) {
      throw std::underflow_error("Underflow in multiplication");
    }
    if (a < 0 && b < 0 && a < std::numeric_limits< long long >::max() / b) {
      throw std::overflow_error("Overflow in multiplication");
    }
    return a * b;
  }

  if (op == '/') {
    if (b == 0) {
      throw std::invalid_argument("Division by zero");
    }
    if (a == std::numeric_limits< long long >::min() && b == -1) {
      throw std::overflow_error("Overflow in division");
    }
    return a / b;
  }

  if (op == '%') {
    if (b == 0) {
      throw std::invalid_argument("Modulo by zero");
    }
    long long mod_result = a % b;
    if (mod_result < 0) {
      mod_result += std::abs(b);
    }
    return mod_result;
  }

  throw std::invalid_argument("Invalid operator");
}
