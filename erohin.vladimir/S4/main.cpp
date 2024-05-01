#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <functional>
#include <stdexcept>
#include <limits>
#include "dictionary_command.hpp"
#include "input_output_collection.hpp"
#include "red_black_tree.hpp"

int main(int argc, char ** argv)
{
  using namespace erohin;

  {
    RedBlackTree< int, int > int_dict;
    int_dict.insert(std::make_pair(1, 10));
    int_dict.insert(std::make_pair(2, 20));
    int_dict.insert(std::make_pair(3, 30));
    int_dict.insert(std::make_pair(4, 40));
    int_dict.insert(std::make_pair(0, 00));
    int_dict.insert(std::make_pair(5, 50));
    for (auto iter: int_dict)
    {
      std::cout << std::endl << "//" << iter.first << "//" << std::endl;
    }
  }

  if (argc != 2)
  {
    std::cerr << "Wrong CLA number\n";
    return 1;
  }
  std::fstream file(argv[1]);
  collection context;
  inputCollection(file, context);
  file.close();
  using dict_func = std::function< void(std::istream &, std::ostream &) >;
  std::map< std::string, dict_func > command;
  {
    using namespace std::placeholders;
    command["print"] = std::bind(print, std::ref(context), _1, _2);
    command["complement"] = std::bind(complement, std::ref(context), _1, _2);
    command["intersect"] = std::bind(intersect, std::ref(context), _1, _2);
    command["union"] = std::bind(unite, std::ref(context), _1, _2);
  }
  std::string command_name;
  std::cin >> command_name;
  while (!std::cin.eof())
  {
    try
    {
      command.at(command_name)(std::cin, std::cout);
    }
    catch (const std::underflow_error &)
    {
      std::cout << "<EMPTY>\n";
    }
    catch (const std::exception & e)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::cin >> command_name;
  }
  return 0;
}
