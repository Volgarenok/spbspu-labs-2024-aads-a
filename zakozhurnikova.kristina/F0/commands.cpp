#include "commands.hpp"

void zakozhurnikova::print(const List< std::string >& args, std::string& result, const dict& dictionary)
{
  if (args.size() != 1)
  {
    throw std::invalid_argument("incorrect command source");
  }

  std::string mapName = args.back();
  if (!dictionary.at(mapName).empty())
  {
    result = mapName + ' ';
    for (auto it = dictionary[mapName].cbegin(); it != dictionary[mapName].cend(); ++it)
    {
      result += it->first + ' ';
      for (auto itList = (it->second).begin(); itList != (it->second).end(); ++itList)
      {
        result += *itList + ' ';
      }
    }
    result.pop_back();
  }
  else
  {
    result = "<EMPTY>";
  }
}
