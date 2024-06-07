#include "input_data.hpp"

void ishmuratov::input_data(AVLTree< int, std::string > & data, std::istream & input)
{
  int key = 0;
  std::string value;
  while (input >> key >> value)
  {
    data.insert(std::make_pair(key, value));
  }
  if (!input.eof())
  {
    input.clear();
    throw std::invalid_argument("Error while reading from file!");
  }
}
