#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include "tree_node.hpp"
#include "tree_iterator.hpp"

namespace ishmuratov
{
  template< class Key, class Value, class Compare = less< Key > >
  class AVLTree
  {
    using tnode = detail::TNode< Key, Value >;
    using Iter = Iterator< Key, Value, Compare >;
    using ConstIter = ConstIterator< Key, Value, Compare >;
  public:
    AVLTree():
      root_(nullptr),
      size_(0)
    {}

    AVLTree(const AVLTree & other):
      AVLTree(other.cbegin(), other.cend())
    {}

    AVLTree(ConstIter begin, ConstIter end):
      root_(nullptr),
      size_(0)
    {
      try
      {
        while (begin != end)
        {
          push(begin->first, begin->second);
          ++begin;
        }
      }
      catch(...)
      {
        clear();
      }
    }

    AVLTree(AVLTree && other) noexcept:
      root_(other.root_),
      size_(other.size_)
    {
      other.root_ = nullptr;
      other.size_ = 0;
    }

    AVLTree & operator=(const AVLTree & other)
    {
      if (this != std::addressof(other))
      {
        AVLTree temp(other);
        swap(temp);
      }
      return *this;
    }

    AVLTree & operator=(AVLTree && other) noexcept
    {
      if (this != std::addressof(other))
      {
        clear();
        swap(other);
      }
      return *this;
    }

    ~AVLTree()
    {
      clear();
    }

    Iter begin() noexcept
    {
      return Iter(min_elem(root_));
    }

    Iter end() noexcept
    {
      return Iter(nullptr);
    }

    ConstIter cbegin() const noexcept
    {
      return ConstIter(min_elem(root_));
    }

    ConstIter cend() const noexcept
    {
      return ConstIter(nullptr);
    }

    size_t size() const noexcept
    {
      return size_;
    }

    bool empty() const noexcept
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
      throw std::out_of_range("Key wasn't found!");
    }

    Value operator[](const Key & key)
    {
      return at(key);
    }

    void clear()
    {
      delete_node(root_);
      root_ = nullptr;
      size_ = 0;
    }

    void swap(AVLTree & other)
    {
      std::swap(other.root_, root_);
      std::swap(other.comp_, comp_);
      std::swap(other.size_, size_);
    }

    Iter find(const Key & key)
    {
      tnode * node = root_;
      while (node)
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
          return Iter(node);
        }
      }
      return end();
    }

    ConstIter find(const Key & key) const
    {
      tnode * node = root_;
      while (node)
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
          return ConstIter(node);
        }
      }
      return cend();
    }

    void push(const Key & k, const Value & v)
    {
      if (root_ == nullptr)
      {
        root_ = new tnode(k, v);
        size_ += 1;
      }
      else
      {
        root_ = place(k, v, root_);
      }
    }

    void print(std::ostream & output)
    {
      print_impl(root_, 0, output);
    }

  private:
    detail::TNode< Key, Value> * root_;
    Compare comp_;
    size_t size_;

    int get_height(tnode * node)
    {
      if (node == nullptr)
      {
        return 0;
      }
      return node->height;
    }

    tnode * min_elem(tnode * root) const
    {
      if (root == nullptr || root->left == nullptr)
      {
        return root;
      }
      return min_elem(root->left);
    }

    tnode * place(const Key & key, const Value & value, tnode * node)
    {
      if (comp_(key, node->data.first))
      {
        if (node->left == nullptr)
        {
          node->left = new tnode(key, value);
          node->left->parent = node;
          size_ += 1;
        }
        node->left = place(key, value, node->left);
        if (get_height(node->left) - get_height(node->right) == 2)
        {
          if (comp_(key, node->left->data.first))
          {
            node = rotate_right(node);
          }
          else
          {
            node = rotate_double_right(node);
          }
        }
      }
      else if (comp_(node->data.first, key))
      {
        if (node->right == nullptr)
        {
          node->right = new tnode(key, value);
          node->right->parent = node;
          size_ += 1;
        }
        node->right = place(key, value, node->right);
        if (get_height(node->right) - get_height(node->left) == 2)
        {
          if (comp_(node->right->data.first, key))
          {
            node = rotate_left(node);
          }
          else
          {
            node = rotate_double_left(node);
          }
        }
      }
      else
      {
        node->data.second = value;
      }
      node->height = std::max(get_height(node->left), get_height(node->right)) + 1;
      return node;
    }

    void delete_node(tnode * node)
    {
      if (node == nullptr)
      {
        return;
      }
      delete_node(node->left);
      delete_node(node->right);
      delete node;
    }

    tnode * rotate_left(tnode * node)
    {
      tnode * rot_node = node->right;
      node->right = rot_node->left;
      rot_node->left = node;

      rot_node->parent = node->parent;
      node->parent = rot_node;

      node->height = std::max(get_height(node->left), get_height(node->right)) + 1;
      rot_node->height = std::max(get_height(node->right), node->height) + 1 ;
      return rot_node;
    }

    tnode * rotate_right(tnode * node)
    {
      tnode * rot_node = node->left;
      node->left = rot_node->right;
      rot_node->right = node;

      rot_node->parent = node->parent;
      node->parent = rot_node;

      node->height = std::max(get_height(node->left), get_height(node->right)) + 1;
      rot_node->height = std::max(get_height(rot_node->left), node->height) + 1;
      return rot_node;
    }

    tnode * rotate_double_left(tnode * node)
    {
      node->right = rotate_right(node->right);
      return rotate_left(node);
    }

    tnode * rotate_double_right(tnode * node)
    {
      node->left = rotate_left(node->left);
      return rotate_right(node);
    }

    void print_impl(tnode * root, int space, std::ostream & output)
    {
      if (root == nullptr)
        return;

      space += 5;

      print_impl(root->right, space, output);

      output << "\n";
      for (int i = 5; i < space; i++)
      {
        output << " ";
      }
      output << root->data.first << "\n";

      print_impl(root->left, space, output);
    }
  };
}

#endif
