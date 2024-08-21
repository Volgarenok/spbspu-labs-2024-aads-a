#include "parseLine.hpp"

void belokurskaya::parseLine(char* line, std::string& dict_name, Dictionary& dict)
{
  char* next_token = nullptr;
  char* token = strtok_s(line, " ", &next_token);
  if (token)
  {
    dict_name = token;
    while ((token = strtok_s(nullptr, " ", &next_token)))
    {
      int key = std::atoi(token);
      if ((token = strtok_s(nullptr, " ", &next_token)))
      {
        std::string value = token;
        dict.push(key, value);
      }
    }
  }
}
