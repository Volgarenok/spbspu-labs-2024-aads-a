#include "input.hpp"

namespace sakovskaia
{
  Tree< std::string, Tree< size_t, std::string > > input(std::istream & input)
  {
    Tree< std::string, Tree< size_t, std::string > > dictionaries;
    std::string name;
    while (input >> name)
    {
      Tree< size_t, std::string > dictionary;
      size_t key = 0;
      while (input >> key)
      {
        std::string word;
        if (!(input >> word))
        {
          input.clear();
          break;
        }
        dictionary.push(key, word);
      }
      input.clear();
      dictionaries.push(name, dictionary);
    }
    return dictionaries;
  }
}

