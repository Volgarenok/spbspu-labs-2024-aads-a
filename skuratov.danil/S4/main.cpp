#include <iostream>
#include <fstream>
#include <exception>
#include "AVLTree.hpp"

int main(int argc, char* argv[])
{
  using namespace skuratov;
  AVLTree< std::string, AVLTree< int, std::string > > dictionary;
  if (argc > 1)
  {
    std::ifstream infile(argv[1]);
    if (!infile)
    {
      std::cerr << "Error reading file" << '\n';
      return 1;
    }
    while (!infile.eof())
    {
      infile.clear();
      AVLTree< int, std::string > tempDic;
      std::string nameDic = {};
      std::cin >> nameDic;

      int keyNum = {};
      while (std::cin >> keyNum)
      {
        std::string value = {};
        std::cin >> value;
        tempDic.insert(keyNum, value);
      }
      dictionary.insert(nameDic, tempDic);
    }
  }

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      //wrote after implementing the commands
    }
    catch (const std::exception&)
    {
      std::cerr << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
