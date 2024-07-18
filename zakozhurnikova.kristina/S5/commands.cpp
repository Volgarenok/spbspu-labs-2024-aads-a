#include "commands.hpp"
#include "getSum.hpp"

namespace zak = zakozhurnikova;

int zak::ascending(std::string& result, map& tree)
{
  KeySum amount;
  amount = tree.traverse_lnr(amount);
  int sum = amount.getResult();
  result = amount.getLine();
  return sum;
}

int zak::descending(std::string& result, map& tree)
{
  KeySum amount;
  amount = tree.traverse_rnl(amount);
  int sum = amount.getResult();
  result = amount.getLine();
  return sum;
}

int zak::breadth(std::string& result, map& tree)
{
  KeySum amount;
  amount = tree.traverse_breadth(amount);
  int sum = amount.getResult();
  result = amount.getLine();
  return sum;
}
