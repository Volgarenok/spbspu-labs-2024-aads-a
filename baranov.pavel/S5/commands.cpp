#include "commands.hpp"
#include <string>
#include "summator.hpp"

void baranov::ascending(std::ostream & out, const Tree< int, std::string > & tree)
{
  Summator sum;
  sum = tree.traverse_lnr(sum);
  int resultKey = sum.getResultKey();
  std::string resultValue = sum.getResultValue();
  if (resultValue.empty())
  {
    out << "<EMPTY>";
    return;
  }
  out << resultKey << ' ' << resultValue;
}

