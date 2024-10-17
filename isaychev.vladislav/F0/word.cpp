#include "word.hpp"
#include <iostream>
#include <cctype>

bool is_letter(char c)
{
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool has_no_letters(const std::string & str)
{
  for (auto i = str.begin(); i != str.end(); ++i)
  {
    if (is_letter(*i))
    {
      return false;
    }
  }
  return true;
}

std::istream & isaychev::operator>>(std::istream & in, Word & w)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  std::string temp;
  in >> temp;
  if (has_no_letters(temp))
  {
    in.setstate(std::ios::failbit);
  }
  else
  {
    const char * bracs_and_quotes = "'\"()";
    if (temp.find_first_of(bracs_and_quotes) != std::string::npos)
    {
      temp = std::move(temp.substr(temp.find_first_not_of(bracs_and_quotes)));
      temp = std::move(temp.substr(0, temp.find_first_of(bracs_and_quotes)));
    }
    if (std::ispunct(temp.back()))
    {
      temp.pop_back();
    }
    w.content = std::move(temp);
  }
  return in;
}

std::ostream & isaychev::operator<<(std::ostream & out, const Word & w)
{
  return out << w.content;
}

bool isaychev::operator<(const Word & lhs, const Word & rhs)
{
  return lhs.content < rhs.content;
}

bool isaychev::operator==(const Word & lhs, const Word & rhs)
{
  return lhs.content == rhs.content;
}
