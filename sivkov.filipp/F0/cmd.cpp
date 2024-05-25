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

  void remove_word(AVLTree< std::string, AVLTree< std::string, std::string > >& treeOfdic, std::istream& in)
  {
    std::string dictionaryName, englishWord;
    if (!(in >> dictionaryName >> englishWord))
    {
      throw std::logic_error("Error arguments");
    }

    if (!treeOfdic.contains(dictionaryName))
    {
      throw std::logic_error("");
    }

    AVLTree< std::string, std::string >& dictionary = treeOfdic.at(dictionaryName);

    if (!dictionary.contains(englishWord))
    {
      throw std::logic_error("");
    }

    dictionary.deleteKey(englishWord);
  }

  void list_words(const AVLTree< std::string, AVLTree< std::string, std::string > >& treeOfdic, std::istream& in, std::ostream& out)
  {
    std::string dictionaryName;
    if (!(in >> dictionaryName))
    {
      throw std::logic_error("Error arguments");
    }

    if (!treeOfdic.contains(dictionaryName))
    {
      throw std::logic_error("");
    }

    const AVLTree< std::string, std::string >& dictionary = treeOfdic.at(dictionaryName);
    for (auto it = dictionary.cbegin(); it != dictionary.cend(); ++it)
    {
      out << it->first << " - " << it->second << std::endl;
    }
  }

  void search_words(const AVLTree< std::string, AVLTree< std::string, std::string > >& treeOfdic, std::istream& in, std::ostream& out)
  {
    std::string dictionaryName;
    if (!(in >> dictionaryName))
    {
      throw std::logic_error("Error arguments");
    }

    if (!treeOfdic.contains(dictionaryName))
    {
      throw std::logic_error("");
    }

    const AVLTree< std::string, std::string >& dictionary = treeOfdic.at(dictionaryName);

    std::string word;
    while (in >> word)
    {
      if (dictionary.contains(word))
      {
        out << dictionary.at(word) << std::endl;
      }
      else
      {
        throw std::logic_error("error");
      }
    }
  }

  void delete_dictionary(AVLTree< std::string, AVLTree< std::string, std::string > >& treeOfdic, std::istream& in)
  {
    std::string dictionaryName;
    if (!(in >> dictionaryName))
    {
      throw std::logic_error("Error arguments");
    }

    if (!treeOfdic.contains(dictionaryName))
    {
      throw std::logic_error("");
    }

    treeOfdic.deleteKey(dictionaryName);
  }

  void rename_dictionary(AVLTree< std::string, AVLTree< std::string, std::string > >& treeOfdic, std::istream& in)
  {
    std::string dictionaryName = "";
    std::string newDictionaryName = "";
    if (!(in >> dictionaryName >> newDictionaryName))
    {
      throw std::logic_error("Error arguments");
    }

    if (!treeOfdic.contains(dictionaryName) || treeOfdic.contains(newDictionaryName))
    {
      throw std::logic_error("");
    }

    AVLTree< std::string, std::string > dictionary = treeOfdic.at(dictionaryName);
    treeOfdic.deleteKey(dictionaryName);
    treeOfdic.push(newDictionaryName, dictionary);
  }

  void count_words(const AVLTree< std::string, AVLTree< std::string, std::string > >& treeOfdic, std::istream& in, std::ostream& out)
  {
    std::string dictionaryName = "";
    if (!(in >> dictionaryName))
    {
      throw std::logic_error("Error arguments");
    }

    if (!treeOfdic.contains(dictionaryName))
    {
      throw std::logic_error("");
    }

    const AVLTree< std::string, std::string >& dictionary = treeOfdic.at(dictionaryName);
    out << dictionary.size() << std::endl;
  }

  void merge_dictionaries(AVLTree< std::string, AVLTree< std::string, std::string > >& treeOfdic, std::istream& in)
  {
    std::string newDictionaryName = "";
    if (!(in >> newDictionaryName))
    {
      throw std::logic_error("Error arguments");
    }

    if (treeOfdic.contains(newDictionaryName))
    {
      throw std::logic_error("");
    }

    AVLTree< std::string, std::string > newDictionary;
    std::string dictionaryName = "";
    bool invalidDictionary = false;

    while (in >> dictionaryName)
    {
      if (!treeOfdic.contains(dictionaryName))
      {
        invalidDictionary = true;
        continue;
      }

      const AVLTree< std::string, std::string >& dictionary = treeOfdic.at(dictionaryName);

      for (auto it = dictionary.cbegin(); it != dictionary.cend(); ++it)
      {
        newDictionary[it->first] = it->second;
      }
    }

    treeOfdic.push(newDictionaryName, newDictionary);

    if (invalidDictionary)
    {
      throw std::logic_error("error dict");
    }
  }

  void repeating_words(const AVLTree<std::string, AVLTree<std::string, std::string>>& treeOfdic, std::istream& in, std::ostream& out)
  {
    std::vector<std::string> dictionaryNames;
    std::string dictionaryName = "";

    while (in >> dictionaryName)
    {
      if (!treeOfdic.contains(dictionaryName))
      {
        throw std::logic_error("Error arguments");
      }
      dictionaryNames.push_back(dictionaryName);
    }

    if (dictionaryNames.empty())
    {
      throw std::logic_error("empty");
    }

    AVLTree<std::string, int> wordCount;

    for (size_t i = 0; i < dictionaryNames.size(); ++i)
    {
      const std::string& name = dictionaryNames[i];
      const AVLTree<std::string, std::string>& dictionary = treeOfdic.at(name);
      for (auto it = dictionary.cbegin(); it != dictionary.cend(); ++it)
      {
        const std::string& word = it->first;
        if (wordCount.contains(word))
        {
          wordCount[word] = wordCount.at(word) + 1;
        }
        else
        {
          wordCount.push(word, 1);
        }
      }
    }

    size_t commonWordCount = 0;
    for (auto it = wordCount.cbegin(); it != wordCount.cend(); ++it)
    {
      if (it->second == dictionaryNames.size())
      {
        commonWordCount++;
      }
    }

    out << commonWordCount << std::endl;
  }


  void save(const AVLTree< std::string, AVLTree< std::string, std::string > >& treeOfdic, const std::string& filename)
  {
    std::ofstream outFile(filename);
    if (!outFile.is_open())
    {
      throw std::logic_error("cant open file");
    }

    for (auto it = treeOfdic.cbegin(); it != treeOfdic.cend(); ++it)
    {
      outFile << it->first;

      const AVLTree< std::string, std::string >& dictionary = it->second;
      for (auto it2 = dictionary.cbegin(); it2 != dictionary.cend(); ++it2)
      {
        outFile << " " << it2->first << " " << it2->second;
      }

      outFile << "\n";
    }
  }

}

