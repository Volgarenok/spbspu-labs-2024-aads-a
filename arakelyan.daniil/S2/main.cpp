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
  Queue< ExpressionObj > infixQ;

  // Token newT;
  // token_t typeT = token_t::smthk;

  // long long num = 5;
  // char num = '+';
  // newT = Token(num);
  // typeT = token_t::operation;
  //
  // ExpressionObj obj{newT, typeT};
  // tokenQ.push(obj);
  // std::cout << tokenQ.front().val_.oper_ << "\n";


  // if (argc == 1)
  // {
  //   std::ifstream input(argv[2]);
  //   readData(input, infixInputQ);
  // }
  // else
  // {
  //   readData(std::cin, infixInputQ);
  // }
  readDataInfixForm(std::cin, infixQ);
  std::cout << "\n";
  while (!infixQ.empty())
  {
    if (infixQ.front().type_ == token_t::operand)
    {
      std::cout << infixQ.front().val_.operand_ << " ";
    }
    else
    {
      std::cout << infixQ.front().val_.oper_ << " ";
    }
    infixQ.pop();
  }
  std::cout << "\n";

  // std::cout << infixInputQ.front() << "\n";
  return 0;
}
