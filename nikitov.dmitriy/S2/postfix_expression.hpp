#ifndef POSTFIX_EXPRESSION_HPP
#define POSTFIX_EXPRESSION_HPP

#include "queue.hpp"
#include "postfix_type.hpp"

namespace nikitov
{
  struct PostfixExpression
  {
  public:
    PostfixExpression operator+(long long value) const;
    PostfixExpression operator-(long long value) const;
    PostfixExpression operator/(long long value) const;
    PostfixExpression operator*(long long value) const;
    PostfixExpression operator%(long long value) const;

    void add(PostfixType& value);
    void add(PostfixType&& value);
    PostfixType remove();

    size_t size() const;
    bool empty() const;

    long long solve();

  private:
    Queue< PostfixType > data;
  };
}
#endif
