#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "eng-rusDictionary.hpp"
#include "binarySearchTree.hpp"
#include "MyVector.hpp"

namespace belokurskaya
{
  namespace cmd
  {
    void createDict(BinarySearchTree< std::string, EngRusDict >& EngRusDicts, std::istream& in);
    void removeDict(BinarySearchTree< std::string, EngRusDict >& EngRusDicts, std::istream& in);
    void add(BinarySearchTree< std::string, EngRusDict >& EngRusDicts, std::istream& in);
    void remove(BinarySearchTree< std::string, EngRusDict >& EngRusDicts, std::istream& in);
    void assign(BinarySearchTree< std::string, EngRusDict >& EngRusDicts, std::istream& in);
    void removeWords(BinarySearchTree< std::string, EngRusDict >& EngRusDicts, std::istream& in);
    void getIntersection(BinarySearchTree< std::string, EngRusDict >& EngRusDicts, std::istream& in);
    void getDifference(BinarySearchTree< std::string, EngRusDict >& EngRusDicts, std::istream& in);
    void clear(BinarySearchTree< std::string, EngRusDict >& EngRusDicts, std::istream& in);
    void display(BinarySearchTree< std::string, EngRusDict >& EngRusDicts, std::istream& in, std::ostream& out);
    void getTranslation(BinarySearchTree< std::string, EngRusDict >& EngRusDicts, std::istream&, std::ostream& out);
    void countTranslations(BinarySearchTree< std::string, EngRusDict >& EngRusDicts, std::istream& in, std::ostream& out);
    void help(std::ostream& out);
    void checkFile(std::istream& in, std::ostream& out);
  }
}

#endif
