#ifndef SUMMATOR_HPP
#define SUMMATOR_HPP

#include <string>
#include <utility>

namespace baranov
{
  class Summator
  {
    public:
      Summator();
      void operator()(const std::pair< int, std::string > & data);
      int getResultKey() const;
      std::string getResultValue() const;
    private:
      int resultKey_;
      std::string resultValue_;
      int sign(int value);
      bool same_sign(int a, int b);
      int sum(int a, int b);
  };
}

#endif

