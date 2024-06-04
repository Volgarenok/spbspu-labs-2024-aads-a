#include "cmds.hpp"

void skuratov::isPrint(std::istream& in, AVLTree< std::string, AVLTree< int, std::string > >& dictionary, std::ostream& out)
{
  std::string name;
  in >> name;

  try
  {
    const AVLTree< int, std::string >& dic = dictionary.at(name);
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
      out << '\n';
    }
  }
  catch (std::out_of_range&)
  {
    out << "<KEY NOT FOUND>" << '\n';
  }
}

void skuratov::isComplement(std::istream& in, AVLTree< std::string, AVLTree< int, std::string > >& dictionary)
{}

void skuratov::isIntersect(std::istream& in, AVLTree< std::string, AVLTree< int, std::string > >& dictionary)
{}

void skuratov::isUnion(std::istream& in, AVLTree< std::string, AVLTree< int, std::string > >& dictionary)
{}
