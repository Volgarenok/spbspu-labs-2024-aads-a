#ifndef INFIX_EXPRESSION_HPP
#define INFIX_EXPRESSION_HPP
#include <cstddef>
#include <string>
#include "token.hpp"
#include "operators.hpp"
#include "queue.hpp"

namespace zaitsev
{
  template< typename T >
  class InfixExpression
  {
  public:
    using iterator = typename Queue< Token< T > >::iterator;
    using const_iterator = typename Queue< Token< T > >::const_iterator;
  private:
    Queue< Token< T > > tokens_;
    void add_non_value_token(char symbol);
  public:
    InfixExpression() = default;
    InfixExpression(const std::string& s, T (*nums_converter)(const std::string&,size_t*,int));
    InfixExpression(const InfixExpression& other) = default;
    InfixExpression(InfixExpression&& other) = default;
    ~InfixExpression() = default;
    bool empty() const
    {
      return tokens_.empty();
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
  };

  template< typename T >
  InfixExpression< T >::InfixExpression(const std::string& s, T(*nums_converter)(const std::string&, size_t*, int)):
    tokens_()
  {
    size_t beg_pos = 0;
    size_t len = 0;
    for (size_t i = 0; i < s.size() + 1; ++i)
    {
      if ((i == s.size() || s[i] == ' ') && len > 0)
      {
        if (len == 1 && !std::isdigit(s[beg_pos]))
        {
          add_non_value_token(s[beg_pos]);
        }
        else
        {
          Token< T > t;
          t.type_ = token_type::value;
          t.token_.value_ = nums_converter(s.substr(beg_pos, len), nullptr, 10);
          tokens_.push(std::move(t));
        }
        len = 0;
      }
      else
      {
        if (len == 0)
        {
          beg_pos = i;
        }
        ++len;
      }
    }
  }


  template< typename T >
  void InfixExpression< T >::add_non_value_token(char symbol)
  {
    Token< T > t;
    switch (symbol)
    {
    case '(':
      t.type_ = token_type::bracket;
      t.token_.bracket_ = bracket_type::round_open;
      break;
    case ')':
      t.type_ = token_type::bracket;
      t.token_.bracket_ = bracket_type::round_close;
      break;
    case '+':
      t.type_ = token_type::binary_operator;
      t.token_.bin_operator_ = new SafePlus< T >{};
      break;
    case '-':
      t.type_ = token_type::binary_operator;
      t.token_.bin_operator_ = new SafeMinus< T >{};
      break;
    case '%':
      t.type_ = token_type::binary_operator;
      t.token_.bin_operator_ = new SafeMod< T >{};
      break;
    case '/':
      t.type_ = token_type::binary_operator;
      t.token_.bin_operator_ = new SafeDivision< T >{};
      break;
    case '*':
      t.type_ = token_type::binary_operator;
      t.token_.bin_operator_ = new SafeMultiplication< T >{};
      break;
    default:
      return;
    }
    tokens_.push(std::move(t));
  }
}
#endif
