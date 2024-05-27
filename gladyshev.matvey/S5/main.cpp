#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include "avltree.hpp"
#include "sumfunc.hpp"

int main(int argc, char* argv[])
{
  using namespace gladyshev;
  Tree< int, std::string > dict;
  if (argc == 3)
  {
    int key = 0;
    std::string value = "";
    std::ifstream file(argv[2]);
    while (file >> key >> value)
    {
      dict.insert(key, value);
    }
  }
  else
  {
    std::cerr << "No such file\n";
    return 1;
  }
  try
  {
    Key_summ func;
    if (std::strcmp(argv[1], "ascending") == 0)
    {
      func = dict.traverse_lnr(func);
    }
    else if (std::strcmp(argv[1], "descending") == 0)
    {
      func = dict.traverse_rnl(func);
    }
    else if (std::strcmp(argv[1], "breadth") == 0)
    {
      func = dict.traverse_breadth(func);
    }
    else
    {
      std::cerr << "Bad data\n";
      return 1;
    }
    std::cout << func.result << func.elems << "\n";
  }
  catch (const std::exception& e)
  {
    std::cout << e.what() << "\n";
    return 1;
  }
}
