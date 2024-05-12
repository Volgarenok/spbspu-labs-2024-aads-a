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
    int getKey() const;
    std::string getVal() const;
  private:
    std::string str;
    int key;
  };
}
#endif
