#include <iostream>
#include <string>
#include <functional>
#include <utility>
#include <map>

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

int main()
{
  std::map< int, std::string > myMap;
  while (!std::cin.eof())
  {
    std::cin.clear();
    int keyNumber = 0;
    std::string value = "";
    while (std::cin >> keyNumber >> value)
    {
      myMap.insert(std::make_pair(keyNumber, value));
    }
  }
  std::cout << "|||" << myMap[10];
}
