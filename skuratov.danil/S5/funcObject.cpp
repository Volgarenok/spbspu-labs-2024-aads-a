#include "funcObject.hpp"
#include <limits>
#include <stdexcept>

skuratov::KeySumm::KeySumm():
	keyValue_(0),
	nameStr_()
{}

void skuratov::KeySumm::operator()(const std::pair< const int, std::string >& keyValue)
{
	constexpr int max = std::numeric_limits< int >::max();
	constexpr int min = std::numeric_limits< int >::min();

	if ((keyValue_ > 0 && max - keyValue_ < keyValue.first) || (keyValue_ < 0 && keyValue.first < 0 && min - keyValue_ > keyValue.first))
	{
		throw std::overflow_error("Overflow");
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
