#include "input.hpp"

namespace sivkov
{
  void inputDictionary(std::map < std::string, std::map< size_t, std::string > >& treeOfdic, std::istream& in)
  {
    while (!in.eof())
    {
      in.clear();
      std::string name = "";
      std::map< size_t, std::string > dictionary;
      size_t key = 0;
      in >> name;
      while (in >> key)
      {
        std::string word = "";
        in >> word;
        dictionary[key] = word;
      }
      treeOfdic[name] = dictionary;
    }
  }
}
