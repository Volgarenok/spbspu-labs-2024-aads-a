#include <iostream>
#include <fstream>
#include <string>

#include "manageData.h"

using namespace stepanov;

int main(int argc, char* argv[])
{
  std::string strInput = "";
  manageExpression expression;
  Stack< long long > stackResult;

  if (argc == 1)
  {
  }
  else if (argc == 2)
  {
    std::ifstream fileName;
    fileName.open(argv[1]);
    if (!fileName.is_open())
    {
      std::cerr << "No such file in directory" << "\n";
      return 1;
    }
    fileName.close();
  }
  return 0;
}
