#ifndef TREE_HPP
#define TREE_HPP

namespace nikitov
{
  template< class T, class Compare >
  class Tree
  {
  public:
    template< class... Args >
    Tree(Args&&... args);
    ~Tree() = default;

  private:
    T firstValue_;
    T secondValue_;
    Tree< T >* left_;
    Tree< T >* middle_;
    Tree< T >* right_;
    Tree< T >* parent_;
  };

  template< class T, class Compare >
  template< class... Args >
  Tree< T, Compare >::Tree(Args&&... args):
    firstValue_(std::forward< Args >(args)...),
    secondValue_(T()),
    left_(nullptr),
    middle_(nullptr),
    right_(nullptr),
    parent_(nullptr)
  {}
}
#endif
