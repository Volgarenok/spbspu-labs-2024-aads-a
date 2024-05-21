#include "input.hpp"

namespace sivkov
{
  void inputDictionary(AVLTree < std::string, AVLTree< size_t, std::string > >& treeOfdic, std::istream& in)
  {
    while (!in.eof())
    {
      in.clear();
      std::string name = "";
      AVLTree< size_t, std::string > dictionary;
      size_t key = 0;
      in >> name;
      while (in >> key)
      {
        std::string word = "";
        in >> word;
        dictionary.push(key, word);
      }
      treeOfdic.push(name, dictionary);
    }
  }
}
