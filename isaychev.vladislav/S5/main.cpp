#include <fstream>
#include <iostream>
#include "inputDataset.hpp"
#include "datasetSummarizer.hpp"

int main(int argc, char * argv[])
{
  using namespace isaychev;
  BSTree< int, std::string > dataset;
  if (argc == 3)
  {
    std::fstream in(argv[2]);
    inputDataset(in, dataset);
  }
  else
  {
    std::cerr << "bad launch\n";
    return 1;
  }

}
