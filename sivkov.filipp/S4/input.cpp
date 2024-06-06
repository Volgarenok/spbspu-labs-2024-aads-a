#include "input.hpp"

namespace sivkov
{
  AVLTree < std::string, AVLTree< size_t, std::string > > inputDictionary(std::istream& in)
  {
    AVLTree < std::string, AVLTree< size_t, std::string > > treeOfdic;
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
    return treeOfdic;
  }
}
