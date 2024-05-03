#ifndef AVLTREE_HPP
#define AVLTREE_HPP

namespace chistyakov
{
  template< typename T, typename Comp = std::less< T > >
  class AVLTree
  {
    public:
    private:
      size_t size_;
      Node * node_;
  };
}

#endif
