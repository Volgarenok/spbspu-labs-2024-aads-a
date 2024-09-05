#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include "dictionary.hpp"

namespace nikitov
{
  void printHelp(std::ostream& output);

  void printDictCmd(const Tree< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output);
  void printAllCmd(const Tree< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output);
  void printNamesCmd(const Tree< std::string, Dictionary >& dictOfDicts, std::istream&, std::ostream& output);
  void findCmd(const Tree< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output,
    const std::string& parameter);
  void translateSentenceCmd(const Tree< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output);
  void translateFileCmd(const Tree< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output);
  void saveCmd(const Tree< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream&);

  void createCmd(Tree< std::string, Dictionary >& dictOfDicts, std::istream& input);
  void addCmd(Tree< std::string, Dictionary >& dictOfDicts, std::istream& input, const std::string& parameter);
  void editCmd(Tree< std::string, Dictionary >& dictOfDicts, std::istream& input, const std::string& parameter);
  void deleteCmd(Tree< std::string, Dictionary >& dictOfDicts, std::istream& input, const std::string& parameter);
  void mergeCmd(Tree< std::string, Dictionary >& dictOfDicts, std::istream& input);
}
#endif
