#ifndef POSTFIX_EXPRESSION_HPP
#define POSTFIX_EXPRESSION_HPP
#include <stdexcept>
#include "queue.hpp"
#include "stack.hpp"
#include "token.hpp"
#include "infix_expression.hpp"

namespace zaitsev
{
  template< typename T >
  class PostfixExpression
  {
  public:
    using iterator = typename Queue< Token< T > >::iterator;
    using const_iterator = typename Queue< Token< T > >::const_iterator;

    PostfixExpression() = default;
    PostfixExpression(const PostfixExpression& other) = default;
    PostfixExpression(PostfixExpression&& other) = default;
    PostfixExpression(const InfixExpression< T >& expression):
      tokens_()
    {
      convert_from_infix(expression);
    }
    void convert_from_infix(const InfixExpression< T >& expression)
    {
      Stack< Token< T > > internal_state;
      Queue< Token< T > > new_tokens;
      typename InfixExpression< T >::const_iterator expr_iterator = expression.cbegin();
      while (expr_iterator != expression.end())
      {
        switch ((*expr_iterator).type_)
        {
        case token_type::bracket:
        {
          switch ((*expr_iterator).token_.bracket_)
          {
          case bracket_type::round_open:
            internal_state.push(*expr_iterator);
            break;

          case bracket_type::round_close:
            while (!internal_state.empty() && internal_state.top().type_ != token_type::bracket)
            {
              new_tokens.push(internal_state.top());
              internal_state.pop();
            }
            if (internal_state.empty() ||
              static_cast<int>(internal_state.top().token_.bracket_)
              + static_cast<int>((*expr_iterator).token_.bracket_) != 0)
            {
              throw std::runtime_error("Incorrect expression");
            }
            else
            {
              internal_state.pop();
            }
            break;

          default:
            throw std::runtime_error("Unknown bracket");
          }
          break;
        }
        case token_type::binary_operator:
        {
          size_t top_token_priority = (*expr_iterator).token_.bin_operator_->priority();
          while (!internal_state.empty()
            && internal_state.top().type_ == token_type::binary_operator
            && internal_state.top().token_.bin_operator_->priority() >= top_token_priority)
          {
            new_tokens.push(internal_state.top());
            internal_state.pop();
          }
          internal_state.push(*expr_iterator);
          break;
        }
        case token_type::value:
        {
          new_tokens.push(*expr_iterator);
          break;
        }
        default:
          throw std::runtime_error("Unknown token");
        }
        ++expr_iterator;
      }
      while (!internal_state.empty())
      {
        if (internal_state.top().type_ == token_type::binary_operator)
        {
          new_tokens.push(internal_state.top());
          internal_state.pop();
        }
        else
        {
          throw std::runtime_error("Incorrect expression");
        }
      }
      tokens_ = std::move(new_tokens);
    }
    T calculate()
    {
      Stack< T > values;
      typename Queue< Token< T > >::const_iterator expr_iterator = tokens_.cbegin();
      while (expr_iterator != tokens_.cend())
      {
        T a, b;
        switch ((*expr_iterator).type_)
        {
        case token_type::value:
          values.push((*expr_iterator).token_.value_);
          break;
        case token_type::binary_operator:
          b = values.top();
          values.pop();
          a = values.top();
          values.pop();
          values.push((*((*expr_iterator).token_.bin_operator_))(a, b));
          break;
        default:
          throw std::logic_error("Incorrect token");
        }
        ++expr_iterator;
      }
      if (values.size() != 1)
      {
        throw std::runtime_error("Incorrect expression");
      }
      return values.top();
    }
    bool empty() const
    {
      return tokens_.empty();
    }
    Token< T >& get_token()
    {
      return tokens_.front();
    }
    void pop_token()
    {
      tokens_.pop();
    }
    iterator begin()
    {
      return tokens_.begin();
    }
    iterator end()
    {
      return tokens_.end();
    }
    const_iterator begin() const
    {
      return tokens_.cbegin();
    }
    const_iterator end() const
    {
      return tokens_.cend();
    }
    const_iterator cbegin() const
    {
      return tokens_.cbegin();
    }
    const_iterator cend() const
    {
      return tokens_.cend();
    }
  private:
    Queue< Token< T > > tokens_;
  };
}
#endif
