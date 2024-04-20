#ifndef POSTFIXTYPE_HPP
#define POSTFIXTYPE_HPP
#include <exception>
#include <iostream>

class PostfixType
{
public:
  PostfixType();
  PostfixType(char c);
  PostfixType(long long i);
  PostfixType(const PostfixType& other);
  PostfixType(PostfixType&& other) noexcept;
  PostfixType& operator=(const PostfixType& other);
  PostfixType& operator=(PostfixType&& other) noexcept;
  bool operator==(const PostfixType& other) const;

  bool isChar() const;
  bool isLL() const;
  char getChar() const;
  long long getLL() const;

private:
  enum DataType { CHAR, LL };
  DataType type;
  union
  {
    char charValue;
    long long longLongValue;
  };
};

#endif
