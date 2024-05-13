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
    if (first == "+" || first == "-")
    {
      return true;
    }
    else
    {
      return second == "*" || second == "/" || second == "%";
    }
  }
}
