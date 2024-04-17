#ifndef MAP_HPP
#define MAP_HPP
#include<memory>

template<size_t node_sz = 2,  typename T, class Comparator >
class Map
{
  struct Node;
  using val_alloc_traits = std::allocator_traits< allocator< T > >;
  using node_alloc_traits = std::allocator_traits< allocator< Node > >;
  using childs_alloc_traits = std::allocator_traits< allocator< Node* > >;
  const size_t vals_nmb = node_sz;
  const size_t childs_nmb = node_sz + 1;
  Node* root;
  size_t size_;
  std::allocator<T> vals_alloc;
  std::allocator< Node > nodes_alloc;
  std::allocator< Node* > childs_alloc;
  struct Node
  {
    size_t size_;
    T* vals_;
    Node** childs_;

    Node(size_t sz):
      size_(sz),
      vals_(val_alloc_traits::allocate(vals_alloc, vals_nmb)),
      childs_(childs_alloc_traits::allocate(childs_alloc, childs_nmb))
    {

    }
    Node(const Node& other):
      size_(other.size_),
      vals_(val_alloc_traits::allocate(vals_alloc, vals_nmb)),
      childs_(childs_alloc_traits::allocate(childs_alloc, childs_nmb))
    {
      size_t i = 0;
      size_t j = 0;
      try
      {
        for (; i < size_; ++i)
        {
          val_alloc_traits::construct(vals_alloc, vals_ + i, other.vals_[i]);
        }
      }
      catch (...)
      {
        for (size_t k = 0; k < i; ++k)
        {
          val_alloc_traits::destruct(vals_alloc, vals_ + k);
        }
        val_alloc_traits::deallocate(vals_alloc, vals_);
        for (size_t k = 0; k < i; ++k)
        {
          val_alloc_traits::destruct(vals_alloc, vals_ + k);
        }
      }
    }
  };

  Map():
    root(nullptr),
    size_(0),
    vals_alloc(),
    nodes_alloc(),
    childs_alloc()
  {}
  Map(Map&& other):
    root(other.root),
    size_(other.size_),
    vals_alloc(),
    nodes_alloc(),
    childs_alloc()
  {
    other.root = nullptr;
    other.size_ = 0;
  }
};

#endif
