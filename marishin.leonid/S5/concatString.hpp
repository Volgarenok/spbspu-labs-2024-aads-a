#ifndef CONCATSTRING_HPP
#define CONCATSTRING_HPP

#include <string>

namespace marishin
{
  class ConcatString
  {
  public:
    ConcatString();
    void operator()(const std::string & str);
    std::string getResult() const;
  private:
    std::string result_;
  };
}

#endif
