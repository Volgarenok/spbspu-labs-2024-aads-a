#include "commands.hpp"
#include <string>
#include "calcSum.hpp"

void baranov::ascending(std::ostream & out, std::map< int, std::string > & tree)
{
  KeySum amount;
  auto end = tree.cend();
  for (auto i = tree.cbegin(); i != end; ++i)
  {
    amount(*i);
  }
  int sum = amount.getResultKey();
  std::string str = amount.getResultValue();
  if (!str.empty())
  {
    out << sum << ' ' << str;
  }
}

