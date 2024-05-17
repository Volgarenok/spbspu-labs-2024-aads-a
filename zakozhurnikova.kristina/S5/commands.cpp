#include "commands.hpp"
#include "getSum.hpp"

namespace zak = zakozhurnikova;

int zak::ascending(std::string& result, map& tree)
{
  KeySum amount;
  amount = tree.traverse_lnr(amount, result);
  int sum = amount.getResult();
  return sum;
}

int zak::descending(std::string& result, map& tree)
{
  KeySum amount;
  amount = tree.traverse_rnl(amount, result);
  int sum = amount.getResult();
  return sum;
}

int zak::breadth(std::string& result, map& tree)
{
  KeySum amount;
  amount = tree.traverse_breadth(amount, result);
  int sum = amount.getResult();
  return sum;
}
