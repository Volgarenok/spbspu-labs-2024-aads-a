#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include "tree_node.hpp"
#include "tree_iterator.hpp"
#include <queue.hpp>
#include <stack.hpp>

namespace ishmuratov
{
  template< class Key, class Value, class Compare = std::less< Key > >
  class AVLTree
  {
    using tnode = detail::TNode< Key, Value >;
    using Iter = TreeIterator< Key, Value, Compare >;
    using ConstIter = ConstTreeIterator< Key, Value, Compare >;
  public:
    AVLTree():
      root_(nullptr),
      comp_(new Compare()),
      size_(0)
    {}

    AVLTree(const AVLTree & other):
      AVLTree(other.cbegin(), other.cend())
    {}

    AVLTree(std::initializer_list< std::pair< Key, Value > > init_list):
      AVLTree(init_list.begin(), init_list.end())
    {}

    AVLTree(ConstIter begin, ConstIter end):
      root_(nullptr),
      comp_(new Compare()),
      size_(0)
    {
      try
      {
        while (begin != end)
        {
          insert(std::make_pair(begin->first, begin->second));
          ++begin;
        }
      }
      catch (...)
      {
        clear();
        throw;
      }
    }

    AVLTree(AVLTree && other) noexcept:
      root_(other.root_),
      comp_(other.comp_),
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
      delete comp_;
    }

    Iter begin() noexcept
    {
      return Iter(min_elem(root_));
    }

    Iter rbegin() noexcept
    {
      return Iter(max_elem(root_));
    }

    Iter end() noexcept
    {
      return Iter(nullptr);
    }

    ConstIter cbegin() const noexcept
    {
      return ConstIter(min_elem(root_));
    }

    ConstIter crbegin() const noexcept
    {
      return ConstIter(max_elem(root_));
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
      tnode * node = get(root_, key);
      if (node == nullptr)
      {
        throw std::out_of_range("Key wasn't found!");
      }
      else
      {
        return node->data.second;
      }
    }

    const Value & at(const Key & key) const
    {
      tnode * node = get(root_, key);
      if (node == nullptr)
      {
        throw std::out_of_range("Key wasn't found!");
      }
      else
      {
        return node->data.second;
      }
    }

    Value operator[](const Key & key)
    {
      auto nodes = insert_impl(std::make_pair(key, Value()), root_, false);
      return nodes.second->data.second;
    }

    void clear()
    {
      delete_node(root_);
      root_ = nullptr;
      size_ = 0;
    }

    void swap(AVLTree & other)
    {
      std::swap(root_, other.root_);
      std::swap(comp_, other.comp_);
      std::swap(size_, other.size_);
    }

