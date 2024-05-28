#include "inputdata.hpp"

void gladyshev::read_dictionaries(std::ifstream& in, mainDic& dictionaries)
{
  std::string dataset = "";
  std::string value = "";
  int key = 0;
  while (in >> dataset)
  {
    Tree< int, std::string > dict;
    if (in.get() == '\n')
    {
       dictionaries.insert(dataset, dict);
       continue;
    }
    while (in >> key >> value)
    {
      dict.insert(key, value);
      if (in.get() == '\n')
      {
        break;
      }
    }
    dictionaries.insert(dataset, dict);
  }
}
