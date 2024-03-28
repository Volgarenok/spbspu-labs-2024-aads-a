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
  private:
    Queue<Token<T>> tokens_;
  public:
    using iterator = typename Queue<Token<T>>::iterator;
    using const_iterator = typename Queue<Token<T>>::const_iterator;

    bool convert_from_infix(const InfixExpression< T >& expression);
    T calculate();
    bool empty() const;
    Token< T >& get_token();
    void pop_token();
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
  };

  template<typename T>
  bool PostfixExpression< T >::convert_from_infix(const InfixExpression<T>& expression)
  {
    Stack<Token<T>> internal_state;
    InfixExpression<T>::template const_iterator expr_iterator = expression.cbegin();
    try
    {
      while (expr_iterator!=expression.end())
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
              tokens_.push(internal_state.top());
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
            tokens_.push(internal_state.top());
            internal_state.pop();
          }
          internal_state.push(*expr_iterator);
          break;
        }
        case token_type::value:
        {
          tokens_.push(*expr_iterator);
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
          tokens_.push(internal_state.top());
          internal_state.pop();
        }
        else
        {
          throw std::runtime_error("Incorrect expression");
        }
      }
    }
    catch (const std::exception&)
    {
      tokens_.clear();
      throw;
    }
    return true;
  }

  template<typename T>
  T PostfixExpression<T>::calculate()
  {
    Stack<T> values;
    Queue<Token<T>>::template const_iterator expr_iterator = tokens_.cbegin();
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
        values.push((* ((*expr_iterator).token_.bin_operator_))(a, b));
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
  template<typename T>

  bool PostfixExpression<T>::empty() const
  {
    return tokens_.empty();
  }
  template<typename T>
  Token<T>& PostfixExpression<T>::get_token()
  {
    return tokens_.front();
  }
  template<typename T>
  void PostfixExpression<T>::pop_token()
  {
    tokens_.pop();
  }
}
#endif
