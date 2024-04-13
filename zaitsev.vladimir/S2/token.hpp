#ifndef TOKENS_HPP
#define TOKENS_HPP
#include <memory>
#include <iostream>
#include "operators.hpp"

namespace zaitsev
{
  enum struct token_type { undefined = -1, bracket = 0, binary_operator, value };
  enum struct bracket_type { empty = 0, round_open = 1, round_close = -1 };

  template< typename T >
  union TokenValue
  {
    bracket_type bracket_;
    BinaryOperator< T >* bin_operator_;
    T value_;
  };

  template< typename T >
  struct Token
  {
    token_type type_;
    TokenValue< T > token_;
    Token() = default;
    Token(const Token< T >& other):
      type_(other.type_)
    {
      token_ = copy_other_value(other);
    }
    Token(Token< T >&& other):
      type_(other.type_),
      token_(other.token_)
    {
      reset_other_value(std::move(other));
    }
    Token< T >& operator=(const Token< T >& other)
    {
      TokenValue< T > new_token= copy_other_value(other);
      if (type_ == token_type::binary_operator)
      {
        delete token_.bin_operator_;
      }
      type_ = other.type_;
      token_ = new_token;
      return *this;
    }
    Token< T >& operator=(Token< T >&& other)
    {
      type_ = other.type_;
      token_ = other.token_;
      reset_other_value(std::move(other));
    }
    ~Token()
    {
      if (type_ == token_type::binary_operator)
      {
        delete token_.bin_operator_;
      }
    }
    friend std::ostream& operator<<(std::ostream& output, const Token< T >& token)
    {
      switch (token.type_)
      {
      case zaitsev::token_type::undefined:
        output << "T";
        break;
      case zaitsev::token_type::bracket:
        switch (token.token_.bracket_)
        {
        case bracket_type::empty:
          output << "OO";
          break;
        case bracket_type::round_open:
          output << '(';
          break;
        case bracket_type::round_close:
          output << ')';
          break;
        }
        break;
      case zaitsev::token_type::binary_operator:
        if (!token.token_.bin_operator_)
        {
          output << "Op";
        }
        else
        {
          token.token_.bin_operator_->operator<<(output);
        }
        break;
      case zaitsev::token_type::value:
        output << token.token_.value_;
        break;
      }
      return output;
    }
  private:
    TokenValue< T > copy_other_value(const Token< T >& other)
    {
      TokenValue< T > return_value;
      switch (other.type_)
      {
      case token_type::bracket:
        return_value.bracket_ = other.token_.bracket_;
        break;
      case token_type::binary_operator:
        return_value.bin_operator_ = other.token_.bin_operator_->clone();
        break;
      case token_type::value:
        return_value.value_ = other.token_.value_;
        break;
      default:
        return_value.bracket_ = bracket_type::empty;
      }
      return return_value;
    }
    void reset_other_value(Token< T >&& other)
    {
      switch (other.type_)
      {
      case token_type::bracket:
        other.token_.bracket_ = bracket_type::empty;
        break;
      case token_type::binary_operator:
        other.token_.bin_operator_ = nullptr;
        break;
      case token_type::value:
        other.token_.value_ = 0;
      }
      other.type_ = token_type::undefined;
    }
  };
}
#endif
