#ifndef SUMFUNC_HPP
#define SUMFUNC_HPP

#include "sumNum.hpp"
#include "concatString.hpp"

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
    SumNum sumNum_;
    ConcatString concatString_;
  };
}

#endif
