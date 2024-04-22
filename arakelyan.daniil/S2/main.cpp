#include <iostream>
#include <fstream>

#include "queue.hpp"
#include "stack.hpp"
#include "token.hpp"
#include "inputData.hpp"
#include "calculateProc.hpp"
#include <list/binList.hpp>
#include <stdexcept>


std::ostream &printAllPostfixQs(std::ostream &out, arakelyan::Queue< arakelyan::Queue< arakelyan::ExpressionObj > > &qOfQs)
{
  while (!qOfQs.empty())
  {
    arakelyan::Queue< arakelyan::ExpressionObj > postfixQueue = transformInfixToPostfix(qOfQs.front());
    while (!postfixQueue.empty())
    {
      if (postfixQueue.front().type_ == arakelyan::token_t::operation)
      {
        out << postfixQueue.front().val_.oper_ << " ";
      }
      else if (postfixQueue.front().type_ == arakelyan::token_t::operand)
      {
        out << postfixQueue.front().val_.operand_ << " ";
      }
      else if (postfixQueue.front().type_ == arakelyan::token_t::bracket)
      {
        out << postfixQueue.front().val_.oper_ << " ";
      }
      postfixQueue.pop();
    }
    out << "\n";
    qOfQs.pop();
  }
  return out;
}

int main()
{
  using namespace arakelyan;
  Queue< Queue< ExpressionObj > > qOfQs;

  while (!std::cin.eof())
  {
    Queue< ExpressionObj > infixQueue = readDataInInfixForm(std::cin);
    qOfQs.push(infixQueue);
  }

  try
  {
    printAllPostfixQs(std::cout, qOfQs);
  }
  catch (const std::logic_error &e)
  {
    std::cout << "Error: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
