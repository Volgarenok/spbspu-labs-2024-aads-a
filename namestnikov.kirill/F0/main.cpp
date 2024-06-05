#include "hash_table.hpp"
#include <iostream>


int main()
{
  using namespace namestnikov;
  HashTable< std::string, std::string > h;
  h["kirill"] = "wizyx";
  std::cout << h["kirill"];
}
