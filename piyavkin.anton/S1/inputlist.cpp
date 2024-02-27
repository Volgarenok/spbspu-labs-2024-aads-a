#include "inputlist.hpp"
#include <cmath>

std::pair< std::string, piyavkin::List< unsigned int >* >* piyavkin::inputList(std::istream& in, size_t& size, size_t& max_size_list)
{
  size_t max_size = 0;
  std::string name = "";
  size_t capacity = 10;
  char symbol = 0;
  unsigned int val = 0;
  std::pair< std::string, List< unsigned int >* >* pairs = new std::pair< std::string, List< unsigned int >* >[capacity] {};
  while (in >> name)
  {
    if (size == capacity)
    {
      std::pair< std::string, List< unsigned int >* >* old_pairs = pairs;
      pairs = new std::pair< std::string, List< unsigned int >* >[capacity + 10] {};
      for (size_t j = 0; j < capacity; ++j)
      {
        pairs[j] = old_pairs[j];
      }
      delete[] old_pairs;
      capacity += 10;
    }
    List< unsigned int >* list = new List< unsigned int >;
    pairs[size].first = name;
    in >> std::noskipws;
    in >> symbol;
    while (symbol != '\n')
    {
      if (symbol == ' ')
      {
        in >> std::skipws;
        in >> val;
        if (!in)
        {
          delete list;
          delete[] pairs;
          throw std::out_of_range("This number is too huge");
        }
        in >> std::noskipws;
        list->push_back(val);
        ++max_size;
      }
      in >> symbol;
    }
    in >> std::skipws;
    pairs[size++].second = list;
    max_size_list = std::max(max_size, max_size_list);
    max_size = 0;
  }
  if (name == "")
  {
    delete[] pairs;
    throw std::logic_error("There was no input");
  }
  return pairs;
}
