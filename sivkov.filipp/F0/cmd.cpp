#include "cmd.hpp"
#include <vector>
#include <iostream>
#include <fstream>
namespace sivkov
{
  void add_word(AVLTree< std::string, AVLTree< std::string, std::string > >& treeOfdic, std::istream& in)
  {
    std::string dictionaryName = "";
    std::string englishWord = "";
    if (!(in >> dictionaryName >> englishWord))
    {
      throw std::logic_error("Error arguments");
    }

    if (!treeOfdic.contains(dictionaryName))
    {
      throw std::logic_error("no dict");
    }

    AVLTree< std::string, std::string >& dictionary = treeOfdic.at(dictionaryName);

    if (!dictionary.contains(englishWord))
    {
      dictionary.push(englishWord, "");
    }
  }
}
