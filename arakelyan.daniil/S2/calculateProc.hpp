#ifndef CALCULATEPROC_HPP
#define CALCULATEPROC_HPP

#include "queue.hpp"
#include "stack.hpp"
#include "expressionObject.hpp"

namespace arakelyan
{
  void calculatePostfixQ(Queue< Queue< ExpressionObj > > &qOfPostfixQs, Stack< long long > &answerQ);
}
#endif
