#include <iostream>
//#include <limits>
//#include <fstream>
#include <functional>
#include "non_interactive_cmd.hpp"

int main(int argc, char * argv[])
{
  using namespace isaychev;
  if (argc > 3)
  {
    std::cerr << "too many clas'\n";
    return 1;
  }

  BSTree< std::string, FreqList > col;
  try
  {
    using cla_cmd_t = void(BSTree< std::string, FreqList > &);
    BSTree< std::string, std::function< cla_cmd_t > > args;
    args["--help"] = std::bind(print_help, std::ref(std::cout));
    args["--saved"] = load_saved;
    if (argc >= 2)
    {
      if (argc == 3)
      {
        args.at(argv[2])(col);
      }
      args.at(argv[1])(col);
    }
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    return 2;
  }

  std::cout << col.size() << "\n";
}
