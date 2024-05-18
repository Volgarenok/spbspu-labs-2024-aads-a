#include "processcommands.hpp"

#include <functional>
#include <limits>

std::ostream& gladyshev::process_commands(std::istream& in, std::ostream& out, mainDic& findic)
{
  Tree < std::string, std::function < mainDic(const std::string&, const dic&, const dic&) > > cmds;
  cmds["complement"] = complement;
  cmds["intersect"] = intersect;
  cmds["union"] = union_dictionaries;
  std::string command = "";
  std::string dataset = "";
  std::string name1 = "";
  std::string name2 = "";
  std::string name3 = "";
  while (in >> command)
  {
    try
    {
      if (command == "print")
      {
        print_dictionaries(dataset, findic);
      }
      else
      {
        in >> name1 >> name2 >> name3;
        dic supdic1 = findName(findic, name2);
        dic supdic2 = findName(findic, name3);
        mainDic temp = cmds.at(command)(name1, supdic1, supdic2);
        for (const auto& pair: temp)
        {
          findic.insert(pair.first, pair.second);
        }
      }
    }
    catch (const std::out_of_range&)
    {
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch (const std::overflow_error& e)
    {
      std::cout << e.what() << "\n";
    }
  }
  return out;
}
