#include "cmd.hpp"
#include <vector>
#include <iostream>
#include <fstream>

namespace sivkov
{
  using tree = AVLTree< std::string, AVLTree< std::string, std::string > >;

  void add_word(tree& treeOfdic, std::istream& in)
  {
    std::string dictionaryName = "";
    std::string englishWord = "";
    if (!(in >> dictionaryName >> englishWord))
    {
      throw std::logic_error("Invalid arguments");
    }
    if (!treeOfdic.contains(dictionaryName))
    {
      throw std::logic_error("Dictionary not found");
    }

    AVLTree< std::string, std::string >& dictionary = treeOfdic.at(dictionaryName);

    if (!dictionary.contains(englishWord))
    {
      dictionary.push(englishWord, "");
    }
  }

  void add_translation(tree& treeOfdic, std::istream& in)
  {
    std::string dictionaryName = "";
    std::string englishWord = "";
    std::string russianWord = "";
    if (!(in >> dictionaryName >> englishWord >> russianWord))
    {
      throw std::logic_error("Invalid arguments");
    }

    if (!treeOfdic.contains(dictionaryName))
    {
      throw std::logic_error("Dictionary not found");
    }

    AVLTree< std::string, std::string >& dictionary = treeOfdic.at(dictionaryName);

    if (!dictionary.contains(englishWord))
    {
      throw std::logic_error("Word not found");
    }
    dictionary[englishWord] = russianWord;
  }

  void create_dictionary(tree& treeOfdic, std::istream& in)
  {
    std::string dictionaryName;
    if (!(in >> dictionaryName))
    {
      throw std::logic_error("Invalid arguments");
    }

    if (treeOfdic.contains(dictionaryName))
    {
      throw std::logic_error("Dictionary already exists");
    }
    treeOfdic.push(dictionaryName, AVLTree< std::string, std::string >());
  }

  void remove_word(tree& treeOfdic, std::istream& in)
  {
    std::string dictionaryName, englishWord;
    if (!(in >> dictionaryName >> englishWord))
    {
      throw std::logic_error("Invalid arguments");
    }

    if (!treeOfdic.contains(dictionaryName))
    {
      throw std::logic_error("Dictionary not found");
    }

    AVLTree< std::string, std::string >& dictionary = treeOfdic.at(dictionaryName);

    if (!dictionary.contains(englishWord))
    {
      throw std::logic_error("Word not found");
    }

    dictionary.deleteKey(englishWord);
  }

  void list_words(const tree& treeOfdic, std::istream& in, std::ostream& out)
  {
    std::string dictionaryName;
    if (!(in >> dictionaryName))
    {
      throw std::logic_error("Invalid arguments");
    }

    if (!treeOfdic.contains(dictionaryName))
    {
      throw std::logic_error("Dictionary not found");
    }

    const AVLTree< std::string, std::string >& dictionary = treeOfdic.at(dictionaryName);
    for (auto it = dictionary.cbegin(); it != dictionary.cend(); ++it)
    {
      out << it->first << " - " << it->second << "\n";
    }
  }

  void search_words(const tree& treeOfdic, std::istream& in, std::ostream& out)
  {
    std::string line;

    if (!std::getline(in, line))
    {
      throw std::logic_error("Invalid arguments");
    }

    std::vector< std::string > words;
    std::string word;
    size_t pos = 0, prev_pos = 0;

    while ((pos = line.find(' ', prev_pos)) != std::string::npos)
    {
      word = line.substr(prev_pos, pos - prev_pos);
      if (!word.empty())
      {
        words.push_back(word);
      }
      prev_pos = pos + 1;
    }
    word = line.substr(prev_pos);
    if (!word.empty())
    {
      words.push_back(word);
    }

    if (words.empty())
    {
      throw std::logic_error("No dictionary name provided");
    }
    std::string dictionaryName = words[0];

    if (!treeOfdic.contains(dictionaryName))
    {
      throw std::logic_error("Dictionary not found");
    }

    const AVLTree< std::string, std::string >& dictionary = treeOfdic.at(dictionaryName);

    for (size_t i = 1; i < words.size(); ++i)
    {
      const std::string& searchWord = words[i];
      if (dictionary.contains(searchWord))
      {
        out << searchWord << " - " << dictionary.at(searchWord) << "\n";
      }
      else
      {
        throw std::logic_error("Invalid arguments");
      }
    }
  }

  void delete_dictionary(tree& treeOfdic, std::istream& in)
  {
    std::string dictionaryName;
    if (!(in >> dictionaryName))
    {
      throw std::logic_error("Invalid arguments");
    }

    if (!treeOfdic.contains(dictionaryName))
    {
      throw std::logic_error("Dictionary not found");
    }

    treeOfdic.deleteKey(dictionaryName);
  }

