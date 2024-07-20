#include "string_format.hpp"
#include <iostream>
#include <cctype>
#include "delimiter.hpp"

std::istream & erohin::operator>>(std::istream & input, StringFormat && dest)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  return std::getline(input >> SensetiveCaseDelimiter{ dest.wrapper }, dest.ref, dest.wrapper);
}

std::istream & erohin::operator>>(std::istream & input, WordInContextFormat && dest)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  std::string & str = dest.word;
  size_t wrap_size = dest.max_wrapper_size;
  input >> str;
  size_t index = 0;
  while (index < wrap_size && !str.empty() && !std::isalpha(str[0]))
  {
    str = str.substr(1);
    ++index;
  }
  if ((str.empty() || index != wrap_size) && !std::isalpha(str[0]))
  {
    input.setstate(std::ios::failbit);
    return input;
  }
  index = 0;
  while (index < wrap_size && !str.empty() && !std::isalpha(str[str.size() - 1]))
  {
    str = str.substr(0, str.size() - 1);
    ++index;
  }
  if ((str.empty() || index != wrap_size) && !std::isalpha(str[str.size() - 1]))
  {
    input.setstate(std::ios::failbit);
    return input;
  }
  for (size_t i = 0; i < str.size(); ++i)
  {
    str[i] = std::tolower(str[i]);
  }
  return input;
}
