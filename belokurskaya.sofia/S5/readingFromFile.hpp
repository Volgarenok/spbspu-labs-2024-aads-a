#ifndef READING_FROM_FILE_HPP
#define READING_FROM_FILE_HPP

#include <istream>
#include <string>

#include "binarySearchTree.hpp"

namespace belokurskaya
{
  void readingFromFile(std::istream& in, BinarySearchTree< int, std::string >& tree);
}

#endif
