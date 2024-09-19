#include "inputDataset.hpp"
#include <istream>

void isaychev::inputDataset(std::istream & in, dataset_t & dataset)
{
  int key = 0;
  std::string value;
  while (in >> key >> value)
  {
    dataset.insert({key, value});
  }
  if (!in.eof())
  {
    throw std::invalid_argument("incorrect arg");
  }
}
