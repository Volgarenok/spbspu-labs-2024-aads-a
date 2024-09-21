#ifndef CONSTITERATOR_HPP
#define CONSTITERATOR_HPP

namespace vojuck
{
template < typename T >
struct ConstIteratorList
{
  public:
    using this_t = ConstListIterator< T >;
    ConstIteratorList():
      node_(nullptr)
    {}
    ConstIteratorList(Node< T > * node):
      node_(node)
    {}
    ~ConstIteratorList() = default;

    ConstIteratorList(const this_t &) = default;
    ConstIteratorList(const IteratorList< T > & other):
      node_(other.node_)
    {}
    this_t & operator=(const this_t &) = default;
    this_t & operator++()
    {
      assert(node_ != nullptr);
      node_ = node_->next_;
      return *this;
    }
    this_t operator++(int)
    {
      assert(node_ != nullptr);
      this_t result(*this);
      ++(*this);
      return result;
    }
    const T & operator*() const
    {
      assert(node_ != nullptr);
      return node_->data_;
    }
    const T * operator->() const
    {
      assert(node_ != nullptr);
      return std::addressof(node_->data_);
    }

    bool operator==(const this_t & rhs) const
    {
      return node_ == rhs.node_;
    }
    bool operator!=(const this_t & rhs) const
    {
      return !(rhs == *this);
    }
  private:
    Node< T > * node_;

};

}


#endif
