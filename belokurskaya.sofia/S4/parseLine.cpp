#include "parseLine.hpp"

void belokurskaya::parseLine(char* line, std::string& dict_name, Dictionary& dict)
{
  char* next_token = nullptr;
  char* token = splitString(line, " ", &next_token);
  if (token)
  {
    dict_name = token;
    while ((token = splitString(nullptr, " ", &next_token)))
    {
      int key = std::atoi(token);
      if ((token = splitString(nullptr, " ", &next_token)))
      {
        std::string value = token;
        dict.push(key, value);
      }
    }
  }
}

char* belokurskaya::splitString(char* str, const char* delimiters, char** context)
{
  if (str == NULL)
  {
    str = *context;
  }
  if (str == NULL || *str == '\0')
  {
    return NULL;
  }
  while (*str != '\0' && strchr(delimiters, *str) != NULL)
  {
    str++;
  }
  char* token = str;
  while (*str != '\0' && strchr(delimiters, *str) == NULL)
  {
    str++;
  }
  if (*str != '\0')
  {
    *str = '\0';
    str++;
  }
  *context = str;
  return token;
}
