#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <functional>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <utility>
#include "AVLtreeNode.hpp"
#include "constIteratorTree.hpp"
#include "IteratorTree.hpp"

namespace novokhatskiy
{
  template <class Key, class Value, class Compare = std::less<Key>>
  class Tree
  {
  public:
    using node_t = detail::NodeTree<Key, Value>;
    using v_type = std::pair<Key, Value>;
    using constIter = ConstIteratorTree< Key, Value, Compare >;
    using iter = IteratorTree< Key, Value, Compare >;

    Tree():
      root_(nullptr),
      size_(0),
      cmp_()
    {}

    Tree(const Tree& other) :
      root_(nullptr),
      size_(0),
      cmp_(other.cmp_)
    {
      try
      {
        for (auto begin = other.cbegin(); begin != other.cend(); begin++)
        {
          insert3(*begin);
        }
      }
      catch (const std::exception&)
      {
        clear();
        throw;
      }
    }

    Tree(Tree&& other):
      root_(other.root_),
      size_(other.size_),
      cmp_(std::move(other.cmp_))
    {
      other.root_ = nullptr;
      other.size_ = 0;
    }

    Tree& operator=(const Tree& other)
    {
      Tree map(other);
      clear();
      this->swap(map);
      return *this;
      /*if (this != std::addressof(other))
      {
        Tree<Key, Value> tmp(other);
        swap(tmp);
      }
      return *this;*/
    }

    Tree& operator=(Tree&& other)
    {
      clear();
      this->swap(other);
      return *this;
      /*if (this != std::addressof(other))
      {
        swap(other);
      }
      return *this;*/
    }

    node_t* find(node_t* node, const Key& key)
    {
      node_t* root = (node->height < 0) ? node->left : node;
      while (root)
      {
        if (key == root->value.first)
        {
          return root;
        }
        if (cmp_(key, root->value.first))
        {
          if (!root->left)
          {
            return root;
          }
          root = root->left;
        }
        else
        {
          if (!root->right)
          {
            return root;
          }
          root = root->right;
        }
      }
      return nullptr;
    }

    iter find(const Key& key)
    {
      node_t* curr = root_;
      while (curr)
      {
        if (curr->value.first == key)
        {
          return iter(curr);
        }
        curr = (cmp_(curr->value.first, key)) ? curr->right : curr->left;
      }
      return iter(curr);
    }

    constIter find(const Key& key) const
    {
      node_t* curr = root_;
      while (curr)
      {
        if (curr->value.first == key)
        {
          return constIter(curr);
        }
        curr = (cmp_(curr->value.first, key)) ? curr->right : curr->left;
      }
      return constIter(curr);
    }

    size_t erase(const Key& key);

    Value& at(const Key& key)
    {
      node_t* curr = search(key);
      if (curr)
      {
        return curr->value.second;
      }
      throw std::out_of_range("No such element");
    }

    const Value& at(const Key& key) const
    {
      node_t* curr = search(key); //find(root_->left, key)
      if (curr) //&& curr->value.first == key
      {
        return curr->value.second;
      }
      throw std::out_of_range("No such element");
    }

    Value& operator[](const Key& key)
    {
      node_t* tmp = search(key);
      if (tmp->value.first == key)
      {
        return tmp->value.second;
      }
      else
      {
        insert3(std::make_pair(key, Value()));
        node_t* res = search(key);
        return res->value.second;
      }
    }

    const Value& operator[](const Key& key) const
    {
      node_t* tmp = search(key);
      if (tmp->value.first == key)
      {
        return tmp->value.second;
      }
      else
      {
        insert3(std::make_pair(key, Value()));
        node_t* res = search(key);
        return res->value.second;
      }
    }

    void prePrint(node_t* root)
    {
      if (root->left != nullptr)
      {
        prePrint(root->left);
      }
      std::cout << ' ' << root->value.second << ' ';
      if (root->right != nullptr)
      {
        prePrint(root->right);
      }
    }

    void print()
    {
      prePrint(root_);
    }

    void fixedHeight(node_t* node, int h)
    {
      if (h + 1 > node->height)
      {
        node->height++;
      }
      if (node->parent)
      {
        fixedHeight(node->parent, node->height);
      }
    }

    int getBalanceFactor(node_t* node)
    {
      int rightH = 0;
      int leftH = 0;
      if (node->right)
      {
        rightH = node->right->height;
      }
      if (node->left)
      {
        leftH = node->left->height;
      }
      return rightH - leftH;
    }

    node_t* updateHeight(node_t* node)
    {
      node->height = 1 + std::max(node->getHeight(node->left), node->getHeight(node->right));
      return node;
    }

    node_t* insert(const std::pair< Key, Value >& value)
    {
      root_ = insert_imp(value, root_);
      return root_;
    }

    void insert2(const std::pair< Key, Value >& value)
    {
      try
      {
        if (root_)
        {
          insert_imp2(value, root_);
          size_++;
        }
        else
        {
          root_ = new node_t(value);
          size_++;
        }
      }
      catch (const std::exception&)
      {
        clear();
        throw;
      }
    }
    size_t size() const noexcept
    {
      return size_;
    }

