#ifndef GETSUM_HPP
#define GETSUM_HPP
#include <limits>
#include <stdexcept>
#include <string>
#include <utility>

namespace zakozhurnikova
{
  struct KeySum
  {
    KeySum();
    void operator()(std::pair< int, std::string > data);
    int getResult() const;
    std::string getLine() const;

  private:
    int result_;
    std::string line_;
  };
}

#endif
