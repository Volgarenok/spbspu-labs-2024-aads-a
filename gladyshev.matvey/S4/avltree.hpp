#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <algorithm>

#include "treenode.hpp"
#include "treeiterator.hpp"

namespace gladyshev
{
  template < typename Key, typename Value, typename Compare = std::less< Key > >
  struct Tree
  {
  public:
    using tnode = detail::TNode< Key, Value >;
    using iter = TIterator< Key, Value, Compare >;
    using citer = CTIterator< Key, Value, Compare >;
    Tree():
      root_(nullptr)
    {}
    ~Tree()
    {
      clear();
    }
    size_t size() const noexcept
    {
      if (!root_)
      {
        return 0;
      }
      return 1 + size(root_->right) + size(root_->left);
    }
    citer cbegin() const noexcept
    {
      tnode* temp = root_;
      if (!temp)
      {
        return citer(nullptr);
      }
      while (temp->left)
      {
        temp = temp->left;
      }
      return citer(temp);
    }
    citer cend() const noexcept
    {
      return citer();
    }
    iter begin() noexcept
    {
      tnode* temp = root_;
      if (!temp)
      {
        return iter(nullptr);
      }
      while (temp->left)
      {
        temp = temp->left;
      }
      return iter(temp);
    }
    iter end() noexcept
    {
      return iter();
    }
    Tree(const Tree& other):
      Tree()
    {
      root_ = copyNodes(other.root_, nullptr);
    }
    Tree(Tree&& other):
     root_(other.root_)
    {
      other.root_ = nullptr;
    }
    citer find(const Key& value) const
    {
      tnode* node = root_;
      while (node)
      {
        if (Compare()(value, node->data.first))
        {
          node = node->left;
        }
        else if (Compare()(node->data.first, value))
        {
          node = node->right;
        }
        else
        {
          return citer(node);
        }
      }
      return citer();
    }
    iter find(const Key& value)
    {
      tnode* node = root_;
      while (node)
      {
        if (Compare()(value, node->data.first))
        {
          node = node->left;
        }
        else if (Compare()(node->data.first, value))
        {
          node = node->right;
        }
        else
        {
          return iter(node);
        }
      }
      return iter();
    }
    bool empty() const noexcept
    {
      return root_ == nullptr;
    }
    Value& operator[](const Key& key)
    {
      tnode* node = findNode(root_, key);
      if (!node)
      {
        insert(key, Value());
        node = findNode(root_, key);
      }
      return node->data.second;
    }
    Value& at(const Key& key)
    {
      tnode* node = findNode(root_, key);
      if (!node)
      {
        throw std::out_of_range("Key not found in the tree");
      }
      return node->data.second;
    }
    const Value& at(const Key& key) const
    {
      tnode* node = findNode(root_, key);
      if (!node)
      {
        throw std::out_of_range("Key not found in the tree");
      }
      return node->data.second;
    }
    void swap(Tree<Key, Value, Compare>& other) noexcept
    {
      std::swap(root_, other.root_);
    }
    void clear()
    {
      helpClear(root_);
    }
    Tree& operator=(const Tree& other)
    {
      if (this != std::addressof(other))
      {
        Tree temp(other);
        swap(temp);
      }
      return *this;
    }
    void insert(const Key& key, const Value& value)
    {
      if (!root_)
      {
        root_ = new tnode(key, value);
      }
      else
      {
        root_ = insertImpl(key, value, root_);
      }
    }
  private:
    tnode* rotateRight(tnode* node)
    {
      tnode* toRotate = node->left;
      tnode* temp = toRotate->right;
      toRotate->right = node;
      node->left = temp;
      toRotate->parent = node->parent;
      node->parent = toRotate;
      node->height = std::max(height(node->left), height(node->right)) + 1;
      toRotate->height = std::max(height(toRotate->left), height(toRotate->right)) + 1;
      return toRotate;
    }
    tnode* rotateLeft(tnode* node)
    {
      tnode* toRotate = node->right;
      tnode* temp = toRotate->left;
      toRotate->left = node;
      node->right = temp;
      toRotate->parent = node->parent;
      node->parent = toRotate;
      node->height = std::max(height(node->left), height(node->right)) + 1;
      toRotate->height = std::max(height(toRotate->left), height(toRotate->right)) + 1;
      return toRotate;
    }
    tnode* copyNodes(tnode* node, tnode* parent)
    {
      if (!node)
      {
        return nullptr;
      }
      tnode* newNode = new tnode(node->data.first, node->data.second);
      newNode->parent = parent;
      newNode->left = copyNodes(node->left, newNode);
      newNode->right = copyNodes(node->right, newNode);
      newNode->height = node->height;
      return newNode;
    }
    tnode * insertImpl(const Key& key,const Value& value, tnode * node)
    {
      if (Compare()(key, node->data.first))
      {
        if (!node->left)
        {
          node->left = new tnode(key, value);
        }
        node->left = insertImpl(key, value, node->left);
        if (height(node->left) - height(node->right) > 1)
        {
          if (Compare()(key, node->left->data.first))
          {
            node = rotateRight(node);
          }
          else
          {
            node->left = rotateLeft(node->left);
            node = rotateRight(node);
          }
        }
      }
      else if (Compare()(node->data.first, key))
      {
        if (!node->right)
        {
          node->right = new tnode(key, value);
        }
        node->right = insertImpl(key, value, node->right);
        if (height(node->right) - height(node->left) > 1)
        {
          if (Compare()(node->right->data.first, key))
          {
            node = rotateLeft(node);
          }
          else
          {
            node->right = rotateRight(node->right);
            node = rotateLeft(node);
          }
        }
      }
      else
      {
        node->data.second = value;
      }
      node->height = std::max(height(node->left), height(node->right)) + 1;
      return node;
    }
    tnode* findNode(tnode* node, const Key& key) const
    {
      if (!node)
      {
        return nullptr;
      }
      if (Compare()(key, node->data.first))
      {
        return findNode(node->left, key);
      }
      else if (Compare()(node->data.first, key))
      {
        return findNode(node->right, key);
      }
      else
      {
        return node;
      }
    }
    void helpClear(tnode* node)
    {
      if (node)
      {
        helpClear(node->left);
        helpClear(node->right);
        delete node;
      }
    }
    long long height(tnode* node)
    {
      if (!node)
      {
        return 0;
      }
      return node->height;
    }
    tnode* root_;
  };
}

#endif