    bool empty() const noexcept
    {
      return !size_;
    }

    void clear()
    {
      clear_imp(root_);
    }

    void swap(Tree& other)
    {
      std::swap(root_, other.root_);
      std::swap(size_, other.size_);
      std::swap(cmp_, other.cmp_);
    }

    iter erase(iter pos)
    {
      iter res = pos;
      res++;
      node_t* node = nullptr;
      node_t* delElement = nullptr;
      if (!pos.node_->left || !pos.node_->right)
      {
        delElement = pos.node_;
        node = delElement->parent;
        if (!pos.node_->left && !pos.node_->right)
        {
          if (node->left = delElement)
          {
            node->left = nullptr;
          }
          else if (node->right == delElement)
          {
            node->right = nullptr;
          }
        }
        else if (!pos.node_->left && pos.node_->right)
        {
          if (delElement == node->left)
          {
            node->left = delElement->right;
          }
          if (delElement == node->right)
          {
            node->right = delElement->right;
          }
          delElement->right->parent = node;
        }
        else if (!pos.node_->right && pos.node_->left)
        {
          if (delElement == node->left)
          {
            node->left = delElement->left;
          }
          else if (delElement == node->right)
          {
            node->left = delElement->right;
          }
          delElement->left->parent = node;
        }
      }
      else
      {
        auto tmp = pos.node_;
        --pos;
        tmp->value = *pos;
        delElement = pos.node_;
        node = delElement->parent;
        if (delElement == node->right)
        {
          node->right = delElement->left;
        }
        else
        {
          node->left = delElement->left;
        }
        if (delElement->left)
        {
          delElement->left->parent = node;
        }
      }
      delete delElement;
      balance(res.node_);
      return iter(res.node_);
    }

    iter lower_bound(const Key& key)
    {
      iter curr = find(key);
      if (cmp_(curr.node_->value.first, key))
      {
        return ++curr;
      }
      return curr;
    }

    constIter lower_bound(const Key& key) const
    {
      iter curr = find(key);
      if (cmp_(curr.node_->value.first, key))
      {
        return ++curr;
      }
      return curr;
    }

    iter upper_bound(const Key& key)
    {
      iter res = lower_bound(key);
      if (res.node_->value.first == key && res != end())
      {
        return ++res;
      }
      return res;
    }

    constIter upper_bound(const Key& key) const
    {
      constIter res = lower_bound(key);
      if (res.node_->value.first == key && res != cend())
      {
        return ++res;
      }
      return res;
    }

    std::pair< iter, iter > equal_range(const Key& key)
    {
      return std::make_pair(lower_bound(key), upper_bound(key));
    }

    std::pair< constIter, constIter > equal_range(const Key& key) const
    {
      return std::make_pair(lower_bound(key), upper_bound(key));
    }

    size_t count(const Key& key)
    {
      return (find(key) != end());
    }

    constIter cbegin() const
    {
      node_t* curr = root_;
      for (; curr->left; curr = curr->left);
      return constIter(curr);
    }

    constIter cend() const
    {
      return constIter();
    }

    iter begin()
    {
      node_t* curr = root_;
      for (; curr->left; curr = curr->left);
      return iter(curr);
    }

    iter end()
    {
      return iter(root_);
    }

    node_t* search(const Key& key)
    {
      node_t* result = search_imp(root_, key);
      return result;
    }

    void insert3(const std::pair< Key, Value >& val)
    {
      try
      {
        if (root_)
        {
          insert_imp3(val, root_);
          ++size_;
        }
        else
        {
          root_ = new node_t(val);
          ++size_;
        }
      }
      catch (const std::exception&)
      {
        clear();
        throw;
      }
    }

    ~Tree()
    {
      clear();
    }

  private:
    node_t* root_;
    size_t size_;
    Compare cmp_;

    void balance2(node_t* node)
    {
      if (node->height < 0)
      {
        if (node->right->height > 0)
        {
          node->right = rotate_right2(node->right);
        }
        node = rotate_left2(node);
      }
      else
      {
        if (node->left->height < 0)
        {
          node->left = rotate_left2(node->left);
        }
        node = rotate_right2(node);
      }
    }

    void getBalance(node_t* node)
    {
      if ((node->height > 1) || (node->height < -1))
      {
        balance2(node);
      }
      else
      {
        if (node->parent)
        {
          if (node->left)
          {
            ++node->parent->height;
          }
          else if (node->right)
          {
            --node->parent->height;
          }
          if (node->parent->height != 0)
          {
            getBalance(node->parent);
          }
        }
      }
    }

    node_t* rotate_left2(node_t* node)
    {
      node_t* newRoot = node->right;
      node->right = newRoot->left;
      if (newRoot->left)
      {
        newRoot->left->parent = node;
      }
      newRoot->left = node;
      node->parent = newRoot;
      node->height = node->height + 1 - std::min(newRoot->height, 0);
      newRoot->height = newRoot->height + 1 + std::max(node->height, 0);
      return newRoot;
    }

