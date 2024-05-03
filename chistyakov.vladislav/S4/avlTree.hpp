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

      AVLTree(AVLTree && tmp)
        size_(tmp.size_),
        root_(tmp.root_),
        comp_(tmp.comp_)
      {
        tmp.size_ = 0;
        tmp.root_ = nullptr;
      }

    private:
      size_t size_;
      Node * root_;
      Comp comp_;
  };
}

#endif
