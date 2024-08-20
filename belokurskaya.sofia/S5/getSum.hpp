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
      std::pair< long long int, std::string > getResult() const;

    private:
      long long int resultKey_;
      std::string resultValue_;
      bool sameSign(long long int a, long long int b);
      long long int sum(long long int a, long long int b);
  };
}

#endif
