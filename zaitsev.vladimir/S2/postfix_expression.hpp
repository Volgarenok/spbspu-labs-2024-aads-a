#ifndef POSTFIX_EXPRESSION_HPP
#define POSTFIX_EXPRESSION_HPP
#include <stdexcept>
#include <string>
#include "queue.hpp"
#include "stack.hpp"
#include "token.hpp"

namespace zaitsev
{
  class PostfixExpression
  {
  public:
    PostfixExpression() = default;
    PostfixExpression(const PostfixExpression& other) = default;
    PostfixExpression(PostfixExpression&& other) = default;
    PostfixExpression(const std::string& s):
      tokens_()
    {
      make_postfix(s);
    }
    PostfixExpression& operator=(const PostfixExpression& other) = default;
    PostfixExpression& operator=(PostfixExpression&& other) = default;
    void make_postfix(const std::string& s);
    long long calculate();
    bool empty() const
    {
      return tokens_.empty();
    }
  private:
    Queue< Token > tokens_;
    Queue< Token > split_on_tokens(const std::string& s);
    void add_non_value_token(Queue< Token >& tokens, char symbol);
  };
}
#endif
