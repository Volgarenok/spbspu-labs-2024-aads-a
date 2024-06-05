#ifndef INPUTMAP_HPP
#define INPUTMAP_HPP
#include <iosfwd>
#include <map>
#include <string>
#include <tree/binarySearchTree.hpp>

namespace strelyaev
{
 Tree< std::string, Tree< int, std::string > > inputMap(std::istream&);
}

#endif

