#include <iostream>
#include <fstream>
#include <vector>
#include "infixToPostfix.hpp"
#include "evaluatePostfix.hpp"

int main(int argc, char* argv[]) {
  std::vector<long long> results;
  std::string line;

  if (argc == 2) {
    std::ifstream infile(argv[1]);
    if (!infile.is_open()) {
      std::cerr << "Cannot open file: " << argv[1] << std::endl;
      return 1;
    }
    while (std::getline(infile, line)) {
      if (line.empty()) continue;
      try {
        auto postfix = petuhov::infixToPostfix(line);
        long long result = petuhov::evaluatePostfix(postfix);
        results.push_back(result);
      } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 2;
      }
    }
    infile.close();
  } else {
    while (std::getline(std::cin, line)) {
      if (line.empty()) {
        continue;
      }
      try {
        auto postfix = petuhov::infixToPostfix(line);
        long long result = petuhov::evaluatePostfix(postfix);
        results.push_back(result);
      } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 2;
      }
    }
  }

  for (auto it = results.rbegin(); it != results.rend(); ++it) {
    std::cout << *it;
    if (it + 1 != results.rend()) {
      std::cout << " ";
    }
  }
  std::cout << std::endl;

  return 0;
}
