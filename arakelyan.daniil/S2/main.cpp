#include <iostream>
#include <stdexcept>

#include "queue.hpp"
#include "stack.hpp"
#include "expressionObject.hpp"
#include "inputData.hpp"
#include "transformToPostfix.hpp"
#include "calculateProc.hpp"
#include <list/binList.hpp>

std::ostream &printAllPostfixQs(std::ostream &out, arakelyan::Queue< arakelyan::Queue< arakelyan::detail::ExpressionObj > > &qOfQs)
{
  using namespace arakelyan::detail;
  while (!qOfQs.empty())
  {
    arakelyan::Queue< ExpressionObj > postfixQueue = transformInfixToPostfix(qOfQs.front());
    while (!postfixQueue.empty())
    {
      if (postfixQueue.front().type_ == token_t::operation)
      {
        out << postfixQueue.front().val_.oper_ << " ";
      }
      else if (postfixQueue.front().type_ == token_t::operand)
      {
        out << postfixQueue.front().val_.operand_ << " ";
      }
      else if (postfixQueue.front().type_ == token_t::bracket)
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
  using namespace detail;
  Queue< Queue< ExpressionObj > > qOfInfQs;

  while (!std::cin.eof())
  {
    Queue< ExpressionObj > infixQueue = readDataInInfixForm(std::cin);
    qOfInfQs.push(infixQueue);
  }

  Queue< Queue< ExpressionObj > > qOfPostQs;
  try
  {
    while (!qOfInfQs.empty())
    {
      Queue< ExpressionObj > postQ = transformInfixToPostfix(qOfInfQs.front());
      qOfInfQs.pop();
      qOfPostQs.push(postQ);
    }
  }
  catch (const std::logic_error &e)
  {
    std::cout << "Error: " << e.what() << "\n";
    return 1;
  }

  Queue< long long > answQ;

  try
  {
    while (!qOfPostQs.empty())
    {
      calculatePostfixQ(qOfPostQs, answQ);
    }
  }
  catch (const std::exception &e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }

  while (!answQ.empty())
  {
    std::cout << answQ.front() << " -> ";
    answQ.pop();
  }

  return 0;
}
