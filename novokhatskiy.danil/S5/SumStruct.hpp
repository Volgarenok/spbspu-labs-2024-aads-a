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
  private:
    int value_;
  };

  struct StrSum
  {
    StrSum();
    void operator()(const std::pair< int, std::string >& val);
    std::string getStr() const;
  private:
    std::string name_;
  };
}

#endif