    Iter find(const Key & key)
    {
      tnode * node = root_;
      while (node)
      {
        if ((*comp_)(key, node->data.first))
        {
          node = node->left;
        }
        else if ((*comp_)(node->data.first, key))
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
        if ((*comp_)(key, node->data.first))
        {
          node = node->left;
        }
        else if ((*comp_)(node->data.first, key))
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

    void insert(const std::pair< Key, Value > & pair)
    {
      if (root_ == nullptr)
      {
        root_ = new tnode(pair.first, pair.second);
        size_ += 1;
      }
      else
      {
        auto nodes = insert_impl(pair, root_, true);
        root_ = nodes.first;
      }
    }

    void insert(ConstIter begin, ConstIter end)
    {
      while (begin != end)
      {
        insert(*begin);
        ++begin;
      }
    }

    void erase(const Key & k)
    {
      root_ = erase_impl(k, root_);
    }

    void erase(ConstIter begin, ConstIter end)
    {
      while (begin != end)
      {
        erase(begin->first);
        ++begin;
      }
    }

    size_t count(const Key & k) const
    {
      size_t count = 0;
      for (auto node = cbegin(); node != cend(); ++node)
      {
        if (!(*comp_)(k, node->first) && !((*comp_)(node->first, k)))
        {
          ++count;
        }
      }
      return count;
    }

    Iter lower_bound(const Key & k)
    {
      for (auto node = begin(); node != end(); ++node)
      {
        if (!(*comp_)(node->first, k))
        {
          return node;
        }
      }
      return end();
    }

    Iter upper_bound(const Key & k)
    {
      for (auto node = begin(); node != end(); ++node)
      {
        if ((*comp_)(k, node->first))
        {
          return node;
        }
      }
      return end();
    }

    std::pair< Iter, Iter > equal_range(const Key & k)
    {
      return std::make_pair(lower_bound(k), upper_bound(k));
    }

    template< class F >
    F traverse_lnr(F f) const
    {
      if (empty())
      {
        throw std::logic_error("<EMPTY>");
      }
      Stack< tnode * > stack;
      tnode * temp = root_;
      while (!stack.empty() || temp != nullptr)
      {
        while (temp != nullptr)
        {
          stack.push(temp);
          temp = temp->left;
        }
        temp = stack.top();
        f(temp->data);
        stack.pop();
        temp = temp->right;
      }
      return f;
    }

    template< class F >
    F traverse_rnl(F f) const
    {
      if (empty())
      {
        throw std::logic_error("<EMPTY>");
      }
      Stack< tnode * > stack;
      tnode * temp = root_;
      while (!stack.empty() || temp != nullptr)
      {
        while (temp != nullptr)
        {
          stack.push(temp);
          temp = temp->right;
        }
        temp = stack.top();
        f(temp->data);
        stack.pop();
        temp = temp->left;
      }
      return f;
    }

    template< class F >
    F traverse_breadth(F f) const
    {
      if (empty())
      {
        throw std::logic_error("<EMPTY>");
      }
      Queue< tnode * > queue;
      queue.push(root_);
      while (!queue.empty())
      {
        const tnode * temp = queue.back();
        f(temp->data);
        queue.pop();
        if (temp->left)
        {
          queue.push(temp->left);
        }
        if (temp->right)
        {
          queue.push(temp->right);
        }
      }
      return f;
    }

  private:
    detail::TNode< Key, Value> * root_;
    Compare * comp_;
    size_t size_;

    int get_height(tnode * node)
    {
      if (node == nullptr)
      {
        return 0;
      }
      return node->height;
    }

    tnode * get(tnode * node, const Key & key) const
    {
      node = root_;
      while (node != nullptr)
      {
        if ((*comp_)(key, node->data.first))
        {
          node = node->left;
        }
        else if ((*comp_)(node->data.first, key))
        {
          node = node->right;
        }
        else
        {
          return node;
        }
      }
      return nullptr;
    }

    tnode * min_elem(tnode * root) const
    {
      if (root == nullptr || root->left == nullptr)
      {
        return root;
      }
      return min_elem(root->left);
    }

    tnode * max_elem(tnode * root) const
    {
      if (root == nullptr || root->right == nullptr)
      {
        return root;
      }
      return max_elem(root->right);
    }

    std::pair< tnode *, tnode * > insert_impl(const std::pair< Key, Value > & pair, tnode * node, bool rewrite)
    {
      tnode * inserted = nullptr;
      if ((*comp_)(pair.first, node->data.first))
      {
        if (node->left == nullptr)
        {
          node->left = new tnode(pair.first, pair.second);
          inserted = node->left;
          node->left->parent = node;
          size_ += 1;
        }
        else
        {
          auto node_pair = insert_impl(pair, node->left, rewrite);
          node->left = node_pair.first;
          inserted = node_pair.second;
        }
      }
      else if ((*comp_)(node->data.first, pair.first))
      {
        if (node->right == nullptr)
        {
          node->right = new tnode(pair.first, pair.second);
          inserted = node->right;
          node->right->parent = node;
          size_ += 1;
        }
        else
        {
          auto node_pair = insert_impl(pair, node->right, rewrite);
          node->right = node_pair.first;
          inserted = node_pair.second;
        }
      }
      else
      {
        if (rewrite)
        {
          node->data.second = pair.second;
        }
        inserted = node;
      }

      node->height = std::max(get_height(node->left), get_height(node->right)) + 1;
      return std::make_pair(balance(pair.first, node), inserted);
    }

    tnode * erase_impl(const Key & k, tnode * node)
    {
      tnode * temp;
      if (node == nullptr)
      {
        return node;
      }
      if ((*comp_)(k, node->data.first))
      {
        node->left = erase_impl(k, node->left);
      }
      else if ((*comp_)(node->data.first, k))
      {
        node->right = erase_impl(k, node->right);
      }
      else
      {
        if ((node->left == nullptr) || (node->right == nullptr))
        {
          if (node->left)
          {
            temp = node->left;
          }
          else
          {
            temp = node->right;
          }
          delete node;
          size_ -= 1;
          return temp;
        }
        else
        {
          temp = min_elem(node->right);
          node->data = temp->data;
          node->right = erase_impl(node->data.first, node->right);
        }
      }

      node->height = std::max(get_height(node->left), get_height(node->right)) + 1;
      return balance(k, node);
    }

    tnode * balance(const Key k, tnode * node)
    {
      if (get_height(node->left) - get_height(node->right) == 2)
      {
        if ((*comp_)(k, node->left->data.first))
        {
          node = rotate_right(node);
        }
        else
        {
          node = rotate_double_right(node);
        }
      }
      if (get_height(node->right) - get_height(node->left) == 2)
      {
        if ((*comp_)(node->right->data.first, k))
        {
          node = rotate_left(node);
        }
        else
        {
          node = rotate_double_left(node);
        }
      }
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
  };
}

#endif
