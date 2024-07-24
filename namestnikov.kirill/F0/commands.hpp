#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>
#include <hash_table.hpp>

namespace namestnikov
{
  using dictMain = HashTable< std::string, HashTable< std::string, std::string > >;
  void doHelp(std::ostream & out);
  void doCreate(std::istream & in, dictMain & mainMap, std::ostream & out);
  void doAdd(std::istream & in, dictMain & mainMap, std::ostream & out);
  void doFind(std::istream & in, dictMain & mainMap, std::ostream & out);
  void doRemove(std::istream & in, dictMain & mainMap, std::ostream & out);
  void doSubtract(std::istream & in, dictMain & mainMap, std::ostream & out);
  void doMerge(std::istream & in, dictMain & mainMap, std::ostream & out);
  void doExport(std::istream & in, const dictMain & mainMap);
  void doImport(std::istream & in, dictMain & mainMap);
  void doPrefix(std::istream & in, dictMain & mainMap, std::ostream & out);
  void doPostfix(std::istream & in, dictMain & mainMap, std::ostream & out);
  void doSuffix(std::istream & in, dictMain & mainMap, std::ostream & out);
  void doPalindrome(std::istream & in, dictMain & mainMap, std::ostream & out);
}

#endif
