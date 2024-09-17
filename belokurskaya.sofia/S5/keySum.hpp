#ifndef GET_SUM_HPP
#define GET_SUM_HPP

#include <string>
#include <utility>

namespace belokurskaya
{
  class KeySum
  {
    public:
      KeySum();
      void operator()(const std::pair< const int, std::string >& data);
      std::pair< int, std::string > getResult() const;
      int getResultKey() const;
      std::string getResultValue() const;

    private:
      int resultKey_;
      std::string resultValue_;
      bool sameSign(int a, int b);
      int sum(int a, int b);
  };
}

#endif
