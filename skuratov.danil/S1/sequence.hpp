#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <string>
#include <vector>

namespace skuratov
{
  class Sequence
  {
  public:
    Sequence(const std::string& name):
      name_(name)
    {}
    const std::string& name() const { return name_; }
    std::vector< size_t >& numbers() { return numbers_; }
    const std::vector< size_t >& numbers() const { return numbers_; }

  private:
    std::string name_;
    std::vector< size_t > numbers_;
  };
}

#endif
