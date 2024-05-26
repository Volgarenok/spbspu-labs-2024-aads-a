#include <iostream>
#include <functional>

#include <calc/getInfix.hpp>
#include <tree/twoThreeTree.hpp>

#include "commands.hpp"

int main()
{
  using namespace zhalilov;
  using varModule = TwoThree< std::string, List< InfixToken > >;
  using modulesMap = TwoThree< std::string, varModule >;
  modulesMap modules;

  TwoThree< std::string, std::function< void(std::istream &, std::ostream &) > > сommands;

  using namespace std::placeholders;
  сommands["calc"] = std::bind(calc, std::cref(modules), std::ref(std::cout), _1, _2);
  сommands["modulesadd"] = std::bind(modulesadd, std::ref(modules), _1, _2);
  сommands["modulesvaradd"] = std::bind(modulesvarradd, std::ref(modules), _1, _2);

  while (!std::cin.eof())
  {
    std::string command;
    std::cin >> command;
    try
    {
      сommands.at(command)(std::cin, std::cout);
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what();
    }
  }
}
