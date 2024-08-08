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

  DatasetSummarizer f = dataset.traverse_breadth(DatasetSummarizer());
/*  for (auto i = dataset.cbegin(); i != dataset.cend(); ++i)
  {
    f(*i);
  }*/

  std::cout << f.get_keysum() << f.get_valsum() << "\n";
}
