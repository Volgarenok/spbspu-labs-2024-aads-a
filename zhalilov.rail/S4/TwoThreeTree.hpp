#ifndef TWOTHREETREE_HPP
#define TWOTHREETREE_HPP

#include <functional>

#include "const_iterator.hpp"
#include "iterator.hpp"
#include "node.hpp"

namespace zhalilov
{
  template < class Key, class T, class Compare = std::less < Key > >
  class TwoThree
  {
  public:
    using MapPair = std::pair < Key, T >;
    using iterator = TwoThreeIterator < MapPair >;
    using const_iterator = ConstTwoThreeIterator < MapPair >;

    TwoThree();

    T &at(const Key &);
    const T &at(const Key &) const;
    T &operator[](const Key &);
    T &operator[](Key &&);

    bool empty();
    size_t size();

    void clear();
    void swap();

    iterator find(const Key &);
    const_iterator find(const Key &) const;

  private:
    using Node = detail::Node < MapPair >;
    Node *head_;
    size_t size_;

    void doInsert(const Key &, const T &);
    Node *createTwoNode(Node *, const MapPair &);
    Node *createThreeNode(Node *, const MapPair &, const MapPair &);
  };

  template < class Key, class T, class Compare >
  TwoThree < Key, T, Compare >::TwoThree() :
    head_(nullptr), size_(0)
  {}

  template < class Key, class T, class Compare >
  void TwoThree < Key, T, Compare >::doInsert(const Key &key, const T &value)
  {
    MapPair newPair = std::make_pair(key, value);
    if (empty())
    {
      head_ = createTwoNode(nullptr, MapPair());
      Node newNode = createTwoNode(head_, newPair);
      head_->childs[0] = newNode;
    }
  }

  template < class Key, class T, class Compare >
  typename TwoThree < Key, T, Compare >::Node *TwoThree < Key, T, Compare >::createTwoNode(Node *parent, const MapPair &pair)
  {
    return new Node{ parent, { nullptr, nullptr, nullptr }, { pair, pair }, detail::NodeType::Two };
  }

  template < class Key, class T, class Compare >
  typename TwoThree < Key, T, Compare >::Node *TwoThree < Key, T, Compare >::createThreeNode(Node *parent, const MapPair &pair1, const MapPair &pair2)
  {
    return new Node{ parent, { nullptr, nullptr, nullptr }, { pair1, pair2 }, detail::NodeType::Three };
  }
} // namespace zhalilov

#endif
