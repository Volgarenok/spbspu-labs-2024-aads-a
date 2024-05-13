#include "utilities.hpp"
#include <string>

namespace sivkov
{
  bool isOeprator(std::string c)
  {
    return (c == "+" || c == "-" || c == "*" || c == "/" || c == "%");
  }
}
