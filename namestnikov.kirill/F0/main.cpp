#include "hash_table.hpp"
#include <iostream>


int main()
{
  using namespace namestnikov;
  HashTable< std::string, std::string > h;
  h["kirill"] = "ki";
  h["maxxxxxx"] = "ma";
  h.insert("ki", "a");
  h.insert("wiii", "mee");
  /*
  std::cout << h["wiii"];
  std::cout << h["kirill"];
  std::cout << h["maxxxxxx"];
  std::cout << h["ki"];
  */
  for (const auto & key: h)
  {
    std::cout << key.first;
  }
  std::cout << "\n";
  h.erase("ki");
  std::cout << h["ki"];
  h.erase("ki");
  std::cout << h.size();
  std::cout << h.size();
  std::list < std::string > list;
}
