#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <functional>
#include <cstddef>
#include <iostream>
#include <cassert>
#include <type_traits>
#include <stdexcept>
#include <utility>
#include <queue.hpp>
#include <AVLtreeNode.hpp>
#include <constIteratorTree.hpp>
#include <IteratorTree.hpp>

namespace novokhatskiy
{
  template < class Key, class Value, class Compare = std::less< Key > >
  class Tree
  {
  public:
    using node_t = detail::NodeTree< Key, Value >;
    using v_type = std::pair< Key, Value >;
    using constIter = ConstIteratorTree< Key, Value, Compare >;
    using iter = IteratorTree< Key, Value, Compare >;

    Tree():
      root_(nullptr),
      size_(0),
      cmp_()
    {}

    Tree(const Tree &other):
      root_(nullptr),
      size_(0),
      cmp_(other.cmp_)
    {
      try
      {
        for (auto begin = other.cbegin(); begin != other.cend(); begin++)
        {
          insert(*begin);
        }
      }
      catch (const std::exception &)
      {
        clear();
        throw;
      }
    }

    Tree(Tree &&other) noexcept:
      root_(other.root_),
      size_(other.size_),
      cmp_(std::move(other.cmp_))
    {
      static_assert(std::is_nothrow_copy_constructible< Compare >::value, "static_assert");
      other.root_ = nullptr;
      other.size_ = 0;
    }

    Tree &operator=(const Tree &other)
    {
      Tree map(other);
      clear();
      this->swap(map);
      return *this;
    }

    Tree &operator=(Tree &&other) noexcept
    {
      clear();
      this->swap(other);
      return *this;
    }

    template< class F >
    F traverse_lnr(F f)
    {
      if (empty())
      {
        throw std::logic_error("<EMPTY>");
      }
      for (auto i = cbegin(); i != cend(); i++)
      {
        f(*i);
      }
      return f;
    }

    template< class F >
    F traverse_rnl(F f)
    {
      if (empty())
      {
        throw std::logic_error("<EMPTY>");
      }
      for (auto i = cbeginRight(); i != cend(); --i)
      {
        f(*i);
      }
      return f;
    }

    template< class F >
    F traverse_breadth(F f)
    {
      if (empty())
      {
        throw std::logic_error("<EMPTY>");
      }
      Queue< node_t* > queue;
      queue.push(root_);
      while (!queue.empty())
      {
        node_t* node = queue.front();
        queue.pop();
        f(node->value);
        if (node->left)
        {
          queue.push(node->left);
        }
        if (node->right)
        {
          queue.push(node->right);
        }
      }
      return f;
    }

    iter find(const Key &key)
    {
      node_t *curr = root_;
      while (curr)
      {
        if (cmp_(curr->value.first, key))
        {
          curr = curr->right;
        }
        else if (cmp_(key, curr->value.first))
        {
          curr = curr->left;
        }
        else
        {
          return iter(curr);
        }
      }
      return iter(curr);
    }

    constIter find(const Key &key) const
    {
      node_t *curr = root_;
      while (curr)
      {
        if (cmp_(curr->value.first, key))
        {
          curr = curr->right;
        }
        else if (cmp_(key, curr->value.first))
        {
          curr = curr->left;
        }
        else
        {
          return constIter(curr);
        }
      }
      return constIter(curr);
    }

    Value& at(const Key& key)
    {
      iter curr = find(key);
      if (curr.node_)
      {
        return curr.node_->value.second;
      }
      throw std::out_of_range("No such element");
    }

    const Value &at(const Key &key) const
    {
      constIter curr = find(key);
      if (curr.node_)
      {
        return curr.node_->value.second;
      }
      throw std::out_of_range("No such element");
    }

    Value &operator[](const Key &key)
    {
      auto tmp = std::make_pair(key, Value());
      return (insert(tmp).first)->second;
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
      root_ = nullptr;
    }

    void swap(Tree &other) noexcept
    {
      static_assert(std::is_nothrow_copy_constructible<Compare>::value, "static_assert");
      std::swap(root_, other.root_);
      std::swap(size_, other.size_);
      std::swap(cmp_, other.cmp_);
    }

