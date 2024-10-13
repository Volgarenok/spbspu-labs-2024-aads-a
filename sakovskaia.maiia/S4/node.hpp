#ifndef NODE_HPP
#define NODE_HPP
#include <utility>

namespace sakovskaia
{
  namespace detail
  {
    template < typename Key, typename Value >
    struct Node
    {
      Node * left;
      Node * right;
      Node * parent;
      std::pair< Key, Value > data;

      Node() :
        left(nullptr),
        right(nullptr),
        parent(nullptr),
        data(std::pair< Key, Value >())
      {}

      Node(const Key & key, const Value & value) :
        left(nullptr),
        right(nullptr),
        parent(nullptr),
        data(std::make_pair(key, value))
      {}

      Node< Key, Value > * rotate_right(Node< Key, Value > * root)
      {
        if (root == nullptr || root->left == nullptr)
        {
          return root;
        }
        Node< Key, Value > * new_root = root->left;
        root->left = new_root->right;
        if (new_root->right != nullptr)
        {
          new_root->right->parent = root;
        }
        new_root->right = root;
        new_root->parent = root->parent;
        root->parent = new_root;
        return new_root;
      }

      Node< Key, Value > * rotate_left(Node< Key, Value > * root)
      {
        if (root == nullptr || root->right == nullptr)
        {
          return root;
        }
        Node< Key, Value > * new_root = root->right;
        root->right = new_root->left;
        if (new_root->left != nullptr)
        {
          new_root->left->parent = root;
        }
        new_root->left = root;
        new_root->parent = root->parent;
        root->parent = new_root;
        return new_root;
      }
    };
  }
}

#endif
