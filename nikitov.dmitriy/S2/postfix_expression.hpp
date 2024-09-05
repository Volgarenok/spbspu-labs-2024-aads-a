#ifndef POSTFIX_EXPRESSION_HPP
#define POSTFIX_EXPRESSION_HPP

#include <queue.hpp>
#include "postfix_type.hpp"

namespace nikitov
{
  struct PostfixExpression
  {
  public:
    PostfixExpression() = default;
    explicit PostfixExpression(const Queue< PostfixType >& postfixQueue);

    PostfixExpression operator+(long long value) const;
    PostfixExpression operator-(long long value) const;
    PostfixExpression operator/(long long value) const;
    PostfixExpression operator*(long long value) const;
    PostfixExpression operator%(long long value) const;

    PostfixExpression operator+(PostfixExpression value) const;
    PostfixExpression operator-(PostfixExpression value) const;
    PostfixExpression operator/(PostfixExpression value) const;
    PostfixExpression operator*(PostfixExpression value) const;
    PostfixExpression operator%(PostfixExpression value) const;

    long long solve();

  private:
    Queue< PostfixType > data_;
  };
}
#endif
