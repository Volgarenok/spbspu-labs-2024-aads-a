#ifndef TREE_HPP
#define TREE_HPP

namespace nikitov
{
  template< class T >
  class Tree
  {
  private:
    T firstValue_;
    T secondValue_;
    Tree< T >* left_;
    Tree< T >* middle_;
    Tree< T >* right_;
    Tree< T >* parent_;
  };
}
#endif
