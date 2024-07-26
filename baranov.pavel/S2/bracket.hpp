#ifndef BRACKET_HPP
#define BRACKET_HPP

namespace baranov
{
  enum class BracketType
  {
    OPEN,
    CLOSE
  };

  class Bracket
  {
  public:
    Bracket() = default;
    explicit Bracket(char c);
    BracketType getType() const;
  private:
    BracketType type_;
  };
}

#endif

