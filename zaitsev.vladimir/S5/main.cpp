#include "map.hpp"
#include <operators.hpp>

struct summator
{
  void operator()(const std::pair< const int, std::string >& key_value) {
    result_ += key_value.first;
  }
  int result_ = 0;
};

int main(int argc, char** argv)
{

}
