#include <iostream>
#include <fstream>
#include <functional>
#include <limits>

#include "cmd.hpp"
#include "iodata.hpp"

#include "tree.hpp"

int main(int argc, char * argv[])
{
  if (argc != 2)
  {
    std::cerr << "Incorrect number of arguments!\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  using namespace ishmuratov;
  data_t data;
  input_dict(data, file);

  AVLTree< std::string, std::function< void(std::istream &, std::ostream &) > > cmds;
  {
    using namespace std::placeholders;
    cmds.push("print", std::bind(print, std::ref(data), _1, _2));
    cmds.push("complement", std::bind(complement, std::ref(data), _1));
    cmds.push("intersect", std::bind(intersect, std::ref(data), _1));
    cmds.push("union", std::bind(uniond, std::ref(data), _1));
//    cmds["print"] = std::bind(print, std::ref(data), _1, _2);
//    cmds["complement"] = std::bind(complement, std::ref(data), _1);
//    cmds["intersect"] = std::bind(intersect, std::ref(data), _1);
//    cmds["union"] = std::bind(uniond, std::ref(data), _1);
  }

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
    }
    catch (const std::out_of_range &)
    {
      std::cerr << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch (const std::runtime_error & e)
    {
      std::cerr << "<ERROR: " << e.what() << ">\n";
    }
  }
}
