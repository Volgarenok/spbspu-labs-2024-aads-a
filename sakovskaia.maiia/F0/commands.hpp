#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <ostream>
#include <map>
#include <string>
#include <fstream>
#include "tree.hpp"

namespace sakovskaia
{
  void printHelp(std::ostream & output);
  Tree< std::string, Tree< std::string, size_t > > inputCMD(std::string filename);
  void newCmd(Tree< std::string, Tree< std::string, size_t > > & dict, std::istream & input, std::ostream & output);
  void deleteCmd(Tree< std::string, Tree< std::string, size_t > > & dict, std::istream & input, std::ostream & output);
  void loadCmd(Tree< std::string, Tree< std::string, size_t > > & dict, std::istream & input, std::ostream & output);
  void addCmd(Tree< std::string, Tree< std::string, size_t > > & dict, std::istream & input, std::ostream & output);
  void saveCmd(Tree< std::string, Tree< std::string, size_t > > & dict, std::istream & input, std::ostream & output);
  void removeCmd(Tree< std::string, Tree< std::string, size_t > > & dict, std::istream & input, std::ostream & output);
  void frequencyCmd(Tree< std::string, Tree< std::string, size_t > > & dict, std::istream & input, std::ostream & output);
  void updateCmd(Tree< std::string, Tree< std::string, size_t > > & dict, std::istream & input, std::ostream & output);
  void combiningCmd(Tree< std::string, Tree< std::string, size_t > > & dict, std::istream & input, std::ostream & output);
  void diffCmd(Tree< std::string, Tree< std::string, size_t > > & dict, std::istream & input, std::ostream & output);
}
#endif
