#include "commands.hpp"

namespace sakovskaia
{
  void sakovskaia::printHelp(std::ostream & output)
  {
    output << "1. Create new dictionary:\n";
    output << "   new <dictionary_name>\n";
    output << "2. Delete dictionary:\n";
    output << "   delete <dictionary_name>\n";
    output << "3. Load words from file to the dictionary:\n";
    output << "   load <dictionary_name> <file_name>\n";
    output << "4. Add word to the dictionary:\n";
    output << "   add <dictionary_name> <word>\n";
    output << "5. Save dictionary to the file:\n";
    output << "   save <dictionary_name> <file_name>\n";
    output << "6. Remove word from the dictionary:\n";
    output << "   remove <dictionary_name> <word>\n";
    output << "7. Print frequency of the word in the dictionary:\n";
    output << "   frequency <dictionary_name> <word>\n";
    output << "8. Update frequency of the word:\n";
    output << "   update <dictionary_name> <word> <new_frequency>\n";
    output << "9. Combine two dictionaries:\n";
    output << "   combining <dictionary_name1> <dictionary_name2> <result_name>\n";
    output << "10. Create a dictionary containing words and their frequencies\n";
    output << "   that are in the first dictionary, but are missing in the second:\n";
    output << "   diff <dictionary_name1> <dictionary_name2> <result_name>\n";
  }

  Tree< std::string, Tree< std::string, size_t > > inputCMD(std::string filename)
  {
    Tree< std::string, Tree< std::string, size_t > > tree;
    Tree< std::string, size_t > dict;
    std::ifstream file(filename);
    if (!file.is_open())
    {
      throw std::logic_error("Error name");
    }
    std::string word;
    while (file >> word)
    {
      if (dict.contains(word))
      {
        dict.at(word) += 1;
      }
      else
      {
        dict.push(word, 1);
      }
    }
    tree.push("dict1", dict);
    return tree;
  }

  void newCmd(Tree< std::string, Tree< std::string, size_t > > & dict, std::istream & input, std::ostream & output)
  {
    std::string name;
    if (!(input >> name))
    {
      throw std::logic_error("<INVALID ARGUMENT>");
    }
    if (dict.contains(name))
    {
      throw std::logic_error("<ALREADY EXISTS>");
    }
    else
    {
      dict.push(name, Tree< std::string, size_t >());
    }
    output << "The dictionary " << name << " has been created.\n";
  }

  void deleteCmd(Tree< std::string, Tree< std::string, size_t > > & dict, std::istream & input, std::ostream & output)
  {
    std::string name;
    if (!(input >> name))
    {
      throw std::logic_error("<INVALID ARGUMENT>");
    }
    if (dict.contains(name))
    {
      dict.remove(name);
    }
    else
    {
      throw std::logic_error("<DICTIONARY NOT FOUND>");
    }
    output << "The dictionary " << name << " has been deleted.\n";
  }

  void loadCmd(Tree< std::string, Tree< std::string, size_t > > & dict, std::istream & input, std::ostream & output)
  {
    std::string name;
    std::string filename;
    if (!(input >> name >> filename))
    {
      throw std::logic_error("<INVALID ARGUMENT>");
    }
    if (!dict.contains(name))
    {
      throw std::logic_error("<DICTIONARY NOT FOUND>");
    }
    else
    {
      std::ifstream file(filename);
      if (!file.is_open())
      {
        throw std::logic_error("<FILE NOT FOUND>");
      }
      dict = inputCMD(filename);
    }
    output << "The dictionary " << name << " has been loaded.\n";
  }

  void addCmd(Tree< std::string, Tree< std::string, size_t > > & dict, std::istream & input, std::ostream & output)
  {
    std::string name, word;
    if (!(input >> name >> word))
    {
      throw std::logic_error("<INVALID ARGUMENT>");
    }
    if (!dict.contains(name))
    {
      throw std::logic_error("<DICTIONARY NOT FOUND>");
    }
    auto & innerDict = dict.at(name);
    if (innerDict.contains(word))
    {
      innerDict.at(word) += 1;
    }
    else
    {
      innerDict.push(word, 1);
    }
    output << word << " added to " << name << ".\n";
  }

  void saveCmd(Tree<std::string, Tree<std::string, size_t>>& dict, std::istream& input, std::ostream& output)
  {
    std::string name;
    std::string filename;
    if (!(input >> name >> filename))
    {
      throw std::logic_error("<INVALID ARGUMENT>");
    }
    if (!dict.contains(name))
    {
      output << "<DICTIONARY NOT FOUND>\n";
      return;
    }
    std::ofstream file(filename);
    if (!file.is_open())
    {
      throw std::logic_error("<FILE ERROR>");
    }
    Tree< std::string, size_t > & innerDict = dict.at(name);
    std::vector< std::pair< std::string, size_t > > wordFrequencies;
    innerDict.traverseLnr(wordFrequencies);
    for (const auto & wordFrequency : wordFrequencies)
    {
        file << wordFrequency.first << " " << wordFrequency.second << "\n";
    }
    file.close();
    output << "The dictionary " << name << " has been saved.\n";
  }

