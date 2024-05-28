#include <iostream>
#include <limits>
#include <functional>
#include "tree.hpp"
#include "bdlist.hpp"

#include "input.hpp"
#include "cmd.hpp"

int main()
{
  using namespace ishmuratov;
  dict_t dict;
//  input_dictionary(dict, std::cin);

  AVLTree< std::string, std::function< void(std::istream &, std::ostream &) > > cmds;
  {
    using namespace std::placeholders;
    cmds.insert(std::make_pair("createdict", std::bind(create_dict, std::ref(dict), _1)));
    cmds.insert(std::make_pair("deletedict", std::bind(delete_dict, std::ref(dict), _1)));
  }

  AVLTree< int, int > lol;
  lol.insert(std::make_pair(1, 0));

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
    }
    catch (const std::out_of_range &)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch (const std::underflow_error &)
    {
      std::cout << "<EMPTY>\n";
    }
    catch (const std::runtime_error & e)
    {
      std::cout << "<ERROR: " << e.what() << ">\n";
    }
  }
}
