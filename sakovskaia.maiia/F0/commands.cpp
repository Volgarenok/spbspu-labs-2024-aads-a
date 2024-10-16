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
}

