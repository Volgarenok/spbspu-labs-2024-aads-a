#include <fstream>
#include <limits>
#include "cmds.hpp"

int main(int argc, char* argv[])
{
  using namespace skuratov;
  UBST< std::string, UBST< int, std::string > > dictionary;
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
      UBST< int, std::string > tempDic;
      std::string nameDic = {};
      infile >> nameDic;

      int keyNum = {};
      while (infile >> keyNum)
      {
        std::string value = {};
        infile >> value;
        tempDic.insert(keyNum, value);
      }
      dictionary.insert(nameDic, tempDic);
    }
  }

  UBST< std::string, std::function< void(std::istream&, UBST< std::string, UBST< int, std::string > >&) > > cmds;
  {
    using namespace std::placeholders;
    cmds["print"] = std::bind(isPrint, _1, _2, std::ref(std::cout));
    cmds["complement"] = std::bind(isComplement, _1, _2);
    cmds["intersect"] = std::bind(isIntersect, _1, _2);
    cmds["union"] = std::bind(isUnion, _1, _2);
  }

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, dictionary);
    }
    catch (const std::exception&)
    {
      std::cerr << "<INVALID COMMAND>" << '\n';
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
  return 0;
}
