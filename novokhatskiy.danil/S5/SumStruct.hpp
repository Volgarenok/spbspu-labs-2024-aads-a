#ifndef SUM_STRUCT
#define SUM_STRUCT
#include <string>
#include <utility>

namespace novokhatskiy
{
  struct KeySum
  {
  public:
    KeySum();
    void operator()(const std::pair< int, std::string >& value);
    int getKey() const;
    std::string getStr() const;
  private:
    int value_;
    std::string name_;
  };
}

#endif
