#ifndef BRACKET_HPP
#define BRACKET_HPP

namespace erohin
{
  enum bracket_t
  {
    OPEN_BRACKET,
    CLOSE_BRACKET
  };

  struct Bracket
  {
    bracket_t bracket_type;
  };
}

#endif
