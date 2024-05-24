#include "commands.hpp"
#include "sum_func.hpp"

void namestnikov::ascending(int & result, std::string & line, Tree< int, std::string > & map)
{
  SumFunc sumAmount;
  sumAmount = map.traverse_lnr(sumAmount);
  result = sumAmount.getResult();
  line = sumAmount.getLine();
}

void namestnikov::descending(int & result, std::string & line, Tree< int, std::string > & map)
{
  SumFunc sumAmount;
  sumAmount = map.traverse_rnl(sumAmount);
  result = sumAmount.getResult();
  line = sumAmount.getLine();
}

void namestnikov::breadth(int & result, std::string & line, Tree< int, std::string > & map)
{
  SumFunc sumAmount;
  sumAmount = map.traverse_breadth(sumAmount);
  result = sumAmount.getResult();
  line = sumAmount.getLine();
}
