#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include "TreeNode.hpp"
#include "TreeIterator.hpp"
#include "TreeConstIterator.hpp"

namespace vyzhanov
{
  template < typename Key, typename Value, typename Compare = std::less< Key > >
  class AVLTree
  {
    using iterator = TreeIterator< Key, Value, Comparator >;
    using citerator = TreeConstIterator< Key, Value, Comparator >;
    using TreeNode = detail::TreeNode< Key, Value >;
    using pair = std::pair< Key, Value >;
  public:
    AVLTree();
    ~AVLTree();

    iterator begin() noexcept;
    citerator cbegin() noexcept;
    iterator end() noexcept;
    citerator cend() noexcept;
    iterator find(const Key&);
    citerator find(const Key&) const;

    size_t capacity() const noexcept;
    Value operator[](const Key&);
    bool empty() const noexcept;
    void clear();
    void swap(AVLTree&) noexcept;

    void erase(const Key&);
    void erase(citerator begin, citerator end);
    void insert(const pair&);
    void insert(citerator begin, citerator end);
    std::pair< Iter, Iter > equal_range(const Key&);
    size_t count(const Key&) const;

    iterator upper_bound(const Key&);
    citerator lower_bound(const Key&);
  };
}

#endif