    iter erase(iter pos)
    {
      iter res = pos;
      res++;
      node_t *node = nullptr;
      node_t *delElement = nullptr;
      if (!pos.node_->left || !pos.node_->right)
      {
        delElement = pos.node_;
        node = delElement->parent;
        if (!pos.node_->left && !pos.node_->right)
        {
          if (node->left == delElement)
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

    iter lower_bound(const Key &key)
    {
      iter curr = find(key);
      if (cmp_(curr.node_->value.first, key))
      {
        return ++curr;
      }
      return curr;
    }

    constIter lower_bound(const Key &key) const
    {
      iter curr = find(key);
      if (cmp_(curr.node_->value.first, key))
      {
        return ++curr;
      }
      return curr;
    }

    iter upper_bound(const Key &key)
    {
      iter res = lower_bound(key);
      if (res.node_->value.first == key && res != end())
      {
        return ++res;
      }
      return res;
    }

    constIter upper_bound(const Key &key) const
    {
      constIter res = lower_bound(key);
      if (res.node_->value.first == key && res != cend())
      {
        return ++res;
      }
      return res;
    }

    constIter cbeginRight() const
    {
      return constIter(lastRight(root_));
    }

    std::pair< iter, iter > equal_range(const Key &key)
    {
      return std::make_pair(lower_bound(key), upper_bound(key));
    }

    std::pair< constIter, constIter > equal_range(const Key &key) const
    {
      return std::make_pair(lower_bound(key), upper_bound(key));
    }

    size_t count(const Key &key)
    {
      return (find(key) != end());
    }

    constIter cbegin() const
    {
      return constIter(minN(root_));
    }

    constIter cend() const
    {
      return constIter();
    }

    iter begin()
    {
      return iter(minN(root_));
    }

    iter end()
    {
      return iter();
    }

    std::pair< iter, bool > insert(const std::pair< Key, Value >& val)
    {
      node_t* tmp = search(val.first);
      bool isInsert = false;
      if ((tmp && tmp->value.first != val.first) || !tmp)
      {
        insert_imp(val, tmp);
        ++size_;
        isInsert = true;
      }
      return std::pair< iter, bool >(find(val.first), isInsert);
    }

    ~Tree()
    {
      clear();
    }

  private:
    node_t *root_;
    size_t size_;
    Compare cmp_;

    node_t* lastRight(node_t* node) const
    {
      node_t* res = node;
      if (!res)
      {
        return nullptr;
      }
      while (res->right)
      {
        res = res->right;
      }
      return res;
    }

    void balance(node_t *node)
    {
      if (node->height < 0)
      {
        if (node->right->height > 0)
        {
          node->right = rotate_right(node->right);
        }
        node = rotate_left(node);
      }
      else
      {
        if (node->left->height < 0)
        {
          node->left = rotate_left(node->left);
        }
        node = rotate_right(node);
      }
    }

    node_t *search(const Key &key) const
    {
      node_t *result = search_imp(root_, key);
      return result;
    }

    node_t *updateHeight(node_t *node)
    {
      node->height = 1 + std::max(node->getHeight(node->left), node->getHeight(node->right));
      return node;
    }

    void getBalance(node_t *node)
    {
      if ((node->height > 1) || (node->height < -1))
      {
        balance(node);
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

    node_t *rotate_left(node_t *node)
    {
      node_t *newRoot = node->right;
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

    node_t *rotate_right(node_t *node)
    {
      node_t *newRoot = node->left;
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

    void insert_imp(const std::pair<Key, Value>& value, node_t* node)
    {
      if (!node)
      {
        root_ = new node_t(value);
      }
      else if (cmp_(value.first, node->value.first))
      {
        if (node->left)
        {
          insert_imp(value, node->left);
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
          insert_imp(value, node->right);
        }
        else
        {
          node->right = new node_t(value, node);
          getBalance(node->right);
        }
      }
    }

    void clear_imp(node_t *root)
    {
      if (root)
      {
        --size_;
        clear_imp(root->left);
        clear_imp(root->right);
        delete root;
      }
    }

    node_t *find(node_t *node, const Key &key)
    {
      node_t *root = (node->height < 0) ? node->left : node;
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

    node_t *minN(node_t *p) const
    {
      node_t *res = p;
      if (!res)
      {
        return nullptr;
      }
      while (res->left)
      {
        res = res->left;
      }
      return res;
    }

    node_t* search_imp(node_t* node, const Key& key) const
    {
      if (!node)
      {
        return nullptr;
      }
      else if (cmp_(key, node->value.first))
      {
        if (node->left)
        {
          return search_imp(node->left, key);
        }
        else
        {
          return node;
        }
      }
      else if (cmp_(node->value.first, key))
      {
        if (node->right)
        {
          return search_imp(node->right, key);
        }
        else
        {
          return node;
        }
      }
      else
      {
        return node;
      }
    }
  };
}

#endif
