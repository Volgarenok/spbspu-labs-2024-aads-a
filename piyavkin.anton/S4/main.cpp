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
  inputFile(in, map);
  Tree< std::string, std::function< void(std::ostream&, const std::string&, const map_t&) > > cmdsForOutput;
  cmdsForOutput["print"] = print;
  Tree< std::string, std::function< void(map_t&, const std::string&, const std::string&, const std::string&) > > cmdsForCreate;
  {
    using namespace std::placeholders;
    cmdsForCreate["complement"] = complement;
  }
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
        std::cin >> rhsName >> lhsName;
        cmdsForCreate.at(name)(map, nameDataSet, rhsName, lhsName);
      }
      catch (const std::out_of_range&)
      {
        std::cerr << "<INVALID COMMANDS>";
      }
      catch(const std::exception& e)
      {
        std::cerr << e.what() << '\n';
        return 1;
      }
    }
  }
}