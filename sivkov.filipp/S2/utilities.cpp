#include "utilities.hpp"
#include <string>

namespace sivkov
{
  bool isOeprator(const std::string& c)
  {
    return (c == "+" || c == "-" || c == "*" || c == "/" || c == "%");
  }

  bool compareOperators(const std::string& first, const std::string& second)
  {
    return (first == "*" || first == "/" || first == "%") || ((second == "+" || second == "-") && first != "(");
  }

}
