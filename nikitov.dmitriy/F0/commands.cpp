#include "commands.hpp"
#include <fstream>
#include <functional>
#include <algorithm>
#include "dictionary.hpp"

void nikitov::printHelp(std::ostream& output)
{
  output << "Command system:" << '\n'
    << "1. print dictionary <dictName> - output of all words in the specified dictionary" << '\n'
    << "2. print all - output of all words from all dictionaries" << '\n'
    << "3. print names - output the names of all dictionaries" << '\n'
    << "4. find translation <dictName> <word> - search and output of a word translation from the dictionary" << '\n'
    << "5. find antonym <dictName> <word> - search and output of the word's antonyms from the dictionary" << '\n'
    << "6. translate sentence <dictName> - outputs a machine translation of a sentence based on the specified dictionary" << '\n'
    << "7. translate file <dictName> <inputFile> <outputFile> - reads text from a file and writes the translation to another file" << '\n'
    << "8. save dictionary <dictName> <newFileName> - saves the specified dictionary to a file" << '\n'
    << "9. create dictionary <dictName> - creates an empty dictionary with the specified name" << '\n'
    << "10. add translation <dictName> <word> <translation> - adds a word with a translation to the specified dictionary" << '\n'
    << "11. add antonym <dictName> <word> <antonym> - adds an antonym to the word" << '\n'
    << "12. edit primary <dictName> <word> - changes the main translation of the word" << '\n'
    << "13. edit secondary <dictName> <word> - changes the second translation of the word" << '\n'
    << "14. delete primary <dictName> <word> - delete the main translation of the word" << '\n'
    << "15. delete secondary <dictName> <word> - delete the second translation of the word" << '\n'
    << "16. delete antonym <dictName> <word> - remove the antonym of the word" << '\n'
    << "17. merge dictionary <firstDictName> <secondDictName> <newDictName> - creates a new dictionary based on the other two" << '\n';
}

void nikitov::printDictCmd(const Tree< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output)
{
  std::string dictName;
  input >> dictName;
  output << dictOfDicts.at(dictName);
}

void nikitov::printAllCmd(const Tree< std::string, Dictionary >& dictOfDicts, std::istream&, std::ostream& output)
{
  for (auto i = dictOfDicts.cbegin(); i != dictOfDicts.cend(); ++i)
  {
    output << i->second;
  }
}

void nikitov::printNamesCmd(const Tree< std::string, Dictionary >& dictOfDicts, std::istream&, std::ostream& output)
{
  for (auto i = dictOfDicts.cbegin(); i != dictOfDicts.cend(); ++i)
  {
    output << i->first << '\n';
  }
}

void nikitov::findCmd(const Tree< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output,
  const std::string& parameter)
{
  std::string dictionaryName;
  input >> dictionaryName;
  std::string word;
  input >> word;
  if (parameter == "translation")
  {
    output << dictOfDicts.at(dictionaryName).findWord(word) << '\n';
  }
  else
  {
    output << dictOfDicts.at(dictionaryName).findAntonym(word) << '\n';
  }
}

char translate(const nikitov::Tree< std::string, nikitov::Dictionary >& dictOfDicts, const std::string& dictionaryName,
  std::istream& input, std::ostream& output)
{
  std::string line;
  input >> line;
  char symb = ' ';
  std::string temp = line;
  for (auto i = temp.begin(); i != temp.end(); ++i)
  {
    *i = std::tolower(*i);
  }

  try
  {
    if (!temp.empty() && !std::isalpha(temp.back()))
    {
      symb = temp.back();
      temp.pop_back();
      line.pop_back();
    }
    temp = dictOfDicts.at(dictionaryName).findTranslation(temp);
    output << temp;
  }
  catch (const std::exception&)
  {
    output << line;
  }
  if (symb != ' ')
  {
    output << symb;
  }
  return symb;
}

