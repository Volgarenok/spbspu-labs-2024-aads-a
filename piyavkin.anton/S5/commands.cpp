#include "commands.hpp"

void piyavkin::traverse_ascending(std::ostream& out, const Tree< int, std::string >& tree, KeySum& f)
{
  tree.traverse_lnr(f);
  out << f.getKey() << f.getVal();
}

void piyavkin::traverse_descending(std::ostream& out, const Tree< int, std::string >& tree, KeySum& f)
{
  tree.traverse_rnl(f);
  out << f.getKey() << f.getVal();
}

void piyavkin::traverse_breadth(std::ostream& out, const Tree< int, std::string >& tree, KeySum& f)
{
  tree.traverse_breadth(f);
  out << f.getKey() << f.getVal();
}
