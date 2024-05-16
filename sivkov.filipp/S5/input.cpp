#include "input.hpp"

namespace sivkov
{
  void inputDictionary(AVLTree< int, std::string >& dictionary, std::istream& in)
  {
    while (!in.eof())
    {
      in.clear();
      int key = 0;
      while (in >> key)
      {
        std::string word = "";
        in >> word;
        dictionary.push(key, word);
      }
    }
  }
}

