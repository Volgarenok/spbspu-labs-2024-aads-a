#include <fstream>
#include <iostream>
#include "inputDataset.hpp"

/*class DatasetSummarizer
{
 public:
  void operator()(const std::pair< int, std::string > & elem);
  std::ostream & operator<<(std::ostream & out);

 private:
  int key_sum;
  std::string value_sum;

  //check_flows
};*/

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
