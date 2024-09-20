#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include <tree/tree.hpp>
#include <string>

namespace baranov
{
  using dict_t = Tree< std::string, size_t >;
  void createCmd(Tree< std::string, dict_t > & dicts, std::istream & in, std::ostream &);
  void clearCmd(Tree< std::string, dict_t > & dicts, std::istream & in, std::ostream &);
  void deleteCmd(Tree< std::string, dict_t > & dicts, std::istream & in, std::ostream &);
  void addWordsCmd(Tree< std::string, dict_t > & dicts, std::istream & in, std::ostream &);
  void printCountCmd(const Tree< std::string, dict_t > & dicts, std::istream & in, std::ostream & out);
  void printDictCmd(const Tree< std::string, dict_t > & dicts, std::istream & in, std::ostream & out);
  void printTopCmd(const Tree< std::string, dict_t > & dicts, std::istream & in, std::ostream & out);
  void joinCmd(Tree< std::string, dict_t > & dicts, std::istream & in, std::ostream &);
  void intersectCmd(Tree< std::string, dict_t > & dicts, std::istream & in, std::ostream &);
  void saveCmd(const Tree< std::string, dict_t > & dicts, std::istream & in, std::ostream &);
  void lsDictsCmd(const Tree< std::string, dict_t > & dicts, std::istream &, std::ostream & out);
}

#endif