  void rename_dictionary(tree& treeOfdic, std::istream& in)
  {
    std::string dictionaryName = "";
    std::string newDictionaryName = "";
    if (!(in >> dictionaryName >> newDictionaryName))
    {
      throw std::logic_error("Invalid arguments");
    }

    if (!treeOfdic.contains(dictionaryName) || treeOfdic.contains(newDictionaryName))
    {
      throw std::logic_error("Dictionary not found or new name already exists");
    }

    AVLTree< std::string, std::string > dictionary = treeOfdic.at(dictionaryName);
    treeOfdic.deleteKey(dictionaryName);
    treeOfdic.push(newDictionaryName, dictionary);
  }

  void count_words(const tree& treeOfdic, std::istream& in, std::ostream& out)
  {
    std::string dictionaryName = "";
    if (!(in >> dictionaryName))
    {
      throw std::logic_error("Invalid arguments");
    }

    if (!treeOfdic.contains(dictionaryName))
    {
      throw std::logic_error("Dictionary not found");
    }

    const AVLTree< std::string, std::string >& dictionary = treeOfdic.at(dictionaryName);
    out << dictionary.getSize() << "\n";
  }

  void merge_dictionaries(tree& treeOfdic, std::istream& in)
  {
    std::string line;

    if (!std::getline(in, line) || line.empty())
    {
      throw std::out_of_range("Invalid arguments");
    }

    std::vector< std::string > words;
    std::string word;
    size_t pos = 0, prev_pos = 0;

    while ((pos = line.find(' ', prev_pos)) != std::string::npos)
    {
      word = line.substr(prev_pos, pos - prev_pos);
      if (!word.empty())
      {
        words.push_back(word);
      }
      prev_pos = pos + 1;
    }

    word = line.substr(prev_pos);
    if (!word.empty())
    {
      words.push_back(word);
    }

    if (words.empty())
    {
      throw std::out_of_range("Invalid arguments");
    }

    std::string newDictionaryName = words.front();
    words.erase(words.begin());

    if (treeOfdic.contains(newDictionaryName))
    {
      throw std::out_of_range("New dictionary name already exists");
    }

    AVLTree< std::string, std::string > newDictionary;

    for (const std::string& dictionaryName : words)
    {
      if (!treeOfdic.contains(dictionaryName))
      {
        throw std::out_of_range("Invalid arguments");
      }

      AVLTree< std::string, std::string >& dictionary = treeOfdic.at(dictionaryName);

      for (auto it = dictionary.cbegin(); it != dictionary.cend(); ++it)
      {
        newDictionary.push(it->first, it->second);
      }
    }
    treeOfdic.push(newDictionaryName, newDictionary);
  }

  void repeating_words(const tree& treeOfdic, std::istream& in, std::ostream& out)
  {
    std::string line;

    if (!std::getline(in, line))
    {
      throw std::logic_error("Error reading dictionaries");
    }

    if (line.empty())
    {
      throw std::out_of_range("No dictionaries specified");
    }

    std::vector< std::string > dictionaryNames;
    std::string dictionaryName;
    size_t pos = 0, prev_pos = 0;

    while ((pos = line.find(' ', prev_pos)) != std::string::npos)
    {
      dictionaryName = line.substr(prev_pos, pos - prev_pos);
      if (!dictionaryName.empty())
      {
        dictionaryNames.push_back(dictionaryName);
      }
      prev_pos = pos + 1;
    }

    dictionaryName = line.substr(prev_pos);
    if (!dictionaryName.empty())
    {
      dictionaryNames.push_back(dictionaryName);
    }

    if (dictionaryNames.empty())
    {
      throw std::out_of_range("No dictionaries specified");
    }

    for (const auto& name : dictionaryNames)
    {
      if (!treeOfdic.contains(name))
      {
        throw std::out_of_range("One or more dictionaries not found");
      }
    }
    AVLTree< std::string, size_t > wordCount;

    for (const std::string& name : dictionaryNames)
    {
      const AVLTree< std::string, std::string >& dictionary = treeOfdic.at(name);
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

    out << commonWordCount << "\n";
  }

  void save(const tree& treeOfdic, const std::string& filename)
  {
    std::ofstream outFile(filename);
    if (!outFile.is_open())
    {
      throw std::logic_error("Cannot open file");
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

  void help(std::ostream& out)
  {
    out << "add_translation <словарь> <слово> <перевод> - Добавить перевод\n";
    out << "add_word <словарь> <слово> - Добавить слово\n";
    out << "count_words <словарь> - Вывод кол-ва слов\n";
    out << "create <словарь> - Создать словарь\n";
    out << "delete_dictionary <словарь> - Удалить словарь\n";
    out << "list_words <словарь> - Вывод списка слов\n";
    out << "merge <новый_словарь> <словарь1> <словарь2> ... <словарьN> -";
    out << "Создать новый словарь из старых\n";
    out << "remove_word <словарь> <слово> - Удалить слово\n";
    out << "rename_dictionary <словарь> <новое_название> - Переименовать словарь\n";
    out << "repeating_words <словарь1> <словарь2> ... <словарьN> -";
    out << "Поиск одинаковых слов в указанных словарях\n";
    out << "search <словарь> <слово1> <слово2> ... <словоN> - Поиск слова\n";
  }
}
