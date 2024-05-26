#include "input.hpp"
#include <string>

namespace sivkov
{
  AVLTree< std::string, AVLTree< std::string, std::string > > inputDictionary(std::istream& in)
  {
    AVLTree< std::string, AVLTree< std::string, std::string > > treeOfdic;
    std::string line;

    while (std::getline(in, line))
    {
      if (line.empty())
      {
        continue;
      }

      size_t pos = line.find(' ');

      std::string name = line.substr(0, pos);

      AVLTree< std::string, std::string > dictionary;

      size_t start = pos + 1;
      while (start < line.length())
      {
        pos = line.find(' ', start);
        if (pos == std::string::npos)
        {
          break;
        }
        std::string key = line.substr(start, pos - start);
        start = pos + 1;

        pos = line.find(' ', start);
        if (pos == std::string::npos)
        {
          std::string word = line.substr(start);
          dictionary.push(key, word);
          break;
        }
        else
        {
          std::string word = line.substr(start, pos - start);
          dictionary.push(key, word);
          start = pos + 1;
        }
      }

      treeOfdic.push(name, dictionary);
    }

    return treeOfdic;
  }
}

