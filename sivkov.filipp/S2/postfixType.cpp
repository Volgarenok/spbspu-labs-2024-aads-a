#include "postfixType.hpp"

PostfixType::PostfixType():
  type(LL),
  longLongValue(0)
{}

PostfixType::PostfixType(char c):
  type(CHAR),
  charValue(c)
{}

PostfixType::PostfixType(long long i):
  type(LL),
  longLongValue(i)
{}

PostfixType::PostfixType(const PostfixType& other):
  type(other.type)
{
  if (type == CHAR)
  {
    charValue = other.charValue;
  }
  else
  {
    longLongValue = other.longLongValue;
  }
}

PostfixType::PostfixType(PostfixType&& other) noexcept:
  type(other.type)
{
  if (type == CHAR)
  {
    charValue = other.charValue;
  }
  else
  {
    longLongValue = other.longLongValue;
    other.type = LL;
    other.longLongValue = 0;
  }
}

PostfixType& PostfixType::operator=(const PostfixType& other)
{
  if (this != &other)
  {
    type = other.type;
    if (type == CHAR)
    {
      charValue = other.charValue;
    }
    else
    {
      longLongValue = other.longLongValue;
    }
  }
  return *this;
}

PostfixType& PostfixType::operator=(PostfixType&& other) noexcept
{
  if (this != &other)
  {
    type = other.type;
    if (type == CHAR)
    {
      charValue = other.charValue;
    }
    else
    {
      longLongValue = other.longLongValue;
      other.type = LL;
      other.longLongValue = 0;
    }
  }
  return *this;
}

bool PostfixType::operator==(const PostfixType& other) const
{
  if (type != other.type)
  {
    return false;
  }
  if (type == CHAR)
  {
    return charValue == other.charValue;
  }
  else
  {
    return longLongValue == other.longLongValue;
  }
}

bool PostfixType::isChar() const
{
  return type == CHAR;
}

bool PostfixType::isLL() const
{
  return type == LL;
}

char PostfixType::getChar() const
{
  if (isChar())
  {
    return charValue;
  }
  else
  {
    throw std::logic_error("Invalid type conversion: not a char");
  }
}

long long PostfixType::getLL() const
{
  if (isLL())
  {
    return longLongValue;
  }
  else
  {
    throw std::logic_error("Invalid type conversion: not a long long");
  }
}

