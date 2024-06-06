#include "command.hpp"
#include "sumFunc.hpp"

void marishin::ascending(int & result, std::string & line, Tree< int, std::string > & map)
{
  SumFunc amount;
  amount = map.traverse_lnr(amount);
  result = amount.getResult();
  line = amount.getLine();
}

void marishin::descending(int & result, std::string & line, Tree< int, std::string > & map)
{
  SumFunc amount;
  amount = map.traverse_rnl(amount);
  result = amount.getResult();
  line = amount.getLine();
}

void marishin::breadth(int & result, std::string & line, Tree< int, std::string > & map)
{
  SumFunc amount;
  amount = map.traverse_breadth(amount);
  result = amount.getResult();
  line = amount.getLine();
}
