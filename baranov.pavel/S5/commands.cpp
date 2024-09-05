#include "commands.hpp"
#include <string>
#include "summator.hpp"

void baranov::ascending(std::ostream & out, const Tree< int, std::string > & tree)
{
  Summator sum;
  sum = tree.traverse_lnr(sum);
  int resultKey = sum.getResultKey();
  std::string resultValue = sum.getResultValue();
  out << resultKey << resultValue;
}

void baranov::descending(std::ostream & out, const Tree< int, std::string > & tree)
{
  Summator sum;
  sum = tree.traverse_rnl(sum);
  int resultKey = sum.getResultKey();
  std::string resultValue = sum.getResultValue();
  out << resultKey << resultValue;
}

void baranov::breadth(std::ostream & out, const Tree< int, std::string > & tree)
{
  Summator sum;
  sum = tree.traverse_breadth(sum);
  int resultKey = sum.getResultKey();
  std::string resultValue = sum.getResultValue();
  out << resultKey << resultValue;
}

