#include <iostream>
#include "infixToPostfix.hpp"
#include "evaluatePostfix.hpp"

int main(int argc, char* argv[]) {
  std::string expression;

  if (argc == 2) {
    expression = argv[1];
  } else {
    std::getline(std::cin, expression);
  }

  try {
    auto postfix = petuhov::infixToPostfix(expression);
    int result = petuhov::evaluatePostfix(postfix);
    std::cout << result << std::endl;
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  return 0;
}
