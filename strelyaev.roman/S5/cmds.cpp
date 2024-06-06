#include "cmds.hpp"
#include <limits>

struct Summator
{
  public:
    Summator();
    void operator()(const std::pair< int, std::string >& data);
    int getResult() const;
    std::string getLine() const;

  private:
    int result_;
    std::string line_;
};

Summator::Summator():
  result_(0),
  line_("")
{}

void Summator::operator()(const std::pair< int, std::string >& data)
{
  int max_num = std::numeric_limits< int >::max();
  int min_num = std::numeric_limits< int >::min();
  if ((result_ > 0 && max_num - result_ < data.first) || (result_ < 0 && data.first < 0 && min_num - result_ > data.first))
  {
    throw std::overflow_error("over-/underflow");
  }
  result_ += data.first;
  line_ += data.second + " ";
}

std::string Summator::getLine() const
{
  return line_;
}

int Summator::getResult() const
{
  return result_;
}

int strelyaev::traverseAscending(std::string& result, Tree< int, std::string >& tree)
{
  Summator amount;
  amount = tree.traverse_lnr(amount);
  int sum = amount.getResult();
  result = amount.getLine();
  return sum;
}

int strelyaev::traverseDescending(std::string& result, Tree< int, std::string >& tree)
{
  Summator amount;
  amount = tree.traverse_rnl(amount);
  int sum = amount.getResult();
  result = amount.getLine();
  return sum;
}

int strelyaev::TraverseBreadth(std::string& result, Tree< int, std::string >& tree)
{
  Summator amount;
  amount = tree.traverse_breadth(amount);
  int sum = amount.getResult();
  result = amount.getLine();
  return sum;
}
