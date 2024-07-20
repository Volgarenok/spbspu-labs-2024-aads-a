#ifndef SUM_FUNC_HPP
#define SUM_FUNC_HPP

#include <string>
#include <utility>

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

#endif
