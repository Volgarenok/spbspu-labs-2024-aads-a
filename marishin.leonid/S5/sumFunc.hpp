#ifndef SUMFUNC_HPP
#define SUMFUNC_HPP

#include <string>
#include <utility>
#include <stdexcept>
#include <limits>

namespace marishin
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
