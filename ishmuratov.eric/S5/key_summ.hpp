#ifndef KEY_SUMM_HPP
#define KEY_SUMM_HPP

#include <tuple>
#include <string>

namespace ishmuratov
{
  struct Key_summ
  {
    Key_summ();
    void operator()(const std::pair< const int, std::string > & key_value);
    int get_int() const;
    std::string get_str() const;
  private:
    int int_sum_;
    std::string str_sum_;
  };
}

#endif
