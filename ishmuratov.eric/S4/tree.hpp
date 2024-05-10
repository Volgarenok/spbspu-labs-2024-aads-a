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
      comp_(Compare()),
      size_(0)
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

    size_t size() noexcept
    {
      return size_;
    }

    bool empty() noexcept
    {
      return size_ == 0;
    }

    Value & at(const Key & key)
    {
      tnode * node = root_;
      while (node != nullptr)
      {
        if (comp_(key, node->data.first))
        {
          node = node->left;
        }
        else if (comp_(node->data.first, key))
        {
          node = node->right;
        }
        else
        {
          return node->data.second;
        }
      }
      throw std::runtime_error("Key wasn't found!");
    }

    Value operator[](const Key & key)
    {
      return at(key);
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
        size_ += 1;
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
    size_t size_;

    void place(Key k, Value v, tnode * curr)
    {
      if (comp_(k, curr->data.first))
      {
        if (curr->left == nullptr)
        {
          curr->left = new tnode(k, v);
          curr->left->parent = curr;
          size_ += 1;
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
          size_ += 1;
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
