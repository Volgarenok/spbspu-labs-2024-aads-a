#include <iostream>
#include <fstream>

#include "queue.hpp"
#include "stack.hpp"
#include "token.hpp"
#include "inputData.hpp"
#include "calculateProc.hpp"
#include <list/binList.hpp>

int main()
{
  using namespace arakelyan;
  // Queue < Queue< ExpressionObj > > queueOfInfixQueues;

  // while (!std::cin.eof())
  // {
  //   Queue< ExpressionObj > infixQueue = readDataInInfixForm(std::cin);
  //   // queueOfInfixQueues.push(infixQueue);
  //   std::cout << "read one q\n";
  // }

  Queue< ExpressionObj > infixQueue = readDataInInfixForm(std::cin);
  Queue< ExpressionObj > postfixQueue = transformInfixToPostfix(infixQueue);

  while (!postfixQueue.empty())
  {
    if (postfixQueue.front().type_ == token_t::operation)
    {
      std::cout << postfixQueue.front().val_.oper_ << " ";
    }
    else if (postfixQueue.front().type_ == token_t::operand)
    {
      std::cout << postfixQueue.front().val_.operand_ << " ";
    }
    else if (postfixQueue.front().type_ == token_t::bracket)
    {
      std::cout << postfixQueue.front().val_.oper_ << " ";
    }
    postfixQueue.pop();
  }

  // std::cout << queueOfInfixQueues.size() << " - size of qOfQs\n";

  // //out current qs
  // while (!queueOfInfixQueues.empty())
  // {
  //   while (!queueOfInfixQueues.front().empty())
  //   {
  //     if (queueOfInfixQueues.front().front().type_ == token_t::operand)
  //     {
  //       std::cout << queueOfInfixQueues.front().front().val_.operand_ << " ";
  //     }
  //     else
  //     {
  //       std::cout << queueOfInfixQueues.front().front().val_.oper_ << " ";
  //     }
  //     queueOfInfixQueues.front().pop();
  //   }
  //   std::cout << "\n";
  //
  //   queueOfInfixQueues.pop();
  // }

  return 0;
}
