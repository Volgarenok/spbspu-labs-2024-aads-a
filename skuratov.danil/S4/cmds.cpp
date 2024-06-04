#include "cmds.hpp"

void skuratov::isPrint(std::istream& in, AVLTree< std::string, AVLTree< int, std::string > >& dictionary, std::ostream& out)
{
  std::string name = {};
  in >> name;
  try
  {
    AVLTree< int, std::string > dic = dictionary.at(name);
    if (dic.empty())
    {
      out << "<EMPTY>" << '\n';
    }
    else
    {
      out << name;
      for (auto key = dic.cbegin(); key != dic.cend(); ++key)
      {
        out << " " << key->first << " " << key->second;
      }
      out << "\n";
    }
  }
  catch (std::out_of_range&)
  {
    out << "<DICTIONARY NOT FOUND>" << '\n';
  }
}

void skuratov::isComplement(std::istream&, AVLTree< std::string, AVLTree< int, std::string > >&)
{}

void skuratov::isIntersect(std::istream&, AVLTree< std::string, AVLTree< int, std::string > >&)
{}

void skuratov::isUnion(std::istream&, AVLTree< std::string, AVLTree< int, std::string > >&)
{}
