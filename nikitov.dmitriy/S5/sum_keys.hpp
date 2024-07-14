#ifndef SUM_KEYS_HPP
#define SUM_KEYS_HPP

#include <string>

namespace nikitov
{
  class SumKeys
  {
  public:
    SumKeys();
    void operator()(const std::pair< int, std::string >& value);

    int getKey() const;
    std::string getLine() const;

  private:
    int key_;
    std::string line_;
  };
}
#endif
