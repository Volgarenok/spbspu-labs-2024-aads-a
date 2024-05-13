#include "utilities.hpp"
#include <string>

namespace sivkov
{
  bool isOeprator(std::string& c)
  {
    return (c == "+" || c == "-" || c == "*" || c == "/" || c == "%");
  }

  bool compareOperators(std::string& first, std::string& second)
  {
    bool isFirst = (first == "*" || first == "/" || first == "%");
    bool isSecond = (second == "+" || second == "-");
    bool isClosedBracket = (first != "(");
    return isFirst && isSecond && isClosedBracket;
  }
}