void nikitov::translateSentenceCmd(const Tree< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output)
{
  std::string dictionaryName;
  input >> dictionaryName;
  char symb = ' ';
  bool isFirst = true;

  while (input && symb != '.')
  {
    if (!isFirst)
    {
      output << ' ';
    }
    isFirst = false;
    symb = translate(dictOfDicts, dictionaryName, input, output);
  }
  output << '\n';
}

void nikitov::translateFileCmd(const Tree< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream&)
{
  std::string dictionaryName;
  input >> dictionaryName;
  std::string fileName;
  input >> fileName;
  std::string newFileName;
  input >> newFileName;

  std::ifstream fileInput(fileName);
  std::ofstream fileOutput(newFileName);
  bool isFirst = true;

  while (fileInput)
  {
    if (!isFirst)
    {
      fileOutput << ' ';
    }
    isFirst = false;
    translate(dictOfDicts, dictionaryName, fileInput, fileOutput);
  }
  fileOutput << '\n';
}

void nikitov::saveCmd(const Tree< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream&)
{
  std::string dictName;
  input >> dictName;
  std::string newFileName;
  input >> newFileName;
  std::ofstream fileOutput(newFileName);
  fileOutput << dictOfDicts.at(dictName);
}

void nikitov::createCmd(Tree< std::string, Dictionary >& dictOfDicts, std::istream& input)
{
  std::string dictionaryName;
  input >> dictionaryName;
  if (!dictOfDicts.insert({ dictionaryName, Dictionary() }).second)
  {
    throw std::logic_error("<ERROR: ALREADY EXIST>");
  }
}

void nikitov::addCmd(Tree< std::string, Dictionary >& dictOfDicts, std::istream& input, const std::string& parameter)
{
  std::string dictionaryName;
  input >> dictionaryName;
  std::string word;
  std::string translation;
  input >> word >> translation;
  if (parameter == "translation")
  {
    dictOfDicts.at(dictionaryName).addTranslation(word, translation);
  }
  else
  {
    dictOfDicts.at(dictionaryName).addAntonym(word, translation);
  }
}

void nikitov::editCmd(Tree< std::string, Dictionary >& dictOfDicts, std::istream& input, const std::string& parameter)
{
  std::string dictionaryName;
  input >> dictionaryName;
  std::string word;
  input >> word;
  std::string translation;
  input >> translation;
  if (parameter == "primary")
  {
    dictOfDicts.at(dictionaryName).editPrimaryTranslation(word, translation);
  }
  else
  {
    dictOfDicts.at(dictionaryName).editSecondaryTranslation(word, translation);
  }
}

void nikitov::deleteCmd(Tree< std::string, Dictionary >& dictOfDicts, std::istream& input, const std::string& parameter)
{
  std::string dictionaryName;
  input >> dictionaryName;
  std::string word;
  input >> word;
  if (parameter == "primary")
  {
    dictOfDicts.at(dictionaryName).deletePrimaryTranslation(word);
  }
  else if (parameter == "secondary")
  {
    dictOfDicts.at(dictionaryName).deleteSecondaryTranslation(word);
  }
  else
  {
    dictOfDicts.at(dictionaryName).deleteAntonym(word);
  }
}

void nikitov::mergeCmd(Tree< std::string, Dictionary >& dictOfDicts, std::istream& input)
{
  std::string firstDictionaryName;
  input >> firstDictionaryName;
  auto firstDict = dictOfDicts.at(firstDictionaryName);
  std::string secondDictionaryName;
  input >> secondDictionaryName;
  auto secondDict = dictOfDicts.at(secondDictionaryName);
  std::string newDictionaryName;
  input >> newDictionaryName;
  auto newDict = firstDict;
  for (auto i = secondDict.data_.cbegin(); i != secondDict.data_.cend(); ++i)
  {
    newDict.data_.insert(*i);
  }
  dictOfDicts.insert({ newDictionaryName, newDict });
}
