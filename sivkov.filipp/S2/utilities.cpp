#include "utilities.hpp"
#include <string>

namespace sivkov
{
  bool isOeprator(std::string c)
  {
    return (c == "+" || c == "-" || c == "*" || c == "/" || c == "%");
  }

  int getPriority(std::string op)
  {
    if (op == "*" || op == "/" || op == "%")
    {
      return 2;
    }
    else if (op == "+" || op == "-")
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }
}