  void removeCmd(Tree< std::string, Tree< std::string, size_t > > & dict, std::istream & input, std::ostream & output)
  {
    std::string name, word;
    if (!(input >> name >> word))
    {
      throw std::logic_error("<INVALID ARGUMENT>");
    }
    if (!dict.contains(name))
    {
      throw std::logic_error("<DICTIONARY NOT FOUND>");
    }
    auto & innerDict = dict.at(name);
    if (innerDict.contains(word))
    {
      innerDict.remove(word);
      output << "<" << word << " removed from dictionary>\n";
    }
    else
    {
      throw std::logic_error("<WORD NOT FOUND>");
    }
    output << "Word '" << word << "' removed and frequencies updated.\n";
  }

  void frequencyCmd(Tree< std::string, Tree< std::string, size_t > > & dict, std::istream & input, std::ostream & output)
  {
    std::string name, word;
    if (!(input >> name >> word))
    {
      throw std::logic_error("<INVALID ARGUMENT>");
    }
    if (!dict.contains(name))
    {
      throw std::logic_error("<DICTIONARY NOT FOUND>");
    }
    auto & innerDict = dict.at(name);
    if (innerDict.contains(word))
    {
      output << "Frequency of " << word << " in dictionary: " << innerDict.at(word) << "\n";
    }
    else
    {
      throw std::logic_error("<WORD NOT FOUND>");
    }
  }

  void updateCmd(Tree< std::string, Tree< std::string, size_t > > & dict, std::istream & input, std::ostream & output)
  {
    std::string name, word;
    size_t new_frequency;
    if (!(input >> name >> word >> new_frequency))
    {
      throw std::logic_error("<INVALID ARGUMENT>");
    }
    if (!dict.contains(name))
    {
      throw std::logic_error("<DICTIONARY NOT FOUND>");
    }

    auto & innerDict = dict.at(name);
    if (innerDict.contains(word))
    {
      innerDict.at(word) = new_frequency;
      output << "Frequency of " << word << " in dictionary updated to " << new_frequency << ".\n";
    }
    else
    {
      throw std::logic_error("<WORD NOT FOUND>");
    }
  }

  void combiningCmd(Tree< std::string, Tree< std::string, size_t > > & dict, std::istream & input, std::ostream & output)
  {
    std::string name1, name2, result_name;
    if (!(input >> name1 >> name2 >> result_name))
    {
      throw std::logic_error("<INVALID ARGUMENT>");
    }

    if (!dict.contains(name1) || !dict.contains(name2))
    {
      throw std::logic_error("<DICTIONARY NOT FOUND>");
    }
    const auto & dict1 = dict.at(name1);
    const auto & dict2 = dict.at(name2);
    Tree< std::string, size_t > resultDict;
    for (auto it1 = dict1.cbegin(); it1 != dict1.cend(); ++it1)
    {
      resultDict.push(it1->first, it1->second);
    }
    for (auto it2 = dict2.cbegin(); it2 != dict2.cend(); ++it2)
    {
      if (resultDict.contains(it2->first))
      {
        size_t combinedFrequency = resultDict.at(it2->first) + it2->second;
        resultDict.at(it2->first) = combinedFrequency;
      }
      else
      {
        resultDict.push(it2->first, it2->second);
      }
    }
    dict.push(result_name, resultDict);
    output << "Combined dictionaries successfully into " << result_name << ".\n";
  }

  void diffCmd(Tree< std::string, Tree< std::string, size_t > > & dict, std::istream & input, std::ostream & output)
  {
    std::string name1, name2, result_name;
    if (!(input >> name1 >> name2 >> result_name))
    {
      throw std::logic_error("<INVALID ARGUMENT>");
    }
    if (!dict.contains(name1) || !dict.contains(name2))
    {
      throw std::logic_error("<DICTIONARY NOT FOUND>");
    }
    const auto & dict1 = dict.at(name1);
    const auto & dict2 = dict.at(name2);
    Tree< std::string, size_t > resultDict;
    for (auto it = dict1.cbegin(); it != dict1.cend(); ++it)
    {
      const std::string& word = it->first;
      size_t freq1 = it->second;
      if (!dict2.contains(word) || dict2.at(word) < freq1)
      {
        resultDict.push(word, freq1);
      }
    }
    dict.push(result_name, resultDict);
    output << "Words unique to " << name1 << " saved in " << result_name << ".\n";
  }
}

