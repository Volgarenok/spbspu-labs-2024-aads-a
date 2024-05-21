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
    int get_int();
    std::string get_str();
  private:
    int int_sum_;
    std::string str_sum_;
  };
}

#endif
