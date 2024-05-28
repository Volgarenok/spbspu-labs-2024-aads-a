#include "inputdata.hpp"
#include "processcommands.hpp"
#include "commands.hpp"

int main(int argc, char* argv[])
{
  using namespace gladyshev;
  mainDic dictionaries;
  if (argc == 2)
  {
    std::ifstream file(argv[1]);
    read_dictionaries(file, dictionaries);
  }
  else
  {
    std::cerr << "No such file\n";
    return 1;
  }
  process_commands(std::cin, std::cout, dictionaries);
}
