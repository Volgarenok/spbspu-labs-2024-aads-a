#ifndef CALCULATEPROC_HPP
#define CALCULATEPROC_HPP

#include "queue.hpp"
#include "expressionObject.hpp"

namespace arakelyan
{
  void calculatePostfixQ(Queue< Queue< ExpressionObj > > &qOfPostfixQs, Queue< long long > &answerQ);
}
#endif