    node_t* rotate_right2(node_t* node)
    {
      node_t* newRoot = node->left;
      node->left = newRoot->right;
      if (newRoot->right)
      {
        newRoot->right->parent = node;
      }
      newRoot->right = node;
      node->parent = newRoot;
      node->height = node->height - 1 - std::max(0, newRoot->height);
      newRoot->height = newRoot->height - 1 + std::min(0, node->height);
      return newRoot;
    }

    void insert_imp3(const std::pair< Key, Value >& value, node_t* node)
    {
      try
      {
        if (cmp_(value.first, node->value.first))
        {
          if (node->left)
          {
            insert_imp3(value, node->left);
          }
          else
          {
            node->left = new node_t(value, node);
            getBalance(node->left);
          }
        }
        else
        {
          if (node->right)
          {
            insert_imp3(value, node->right);
          }
          else
          {
            node->right = new node_t(value, node);
            getBalance(node->right);
          }
        }
      }
      catch (const std::exception&)
      {
        clear();
        throw;
      }
    }

    void clear_imp(node_t* root)
    {
      if (root)
      {
        clear_imp(root->left);
        clear_imp(root->right);
        delete root;
      }
    }

    node_t* insert_imp(const std::pair< Key, Value >& value, node_t* curr)
    {
      if (curr == nullptr)
      {
        curr = new node_t(value);
      }
      if (cmp_(curr->value.first, value.first))
      {
        curr->right = insert_imp(value, curr->right);
      }
      else if (curr->value.first == value.first)
      {
        return balance(curr);
      }
      else
      {
        curr->left = insert_imp(value, curr->left);
      }
      return balance(curr);
    }

    void insert_imp2(const std::pair< Key, Value >& value, node_t* curr)
    {
      try
      {
        if (cmp_(value.first, curr->value.first))
        {
          if (curr->left)
          {
            insert_imp2(value, curr->left);
          }
          else
          {
            curr->left = new node_t(value, curr);
            fixedHeight(curr, 0);
            if (curr->parent)
            {
              node_t* tmp = balance(curr->parent);
              if (root_->parent)
              {
                root_ = tmp;
              }
            }
          }
        }
        else
        {
          if (curr->right)
          {
            insert_imp2(value, curr->right);
          }
          else
          {
            curr->right = new node_t(value, curr);
            fixedHeight(curr, 0);
            if (curr->parent)
            {
              balance(curr->parent);
              node_t* tmp = balance(curr->parent);
              if (root_->parent)
              {
                root_ = tmp;
              }
            }
          }
        }
      }
      catch (...)
      {
        clear();
        throw;
      }
    }

    node_t* balance(node_t* node)
    {
      if (getBalanceFactor(node) == 1)
      {
        //if (getBalanceFactor(node->right) < 0)
        //{
          node->right = rotate_right(node->right);
        //}
        return rotate_left(node);
      }
      if (getBalanceFactor(node) == -1)
      {
        if (getBalanceFactor(node->left) > 0)
        {
          node->left = rotate_left(node->left);
        }
        return rotate_right(node);
      }
      return node;
    }

    node_t* rotate_left(node_t* currRoot)
    {
      node_t* newRoot = currRoot->right;
      currRoot->right = newRoot->left;
      if (newRoot->left)
      {
        newRoot->left->parent = currRoot;
      }
      newRoot->left = currRoot;
      newRoot->parent = currRoot->parent;
      if (currRoot->parent)
      {
        currRoot->parent->left = newRoot;
      }
      currRoot->parent = newRoot;
      //std::swap(newRoot->height, currRoot->height);
      //fixedHeight(currRoot);
      //fixedHeight(newRoot);
      return newRoot;
    }

    node_t* rotate_right(node_t* currRoot)
    {
      node_t* newRoot = currRoot->left;
      currRoot->left = newRoot->right;
      if (newRoot->right)
      {
        newRoot->right->parent = currRoot;
      }
      newRoot->right = currRoot;
      newRoot->parent = currRoot->parent;
      currRoot->parent->right = newRoot;
      currRoot->parent = newRoot;
      //fixedHeight(currRoot);
      //fixedHeight(newRoot);
      return newRoot;
    }

    node_t* minN(node_t* p) const
    {
      return (p->left) ? minN(p->left) : p;
      /*auto tmp = root_->left;
      while (tmp->left)
      {
        tmp = tmp->left;
      }
      root_ = tmp;
      return root_;*/
    }

    node_t* search_imp(node_t* node, const Key& key)
    {
      if (!node)
      {
        return nullptr;
      }
      else if (cmp_(key, node->value.first))
      {
        return search_imp(node->left, key);
      }
      else if (cmp_(node->value.first, key))
      {
        return search_imp(node->right, key);
      }
      else
      {
        return node;
      }
    }
  };
}

#endif
