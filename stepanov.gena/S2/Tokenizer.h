#ifndef TOKENIZER_H
#define TOKENIZER_H

namespace stepanov
{
  enum TokenType
  {
    PLUS,
    MINUS,
    MULTIPLICATION,
    MOD,
    DIV,
    LEFT_PAREN,
    RIGHT_PAREN,
    OPERAND,
    NONE
  };
  struct Token
  {
    public:
      Token(char* token);
      ~Token() = default;

      bool isOperand() const noexcept;
      bool isOperator() noexcept;
      bool isParenthesis() const noexcept;
      TokenType getTokenType() const noexcept;
      char getParenthesis() const noexcept;
      char getOperator() noexcept;
      long long getOperand() const noexcept;


    private:
      char* token_;
      TokenType type_;
      long long numData_;
      char charData_;
      TokenType getOperatorType() noexcept;
  }
}

#endif
