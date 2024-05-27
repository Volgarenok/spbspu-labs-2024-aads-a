#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <istream>
#include <ostream>
#include "dictionary.hpp"

namespace nikitov
{
  void printDictCmd(const Tree< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output);
  void printAllCmd(const Tree< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output);

  void findTranslationCmd(const Tree< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output);
  void findAntonymCmd(const Tree< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output);

  void translateSentenceCmd(const Tree< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output);
  void translateFileCmd(const Tree< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream& output);

  void saveCmd(const Tree< std::string, Dictionary >& dictOfDicts, std::istream& input, std::ostream&);

  void createCmd(Tree< std::string, Dictionary >& dictOfDicts, std::istream& input);

  void addTranslationCmd(Tree< std::string, Dictionary >& dictOfDicts, std::istream& input);
  void addAntonymCmd(Tree< std::string, Dictionary >& dictOfDicts, std::istream& input);

  void editPrimaryCmd(Tree< std::string, Dictionary >& dictOfDicts, std::istream& input);
  void editSecondaryCmd(Tree< std::string, Dictionary >& dictOfDicts, std::istream& input);

  void deletePrimaryCmd(Tree< std::string, Dictionary >& dictOfDicts, std::istream& input);
  void deleteSecondaryCmd(Tree< std::string, Dictionary >& dictOfDicts, std::istream& input);
  void deleteAntonymCmd(Tree< std::string, Dictionary >& dictOfDicts, std::istream& input);

  void mergeCmd(Tree< std::string, Dictionary >& dictOfDicts, std::istream& input);
}
#endif
