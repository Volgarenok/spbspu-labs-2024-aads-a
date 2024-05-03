#ifndef AVLTREE_HPP
#define AVLTREE_HPP

namespace chistyakov
{
  template< typename T, typename Comp = std::less< T > >
  class AVLTree
  {
    public:
      AVLTree():
        size_(0),
        root_(nullptr),
        comp_(Comp)
      {}

    private:
      size_t size_;
      Node * root_;
      Comp comp_;
  };
}

#endif
