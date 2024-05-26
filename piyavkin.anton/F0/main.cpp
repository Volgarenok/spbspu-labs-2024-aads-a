#include <iostream>
#include <functional>
#include <fstream>
#include "commands.hpp"

int main()
{
  using namespace piyavkin;
  dic_t dicts;
  Tree< std::string, std::function< void(std::istream&, const dic_t&) > > cmdsForOutput;
  cmdsForOutput["print"] = std::bind(print, std::placeholders::_1, std::ref(std::cout), std::placeholders::_2);
  Tree< std::string, std::function< iterator(std::istream&, dic_t&) > > cmdsForCreate;
  cmdsForCreate["addd"] = addDict;
  cmdsForCreate["chng"] = cmdChange;
  cmdsForCreate["mkd"] = makeDict;
  cmdsForCreate["intersect"] = intersect;
  cmdsForCreate["union"] = unionD;
  std::string name = "";
  while (std::cin >> name)
  {
    try
    {
      cmdsForCreate.at(name)(std::cin, dicts);
    }
    catch (const std::out_of_range&)
    {
      try
      {
        cmdsForOutput.at(name)(std::cin, dicts);
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