#include "commands.hpp"
#include <string>
#include <ostream>
#include "tree.hpp"
#include "key_sum.hpp"

namespace sakovskaia
{
  void input(Tree<int, std::string> & dictionary, std::istream & input)
  {
    while (input)
    {
      std::string word = "";
      int key = 0;
      while (input >> key)
      {
        input >> word;
        dictionary.push(key, word);
      }
    }
    if (!input.eof())
    {
      throw std::out_of_range("Error");
    }
  }

  void ascending(const Tree< int, std::string > & tree, KeySum & f, std::ostream & output)
  {
    KeySum answ = tree.traverseLnr(f);
    output << answ.key_ << answ.str_ << "\n";
  }

  void breadth(const Tree< int, std::string > & tree, KeySum & f, std::ostream & output)
  {
    KeySum answ = tree.traverseBreadth(f);
    output << answ.key_ << answ.str_ << "\n";
  }

  void descending(const Tree< int, std::string > & tree, KeySum & f, std::ostream & output)
  {
    KeySum answ = tree.traverseRnl(f);
    output << answ.key_ << answ.str_ << "\n";
  }
}
