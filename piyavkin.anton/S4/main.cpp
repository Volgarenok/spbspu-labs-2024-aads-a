#include <iostream>
#include <fstream>
#include "inputfile.hpp"
#include "commands.hpp"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "File entered incorrectly\n";
    return 1;
  }
  using namespace piyavkin;
  map_t map;
  std::ifstream in(argv[1]);
  if (!in.is_open())
  {
    std::cerr << "The file is not open\n";
    return 2;
  }
  inputFile(in, map);
  Tree< std::string, std::function< void(std::ostream&, const std::string&, const map_t&) > > cmdsForOutput;
  cmdsForOutput["print"] = print;
  Tree< std::string, std::function< void(map_t&, const std::string&, const std::string&, const std::string&) > > cmdsForCreate;
  cmdsForCreate["complement"] = complement;
  cmdsForCreate["union"] = unionF;
  cmdsForCreate["intersect"] = intersect;
  std::string name = "";
  std::string nameDataSet = "";
  while (std::cin >> name)
  {
    std::cin >> nameDataSet;
    try
    {
      cmdsForOutput.at(name)(std::cout, nameDataSet, map);
    }
    catch (const std::out_of_range&)
    {
      try
      {
        std::string rhsName = "";
        std::string lhsName = "";
        std::cin >> lhsName >> rhsName;
        cmdsForCreate.at(name)(map, nameDataSet, lhsName, rhsName);
      }
      catch (const std::out_of_range&)
      {
        std::cout << "<INVALID COMMAND>\n";
      }
      catch (const std::exception& e)
      {
        std::cerr << e.what() << '\n';
        return 1;
      }
    }
  }
}
