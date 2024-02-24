#include "inputlist.hpp"

std::pair< std::string, piyavkin::List< unsigned int >* >* piyavkin::inputList(std::istream& in)
{
  std::string str = "";
  std::string name = "";
  size_t capacity = 10;
  std::pair< std::string, List< unsigned int >* >* pairs = new std::pair< std::string, List< unsigned int >* >[capacity] {};
  size_t i = 0;
  while (in >> name)
  {
    if (i == capacity)
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
    pairs[i].first = name;
    std::getline(in, str);
    str.erase(0, 1);
    while (str != "")
    {
      if (str.find_first_not_of(' '))
      {
        std::string str2 = str.substr(0, str.find(' '));
        unsigned int val = std::stoul(str2);
        list->push_back(val);
        str.erase(0, str.find(' ') + 1);
      }
      else
      {
        unsigned int val = std::stoul(str);
        list->push_back(val);
        str = "";
      }
    }
    pairs[i++].second = list;
  }
  return pairs;
}
