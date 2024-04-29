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
  {
    using namespace std::placeholders;
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
    catch(const std::out_of_range& e)
    {
      std::cerr << "<INVALID COMMANDS>" << '\n';
    }
  }
}