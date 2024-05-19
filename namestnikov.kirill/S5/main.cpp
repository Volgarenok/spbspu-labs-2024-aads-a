#include <iostream>
#include <string>
#include <functional>
#include <utility>
#include <map>
#include "tree.hpp"

namespace namestnikov
{
  class SumFunc
  {
  public:
    SumFunc();
    void operator()(const std::pair< const int, std::string > & data);
    int getResult() const;
    std::string getLine() const;
  private:
    int result_;
    std::string line_;
  };
}

namestnikov::SumFunc::SumFunc():
  result_(0),
  line_("")
{}

int namestnikov::SumFunc::getResult() const
{
  return result_;
}

std::string namestnikov::SumFunc::getLine() const
{
  return line_;
}

void namestnikov::SumFunc::operator()(const std::pair< const int, std::string > & data)
{
  result_ += data.first;
  line_ = line_ + data.second + " ";
}

void ascending(int & result, std::string & line, namestnikov::Tree< int, std::string > & map)
{
  namestnikov::SumFunc sumAmount;
  sumAmount = map.traverse_lnr(sumAmount);
  result = sumAmount.getResult();
  line = sumAmount.getLine();
}

void descending(int & result, std::string & line, namestnikov::Tree< int, std::string > & map)
{
  namestnikov::SumFunc sumAmount;
  sumAmount = map.traverse_rnl(sumAmount);
  result = sumAmount.getResult();
  line = sumAmount.getLine();
}

void breadth(int & result, std::string & line, namestnikov::Tree< int, std::string > & map)
{
  namestnikov::SumFunc sumAmount;
  sumAmount = map.traverse_breadth(sumAmount);
  result = sumAmount.getResult();
  line = sumAmount.getLine();
}

int main()
{
  using namespace namestnikov;
  Tree< int, std::string > myMap;
  while (!std::cin.eof())
  {
    std::cin.clear();
    int keyNumber = 0;
    std::string value = "";
    while (std::cin >> keyNumber >> value)
    {
      myMap.insert(keyNumber, value);
    }
  }
  std::string output = "";
  int result = 0;
  descending(result, output, myMap);
  std::cout << result;
  std::cout << output << "\n";
}
