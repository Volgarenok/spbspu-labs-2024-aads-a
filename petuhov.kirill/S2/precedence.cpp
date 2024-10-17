#include "precedence.hpp"

int petuhov::precedence(char op) {
  if (op == '+' || op == '-') {
    return 1;
  }
  if (op == '*' || op == '/' || op == '%') {
    return 2;
  }
  if (op == '~') {
    return 3;
  }
  return 0;
}
