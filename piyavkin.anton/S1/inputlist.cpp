#include "inputlist.hpp"
#include <cmath>

using pair_t = std::pair< std::string, piyavkin::List< unsigned long long >* >*;
void piyavkin::freeMemory(pair_t pairs, size_t size)
{
  for (size_t i = 0; i < size; ++i)
  {
    delete pairs[i].second;
  }
  delete[] pairs;
}
pair_t piyavkin::resize(pair_t old_pairs, size_t capacity)
{
  pair_t pairs = new std::pair< std::string, piyavkin::List< unsigned long long >* >[capacity + 10] {};
  for (size_t j = 0; j < capacity; ++j)
  {
    pairs[j] = old_pairs[j];
  }
  freeMemory(old_pairs, capacity);
  capacity += 10;
  return pairs;
}
pair_t piyavkin::inputList(std::istream& in, size_t& size, size_t& max_size_list)
{
  size_t max_size = 0;
  std::string name = "";
  size_t capacity = 0;
  char symbol = 0;
  unsigned long long val = 0;
  pair_t pairs = new std::pair< std::string, List< unsigned long long >* >[capacity] {};
  while (in >> name)
  {
    try
    {
      if (size == capacity)
      {
        pairs = resize(pairs, capacity);
      }
      List< unsigned long long >* list = new List< unsigned long long >;
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
            freeMemory(pairs, size + 1);
            throw std::bad_exception();
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
    catch(const std::bad_alloc& e)
    {
      freeMemory(pairs, size);
      throw;
    }
  }
  if (name == "")
  {
    delete[] pairs;
    throw std::logic_error("There was no input");
  }
  return pairs;
}
