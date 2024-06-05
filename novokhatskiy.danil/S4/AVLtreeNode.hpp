#ifndef AVL_TREE_NODE_HPP
#define AVL_TREE_NODE_HPP

#include <utility>

namespace novokhatskiy
{
  namespace detail
  {
    template < class Key, class Value >
    struct NodeTree
    {
      using val_type = std::pair< Key, Value >;
      val_type value;
      int height;
      NodeTree* left;
      NodeTree* right;
      NodeTree* parent;

      NodeTree():
        value(),
        height(0),
        left(nullptr),
        right(nullptr),
        parent(nullptr)
      {}

      explicit NodeTree(const val_type& val):
        value(val),
        height(0),
        left(nullptr),
        right(nullptr),
        parent(nullptr)
      {}

      NodeTree(const val_type& val, NodeTree* node)
      {
        value = val;
        height = 0;
        parent = node;
        left = nullptr;
        right = nullptr;
      }

      NodeTree(const NodeTree& other):
        value(other.value),
        height(other.height),
        left(other.left),
        right(other.right),
        parent(other.parent)
      {}

      NodeTree(NodeTree&& other):
        value(std::move(other.value)),
        left(other.left),
        right(other.right),
        parent(other.parent)
      {
        other.height = 0;
        other.left = nullptr;
        other.right = nullptr;
        other.parent = nullptr;
      }

      int getHeight(NodeTree* root)
      {
        if (!root)
        {
          return -1;
        }
        else
        {
          int lheight = getHeight(root->left);
          int rheight = getHeight(root->right);
          if (lheight > rheight)
          {
            return lheight + 1;
          }
          else
          {
            return rheight + 1;
          }
        }
      }

      void freeNodes(NodeTree* root)
      {
        if (!root)
        {
          return;
        }
        NodeTree* curr = root;
        while (root->left || root->right)
        {
          if (curr->left)
          {
            curr = curr->left;
            continue;
          }
          if (curr->right)
          {
            curr = curr->right;
            continue;
          }
          curr = curr->parent;
          if (!curr->left->left && curr->left && !curr->left->right)
          {
            delete curr->left;
            curr->left = nullptr;
          }
          if (curr->right && !curr->right->right && !curr->right->left)
          {
            delete curr->right;
            curr->right = nullptr;
          }
        }
        root = nullptr;
      }
    };
  }
}

#endif
