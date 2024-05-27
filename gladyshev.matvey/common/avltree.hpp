#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <algorithm>

#include "treenode.hpp"
#include "treeiterator.hpp"
#include "queue.hpp"

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
    size_t count(const Key& key) const
    {
      return find(key) != cend();
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
    void erase(const Key& key)
    {
      root_ = eraseImpl(root_, key);
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
      return citer(findNode(root_, value));
    }
    iter find(const Key& value)
    {
      return iter(findNode(root_, value));
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
        if (!root_)
        {
          root_ = new tnode(key, Value());
          return root_->data.second;
        }
        std::pair< tnode*, tnode* > result = insertImpl(key, Value(), root_);
        node = result.second;
      }
      return node->data.second;
    }
    std::pair< iter, iter > equal_range(const Key& key)
    {
      iter it = find(key);
      if (it != end())
      {
        return std::make_pair(it, ++it);
      }
      return std::make_pair(end(), end());
    }
    std::pair< citer, citer > equal_range(const Key& key) const
    {
      citer it = find(key);
      if (it != cend())
      {
        return std::make_pair(it, ++it);
      }
      return std::make_pair(cend(), cend());
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
        std::pair< tnode*, tnode* > result = insertImpl(key, value, root_);
        root_ = result.first;
      }
    }
    template< typename F >
    F traverse_lnr(F f) const
    {
      if (empty())
      {
        throw std::logic_error("<EMPTY>");
      }
      for (auto it = cbegin(); it != cend(); ++it)
      {
        f(*it);
      }
      return f;
    }
    template< typename F >
    F traverse_rnl(F f) const
    {
      if (empty())
      {
        throw std::logic_error("<EMPTY>");
      }
      tnode* temp = root_;
      while (temp->right)
      {
        temp = temp->right;
      }
      auto begin = citer(temp);
      while (begin != cend())
      {
        f(*begin);
        --begin;
      }
      return f;
    }
    template< typename F >
    F traverse_breadth(F f) const
    {
      if (empty())
      {
        throw std::logic_error("<EMPTY>");
      }
      Queue< tnode * > nod;
      nod.push(root_);
      while (!nod.empty())
      {
        tnode* curr = nod.back();
        nod.pop();
        f(curr->data);
        if (curr->left)
        {
          nod.push(curr->left);
        }
        if (curr->right)
        {
          nod.push(curr->right);
        }
      }
      return f;
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
    tnode* eraseImpl(tnode* t, const Key& key)
    {
      if (!t)
      {
        return t;
      }
      if (Compare()(key, t->data.first))
      {
        t->left = eraseImpl(t->left, key);
      }
      else if (Compare()(t->data.first, key))
      {
        t->right = eraseImpl(t->right, key);
      }
      else
      {
        if (!t->left || !t->right)
        {
          tnode* temp = t->left ? t->left : t->right;
          delete t;
          return temp;
        }
        else
        {
          tnode* m = t->left;
          while (m->right)
          {
            m = m->right;
          }
          t->data = m->data;
          t->left = eraseImpl(t->left, m->data.first);
       }
      }
      t->height = 1 + std::max(height(t->left), height(t->right));
      return rebalance(t);
    }
    tnode* rebalance(tnode* node)
    {
      int balance = height(node->left) - height(node->right);
      if (balance > 1)
      {
        if (height(node->left->left) >= height(node->left->right))
        {
          node = rotateRight(node);
        }
        else
        {
          node->left = rotateLeft(node->left);
          node = rotateRight(node);
        }
      }
      else if (balance < -1)
      {
        if (height(node->right->right) >= height(node->right->left))
        {
          node = rotateLeft(node);
        }
        else
        {
          node->right = rotateRight(node->right);
          node = rotateLeft(node);
        }
      }
      return node;
    }
    std::pair< tnode*, tnode* > insertImpl(const Key& key, const Value& value, tnode* node)
    {
      tnode* temp = nullptr;
      if (Compare()(key, node->data.first))
      {
        if (!node->left)
        {
          node->left = new tnode(key, value);
          node->left->parent = node;
          temp = node->left;
        }
        else
        {
          auto result = insertImpl(key, value, node->left);
          node->left = result.first;
          temp = node->left;
        }
      }
      else if (Compare()(node->data.first, key))
      {
        if (!node->right)
        {
          node->right = new tnode(key, value);
          node->right->parent = node;
          temp = node->right;
        }
        else
        {
          auto result = insertImpl(key, value, node->right);
          node->right = result.first;
          temp = result.second;
        }
      }
      else
      {
        node->data.second = value;
        temp = node;
      }
      node = rebalance(node);
      node->height = 1 + std::max(height(node->left), height(node->right));
      return std::make_pair(node, temp);
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
