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
  Queue < Queue< ExpressionObj > > queueOfInfixQueues;

  while (!std::cin.eof())
  {
    Queue< ExpressionObj > infixQueue = readDataInfixForm(std::cin);
    queueOfInfixQueues.push(infixQueue);
    std::cout << "read one q\n";
  }

  std::cout << queueOfInfixQueues.size() << " - size of qOfQs\n";

  while (!queueOfInfixQueues.empty())
  {
    while (!queueOfInfixQueues.front().empty())
    {
      if (queueOfInfixQueues.front().front().type_ == token_t::operand)
      {
        std::cout << queueOfInfixQueues.front().front().val_.operand_ << " ";
      }
      else
      {
        std::cout << queueOfInfixQueues.front().front().val_.oper_ << " ";
      }
      queueOfInfixQueues.front().pop();
    }
    std::cout << "\n";

    queueOfInfixQueues.pop();
  }

  return 0;
}
