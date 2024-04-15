#include <iostream>
#include <fstream>

#include "inputData.hpp"
#include "queue.hpp"
#include "stack.hpp"
#include "token.hpp"
#include <list/binList.hpp>

int main()
{
  using namespace arakelyan;
  Queue< ExpressionObj > tokenQ;

  Token newT;
  token_t typeT = token_t::smthk;

  long long num = 5;
  newT = Token(num);
  typeT = token_t::operand;

  ExpressionObj obj{newT, typeT};
  tokenQ.push(obj);
  std::cout << tokenQ.front().val_.operand_ << "\n";


  // if (argc == 1)
  // {
  //   std::ifstream input(argv[2]);
  //   readData(input, infixInputQ);
  // }
  // else
  // {
  //   readData(std::cin, infixInputQ);
  // }

  // std::cout << infixInputQ.front() << "\n";
  return 0;
}
