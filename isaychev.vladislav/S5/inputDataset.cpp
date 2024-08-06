#include "inputDataset.hpp"
#include <istream>

void isaychev::inputDataset(std::istream & in, dataset_t & dataset)
{
  int key = 0;
  std::string value;
  while (!in.eof())
  {
    in >> key >> value;
    dataset[key] = value;
  }
}
