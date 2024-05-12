#ifndef KEYSUM_HPP
#define KEYSUM_HPP
#include <utility>
#include <string>

namespace piyavkin
{
  struct KeySum
  {
  public:
    void operator()(const std::pair< int, std::string >& val);
  private:
    std::string str;
    int key;
  };
}
#endif