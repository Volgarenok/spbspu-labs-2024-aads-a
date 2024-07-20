#include "postfix_expression.hpp"

void zaitsev::PostfixExpression::make_postfix(const std::string& s)
{
  Queue< Token > raw_sequence = split_on_tokens(s);
  Stack< Token > internal_state;
  Queue< Token > new_tokens;
  while (!raw_sequence.empty())
  {
    switch (raw_sequence.front().type_)
    {
    case token_type::bracket:
    {
      switch (raw_sequence.front().value_.bracket_)
      {
      case bracket_type::round_open:
        internal_state.push(raw_sequence.front());
        break;

      case bracket_type::round_close:
        while (!internal_state.empty() && internal_state.top().type_ != token_type::bracket)
        {
          new_tokens.push(internal_state.top());
          internal_state.pop();
        }
        if (!areBraketsPaired(raw_sequence.front(), internal_state.top()))
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
    case token_type::bin_operator:
    {
      while (!internal_state.empty()
        && internal_state.top().type_ == token_type::bin_operator
        && !lessBinOperatorPriority(internal_state.top(), raw_sequence.front()))
      {
        new_tokens.push(internal_state.top());
        internal_state.pop();
      }
      internal_state.push(raw_sequence.front());
      break;
    }
    case token_type::numeric:
    {
      new_tokens.push(raw_sequence.front());
      break;
    }
    default:
      throw std::runtime_error("Unknown token");
    }
    raw_sequence.pop();
  }
  while (!internal_state.empty())
  {
    if (internal_state.top().type_ == token_type::bin_operator)
    {
      new_tokens.push(internal_state.top());
      internal_state.pop();
    }
    else
    {
      throw std::runtime_error("Incorrect expression");
    }
  }
  tokens_.clear();
  tokens_ = std::move(new_tokens);
}

long long zaitsev::PostfixExpression::calculate()
{
  Queue< Token > tokens = tokens_;
  Stack< long long > values;
  while (!tokens.empty())
  {
    long long a = 0;
    long long b = 0;
    switch (tokens.front().type_)
    {
    case token_type::numeric:
      values.push(tokens.front().value_.numeric_);
      break;
    case token_type::bin_operator:
      if (values.size() < 2)
      {
        throw std::runtime_error("Incorrect expression");
      }
      a = values.top();
      values.pop();
      b = values.top();
      values.pop();
      values.push(binOperatorResult(tokens.front(), b, a));
      break;
    default:
      throw std::runtime_error("Incorrect token");
    }
    tokens.pop();
  }
  if (values.size() != 1)
  {
    throw std::runtime_error("Incorrect expression");
  }
  return values.top();
}

zaitsev::Queue< zaitsev::Token > zaitsev::PostfixExpression::split_on_tokens(const std::string& s)
{
  Queue< Token > tokens;
  size_t beg_pos = 0;
  size_t len = 0;
  for (size_t i = 0; i < s.size() + 1; ++i)
  {
    if ((i == s.size() || s[i] == ' ') && len > 0)
    {
      if (len == 1 && !std::isdigit(s[beg_pos]))
      {
        add_non_value_token(tokens, s[beg_pos]);
      }
      else
      {
        TokenValue val;
        val.numeric_ = stoll(s.substr(beg_pos, len));
        tokens.push(Token(token_type::numeric, val));
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
  return tokens;
}

void zaitsev::PostfixExpression::add_non_value_token(Queue< Token >& tokens, char symbol)
{
  TokenValue new_token;
  switch (symbol)
  {
  case '(':
    new_token.bracket_ = bracket_type::round_open;
    tokens.push(Token(token_type::bracket, new_token));
    break;
  case ')':
    new_token.bracket_ = bracket_type::round_close;
    tokens.push(Token(token_type::bracket, new_token));
    break;
  case '+':
    new_token.bin_operator_ = bin_operator_type::plus;
    tokens.push(Token(token_type::bin_operator, new_token));
    break;
  case '-':
    new_token.bin_operator_ = bin_operator_type::minus;
    tokens.push(Token(token_type::bin_operator, new_token));
    break;
  case '%':
    new_token.bin_operator_ = bin_operator_type::mod;
    tokens.push(Token(token_type::bin_operator, new_token));
    break;
  case '/':
    new_token.bin_operator_ = bin_operator_type::div;
    tokens.push(Token(token_type::bin_operator, new_token));
    break;
  case '*':
    new_token.bin_operator_ = bin_operator_type::mult;
    tokens.push(Token(token_type::bin_operator, new_token));
    break;
  default:
    throw std::invalid_argument("Unknown token");
  }
  return;
}
