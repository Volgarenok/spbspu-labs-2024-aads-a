#ifndef TREE_HPP
#define TREE_HPP

#include "tree_node.hpp"
#include "tree_iterator.hpp"

namespace ishmuratov
{
  template< class Key, class Value, class Compare = less< Key > >
  class AVLTree
  {
    using tnode = detail::TNode< Key, Value >;
    using Iter = Iterator< Key, Value, Compare >;
  public:
    AVLTree():
      root_(nullptr),
      comp_(Compare())
    {}
    ~AVLTree() = default;

    tnode * min_elem(tnode * root)
    {
      if (root == nullptr || root->left == nullptr)
      {
        return root;
      }
      return min_elem(root->left);
    }

    Iter begin() noexcept
    {
      return Iter(min_elem(root_));
    }

    Iter end() noexcept
    {
      return Iter(nullptr);
    }

    long long get_height(tnode * node)
    {
      if (node == nullptr)
      {
        return 0;
      }
      return node->height;
    }

    long long get_balance(detail::TNode< Key, Value > * node)
    {
      if (node == nullptr)
      {
        return 0;
      }
      return get_height(node->left) - get_height(node->right);
    }

    void push(Key k, Value v)
    {
      if (root_ == nullptr)
      {
        root_ = new tnode(k, v);
        return;
      }
      else
      {
        place(k, v, root_);
      }
    }

    void print(std::ostream & output)
    {
      printUtil(root_, 0, output);
    }

    tnode * root()
    {
      return root_;
    }

  private:
    detail::TNode< Key, Value> * root_;
    Compare comp_;

    void place(Key k, Value v, tnode * curr)
    {
      if (comp_(k, curr->data.first))
      {
        if (curr->left == nullptr)
        {
          curr->left = new tnode(k, v);
          curr->left->parent = curr;
          return;
        }
        place(k, v, curr->left);
      }
      else if (comp_(curr->data.first, k))
      {
        if (curr->right == nullptr)
        {
          curr->right = new tnode(k, v);
          curr->right->parent = curr;
          return;
        }
        place(k, v, curr->right);
      }
    }

    void printUtil(tnode * root, int space, std::ostream & output)
    {
      if (root == nullptr)
        return;

      space += 5;

      printUtil(root->right, space, output);

      output << "\n";
      for (int i = 5; i < space; i++)
      {
        output << " ";
      }
      output << root->data.first << "\n";

      printUtil(root->left, space, output);
    }
  };
}

#endif
