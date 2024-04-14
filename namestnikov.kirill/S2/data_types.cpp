#include "data_types.hpp"
#include <stdexcept>

namestnikov::PartValue::PartValue():
  operand(0)
{}

namestnikov::PartValue::PartValue(long long number):
  operand(number)
{}

namestnikov::PartValue::PartValue(char symbol):
  operation(symbol)
{}

namestnikov::Key & namestnikov::Key::operator=(const Key & other)
{
  if (this != std::addressof(other))
  {
    type = other.type;
    value = other.value;
  }
  return *this;
}