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

  void add_translation(AVLTree< std::string, AVLTree< std::string, std::string > >& treeOfdic, std::istream& in)
  {
    std::string dictionaryName = "";
    std::string englishWord = "";
    std::string russianWord = "";
    if (!(in >> dictionaryName >> englishWord >> russianWord))
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
      throw std::logic_error("no word");
    }
    dictionary[englishWord] = russianWord;
  }

  void create_dictionary(AVLTree< std::string, AVLTree< std::string, std::string > >& treeOfdic, std::istream& in)
  {
    std::string dictionaryName;
    if (!(in >> dictionaryName))
    {
      throw std::logic_error("Error arguments");
    }

    if (treeOfdic.contains(dictionaryName))
    {
      throw std::logic_error("dictionary already exists");
    }
    treeOfdic.push(dictionaryName, AVLTree< std::string, std::string >());
  }
}
