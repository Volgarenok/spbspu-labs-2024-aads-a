#ifndef NODE_HPP
#define NODE_HPP
namespace strelyaev
{
  template< typename T >
  struct Node
  {
    Node(Node* left, Node* parent, Node* right, T value):
      value_(value),
      parent_(parent),
      right_(right),
      left_(left),
      height_(0)
    {}

    bool isRoot()
    {
      return (parent_ == nullptr);
    }

    bool isLeftChild()
    {
      return (parent_->left_ == this);
    }

    bool isRightChild()
    {
      return (parent_->right_ == this);
    }

    T value_;
    Node< T >* parent_;
    Node< T >* right_;
    Node< T >* left_;
    size_t height_;
  };
}
#endif
