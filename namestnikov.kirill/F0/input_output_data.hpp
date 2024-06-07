#ifndef INPUT_OUTPUT_DATA_HPP
#define INPUT_OUTPUT_DATA_HPP

#include <fstream>
#include <hash_table.hpp>

namespace namestnikov
{
  HashTable< std::string, std::string > inputDict(std::ifstream & in);
  void outputDict(std::ofstream & out, const HashTable< std::string, std::string > & dict);
}

#endif
