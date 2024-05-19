#include <iostream>
#include <string>
#include "stack.hpp"
#include "queue.hpp"
#include "tokens.hpp"
#include "inputPostfix.hpp"
#include "calculatePostfix.hpp"

int main()
{
  using namespace baranov;
  Queue< Token > postfixExp;
  long long int result = 0;

  try
  {
    inputPostfix(std::cin, postfixExp);
    result = calculatePostfix(postfixExp);
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what();
    return 1;
  }

  std::cout << result << '\n';
}

