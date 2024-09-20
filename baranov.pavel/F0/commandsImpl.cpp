#include "commandsImpl.hpp"

void baranov::extendDict(dict_t & dict, std::istream & in)
{
  std::string word;
  while (in >> word)
  {
    std::string cleanWord;
    for (size_t i = 0; i < word.length(); ++i)
    {
      char c = word[i];
      if (std::isalpha(c))
      {
        cleanWord += std::tolower(c);
      }
    }
    if (!cleanWord.empty())
    {
      dict[cleanWord]++;
    }
  }
}

void baranov::printElement(const pair_t & item, std::ostream & out)
{
  out << item.first << ' ' << item.second << '\n';
}

size_t baranov::getWordCount(const dict_t & dict, const std::string & word)
{
  try
  {
    return dict.at(word);
  }
  catch (const std::out_of_range &)
  {
    return 0;
  }
}

bool baranov::countComparator(const pair_t & lhs, const pair_t & rhs)
{
  return lhs.second < rhs.second;
}

