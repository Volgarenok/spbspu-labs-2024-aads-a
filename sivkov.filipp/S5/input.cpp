#include "input.hpp"

namespace sivkov
{
  void inputDictionary(AVLTree< int, std::string >& dictionary, std::istream& in)
  {
    while (in)
    {
      std::string word = "";
      int key = 0;
      while (in >> key)
      {
        in >> word;
        dictionary.push(key, word);
      }
    }
    if (!in.eof())
    {
      throw std::logic_error("error data");
    }
  }
}
