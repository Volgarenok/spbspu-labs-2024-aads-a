#include "funcObject.hpp"

skuratov::KeySumm::KeySumm():
  keyValue_(0),
  nameStr_()
{}

void skuratov::KeySumm::operator()(const std::pair< int, std::string >& keyValue)
{
  constexpr int max = std::numeric_limits< int >::max();
  constexpr int min = std::numeric_limits< int >::min();

  if ((keyValue_ > 0 && keyValue.first > max - keyValue_) || (keyValue_ < 0 && keyValue.first < min - keyValue_))
  {
    throw std::overflow_error("OVERFLOW");
  }
  if ((keyValue_ < 0 && keyValue.first < min - keyValue_) || (keyValue_ > 0 && keyValue.first < 0 && keyValue_ < min - keyValue.first))
  {
    throw std::underflow_error("UNDERFLOW");
  }

  keyValue_ += keyValue.first;
  nameStr_ += ' ' + keyValue.second;
}

int skuratov::KeySumm::getKeyValue() const
{
  return keyValue_;
}

std::string skuratov::KeySumm::getNameString() const
{
  return nameStr_;
}
