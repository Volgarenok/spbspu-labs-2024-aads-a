#ifndef MAP_HPP
#define MAP_HPP
#include<memory>

template<size_t node_sz = 2,  typename T, class Comparator >
class Map
{
  struct Node
  {
    T vals[vals_nmb];
    Node* childs[kindergarten_sz];
  };

  using val_alloc_traits = std::allocator_traits< allocator< T > >;
  using node_alloc_traits = std::allocator_traits< allocator< Node* > >;
  const size_t vals_nmb = node_sz;
  const size_t kindergarten_sz = node_sz + 1;
  Node* root;
  size_t size_;
  std::allocator<T> data_alloc;
  std::allocator< Node > data_alloc;
  std::allocator< Node* > childs_alloc;


};

#endif
