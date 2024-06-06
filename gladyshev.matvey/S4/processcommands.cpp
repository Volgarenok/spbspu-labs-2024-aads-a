#include "processcommands.hpp"

#include <functional>
#include <limits>

std::ostream& gladyshev::process_commands(std::istream& in, std::ostream& out, mainDic& findic)
{
  Tree < std::string, std::function < mainDic(const std::string&, const dic&, const dic&) > > cmds;
  Tree < std::string, std::function < void(const std::string&, const mainDic&) > > printCmds;
  cmds["complement"] = complement;
  cmds["intersect"] = intersect;
  cmds["union"] = union_dictionaries;
  printCmds["print"] = print_dictionaries;
  std::string command = "";
  std::string dataset = "";
  std::string name1 = "";
  std::string name2 = "";
  while (in >> command)
  {
    in >> dataset;
    try
    {
      printCmds.at(command)(dataset, findic);
    }
    catch (const std::out_of_range& e)
    {
      try
      {
        in >> name1 >> name2;
        dic supdic1 = findName(findic, name1);
        dic supdic2 = findName(findic, name2);
        mainDic temp = cmds.at(command)(dataset, supdic1, supdic2);
        for (const auto& pair: temp)
        {
          findic.insert(pair.first, pair.second);
        }
      }
      catch (const std::out_of_range& e)
      {
        out << "<INVALID COMMAND>\n";
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      }
    }
    catch (const std::overflow_error& e)
    {
      out << e.what() << "\n";
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return out;
}
