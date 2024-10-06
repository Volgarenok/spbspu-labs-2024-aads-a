#include "parseLine.hpp"

void belokurskaya::parseLine(char* line, std::string& dict_name, Dictionary& dict)
{
  char* p = line;
  while (*p == ' ')
  {
    p++;
  }

  char* q = p;
  while (*q != ' ' && *q != '\0')
  {
    q++;
  }
  dict_name.assign(p, q - p);

  while (*q == ' ')
  {
    q++;
  }
  while (*q != '\0')
  {
    p = q;
    while (*p != ' ' && *p != '\0')
    {
      p++;
    }
    int key = std::atoi(q);
    q = p;
    while (*q == ' ')
    {
      q++;
    }
    p = q;
    while (*p != ' ' && *p != '\0')
    {
      p++;
    }
    std::string value(q, p - q);
    dict.push(key, value);
    q = p;
  }
}
