#ifndef SUMNUM_HPP
#define SUMNUM_HPP

#include <limits>
#include <stdexcept>

namespace marishin
{
  class SumNum
  {
  public:
    SumNum();
    void operator()(int num);
    int getResult() const;
  private:
    int result_;
  };
}

#endif
