#ifndef TREE_HPP
#define TREE_HPP

#include <functional>
#include "tree_node.hpp"
#include "tree_iterator.hpp"
#include "const_tree_iterator.hpp"

namespace namestnikov
{
  template< class Key, class Value, class Compare = std::less< Key > >
  class Tree
  {
  public:
    using pair_key_t = std::pair< const Key, Value >;
    using node_t = TreeNode< pair_key_t >;
    using iterator = IteratorTree< Key, Value, Compare >;
    using const_iterator = ConstIteratorTree< Key, Value, Compare >;
    Tree():
      root_(nullptr),
      size_(0)
    {}
    Tree(const Tree & other):
      root_(other.root_),
      size_(other.size_),
      compare_(other.compare_)
    {
      other.root_ = nullptr;
      other.size_ = 0;
    }
    Tree & operator=(const Tree & other)
    {
      if (this != std::addressof(other))
      {
        Tree< Key, Value, Compare > temp(other);
        swap(temp);
      }
      return *this;
    }
    Tree & operator=(Tree && other)
    {
      if (this != std::addressof(other))
      {
        swap(other);
      }
      return *this;
    }
    const Value & at(const Key & key)
    {
      node_t * result = search(root_, key);
      if (result)
      {
        return result->data.second;
      }
      else
      {
        throw std::out_of_range("Can not give you access to this element");
      }
    }
    Value & operator[](const Key & key)
    {
      node_t * result = search(root_, key);
      if (result)
      {
        return result->data.second;
      }
      else
      {
        insert(std::make_pair(key, Value()));
        return search(root_, key)->data.second;
      }
    }
    void rotate_left(node_t * node)
    {
      node_t * newRoot = node->right;
      node_t * temp = newRoot->left;
      node->right = temp;
      newRoot->left = node;
      updateHeight(newRoot);
      updateHeight(node);
    }
    void rotate_right(node_t * node)
    {
      node_t * newRoot = node->left;
      node_t * temp = newRoot->right;
      node->left = temp;
      newRoot->right = node;
      updateHeight(node);
      updateHeight(newRoot);
    }
    void print_impl(node_t * root)
    {
      if (root->left != nullptr)
      {
        print_impl(root->left);
      }
      std::cout << " " << root->data.second << " ";
      if (root->right != nullptr)
      {
        print_impl(root->right);
      }
    }
    void print()
    {
      print_impl(root_);
    }
    node_t * balance(node_t * node)
    {
      fixHeight(node);
      if (getBalance(node) == 2)
      {
        if (getBalance(node->right) < 0)
        {
          rotate_right(node->right);
        }
        rotate_left(node);
      }
      else if (getBalance(node) == -2)
      {
        if (getBalance(node->left) > 0)
        {
          rotate_left(node->left);
        }
        rotate_right(node);
      }
      return node;
    }
    node_t * find_min(node_t * node)
    {
      node_t * temp = node;
      while (temp->left)
      {
        temp = temp->left;
      }
      return temp;
    }
    const_iterator find(const Key & key) const
    {
      node_t * temp = root_;
      while ((temp) && (temp->data.first == key))
      {
        if (compare_(temp->data.first, key))
        {
          temp = temp->right;
        }
        else
        {
          temp = temp->left;
        }
      }
      return const_iterator(temp);
    }
    node_t * insert(const pair_key_t & value, node_t * root)
    {
      if (root == nullptr)
      {
        root = new node_t(value);
      }
      else if (compare_(value.first, root->data.first))
      {
        root->left = insert(value, root->left);
        root->left->parent = root;
      }
      else
      {
        root->right = insert(value, root->right);
        root->right->parent = root;
      }
      return balance(root);
    }
    void insert(const pair_key_t & value)
    {
      root_ = insert(value, root_);
      ++size_;
    }
    node_t * search(const Key & key) const
    {
      return search(root_, key);
    }
    node_t * search(node_t * node, const Key & key) const
    {
      if ((node == nullptr) || (node->data.first == key))
      {
        return node;
      }
      if (compare_(key, node->data.first))
      {
        return search(node->left, key);
      }
      else
      {
        return search(node->right, key);
      }
    }
    bool contains(const Key & key) const
    {
      return search(root_, key) != nullptr;
    }
    void fixHeight(node_t * node)
    {
      int rightHeight = getHeight(node->right);
      int leftHeight = getHeight(node->left);
      node->height = std::max(rightHeight, leftHeight) + 1;
    }
    int getHeight(node_t * root)
    {
      return root ? (root->height) : 0;
    }
    void updateHeight(node_t * node)
    {
      node->height = 1 + std::max(node->getHeight(node->left), node->getHeight(node->right));
    }
    int getBalance(node_t * node)
    {
      return getHeight(node->right) - getHeight(node->left);
    }
    bool empty() const noexcept
    {
      return (size_ == 0);
    }
    size_t size() const noexcept
    {
      return size_;
    }
    void swap(Tree & other)
    {
      std::swap(root_, other.root_);
      std::swap(size_, other.size_);
      std::swap(compare_, other.compare_);
    }
    ~Tree()
    {
      clear();
    }
  private:
    node_t * root_;
    size_t size_;
    Compare compare_;
    void clear()
    {
      clear(root_);
      root_ = nullptr;
      size_ = 0;
    }
    void clear(node_t * node)
    {
      if (node)
      {
        clear(node->left);
        clear(node->right);
        delete node;
      }
    }
  };
}

#endif