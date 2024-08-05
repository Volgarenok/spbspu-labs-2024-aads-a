#ifndef MYTREE_HPP
#define MYTREE_HPP

#include <functional>
#include <utility>
#include <list>

#include "treeNode.hpp"
#include "iterBase.hpp"

namespace rebdev
{
  template < class Key, class Value, class Compare = std::less< Key > >
  class AVLTree
  {
    using pair = std::pair< const Key, Value >;
    using node = TreeNode< pair >;

    public:
      using iterator = BaseIter< Key, Value, Compare, pair, node >;
      using const_iterator = BaseIter< Key, Value, Compare, const pair, const node >;

      AVLTree():
        headNode_(new node{nullptr, nullptr, nullptr, pair{}}),
        size_(0)
      {}
      ~AVLTree() noexcept
      {
        clear();
        delete headNode_;
      }

      iterator begin() const
      {
        node * beginNode = headNode_;
        while (((beginNode->left) != nullptr) || ((beginNode->right) != nullptr))
        {
          while ((beginNode->left) != nullptr)
          {
            beginNode = (beginNode->left);
          }
          if ((beginNode->right) != nullptr)
          {
            beginNode = (beginNode->right);
          }
        }
        return iterator(beginNode);
      }
      iterator end() const
      {
        return iterator(headNode_);
      }
      const_iterator cbegin() const
      {
        return const_iterator(*begin());
      }
      const_iterator cend() const
      {
        return const_iterator(*end());
      }

      bool empty() const noexcept
      {
        return (size_ == 0);
      }
      size_t size() const noexcept
      {
        return size_;
      }

      Value & operator[](const Key & k)
      {
        iterator it = find(k);
        if (it != end())
        {
          return ((*it).second);
        }

        node * newNode = new node{nullptr, nullptr, nullptr, pair{k, Value{}}};
        if ((headNode_->right) == nullptr)
        {
          (headNode_->right) = newNode;
          (newNode->parent) = headNode_;
        }
        else
        {
          node * nodeNow = (headNode_->right);
          while ((newNode->parent) != nodeNow)
          {
            if (comp((nodeNow->data.first), k))
            {
              if ((nodeNow->right) == nullptr)
              {
                (nodeNow->right) = newNode;
                (newNode->parent) = nodeNow;
              }
              else
              {
                nodeNow = (nodeNow->right);
              }
            }
            else
            {
              if ((nodeNow->left) == nullptr)
              {
                (nodeNow->left) = newNode;
                (newNode->parent) = nodeNow;
              }
              else
              {
                nodeNow = (nodeNow->left);
              }
            }
          }
        }
        ++size_;
        return (newNode->data.second);
      }
      Value & operator[](Key && k)
      {
        return operator[](k);
      }
      Value & at (const Key & k)
      {
        iterator it = find(k);
        if (it == end())
        {
          throw std::out_of_range("Can't find element in tree by method at");
        }
        return (*it).second;
      }
      const Value & at (const Key & k) const
      {
        const_iterator it = find(k);
        if (it = cend())
        {
          throw std::out_of_range("Can't find element in tree by method at");
        }
        return (*it).second;
      }

      void swap(AVLTree & tree)
      {
        std::swap(headNode_, tree.headNode_);
        std::swap(size_, tree.size_);
      }
      void clear() noexcept
      {
        iterator it = begin();
        while (it != end())
        {
          node * nodeToDel = it.node_;
          ++it;
          delete nodeToDel;
        }
        size_ = 0;
      }
      std::pair< iterator, bool > insert(const pair & p)
      {
        iterator it = find(p.first);
        bool orig = (it == end());
        if (orig)
        {
          (*this)[p.first] = p.second;
        }
        return std::pair< iterator, bool >{it, orig};
      }
      iterator erase (iterator position)
      {
        node * it = position.node_;
        if (((it->left) == nullptr) && ((it->right) == nullptr))
        {
          if ((it->parent) != nullptr)
          {
            if ((it->parent->left) == it)
            {
              it->parent->left = nullptr;
            }
            else
            {
              it->parent->right = nullptr;
            }
          }
          delete it;
          it = headNode_;
        }
        else
        {
          if ((it->left) != nullptr)
          {
            while ((it->left) != nullptr)
            {
              it = (it->left);
              while ((it->right) != nullptr)
              {
                it = (it->right);
              }
            }
          }
          else
          {
            while ((it->right) != nullptr)
            {
              it = (it->right);
              while ((it->left) != nullptr)
              {
                it = (it->left);
              }
            }
          }
          if ((position.node_->left) != it)
          {
            (it->left) = (position.node_->left);
          }
          else
          {
            (it->left) = nullptr;
          }
          if ((position.node_->right) != it)
          {
            (it->right) = (position.node_->right);
          }
          else
          {
            (it->right) = nullptr;
          }
          (it->parent) = (position.node_->parent);
          if ((it->left) != nullptr)
          {
            (it->left->parent) = it;
          }
          if ((it->right) != nullptr)
          {
            (it->right->parent) = it;
          }
          if ((it->parent) != nullptr)
          {
            if ((it->parent->right) == position.node_)
            {
              (it->parent->right) = it;
            }
            else
            {
              (it->parent->left) = it;
            }
          }
          delete position.node_;
        }
        --size_;
        return iterator(it);
      }
      size_t erase (const Key & k)
      {
        size_t num = 0;
        iterator it = find(k);
        while ((it.node_) != headNode_)
        {
          erase(it);
          ++num;
          it = find(k);
        }
        return num;
      }
      iterator find(const Key & k)
      {
        return iterator(findBase(k));
      }
      const_iterator find(const Key & k) const
      {
        return const_iterator(findBase(k));
      }
      size_t count (const Key & k) const
      {
        size_t num = 0;
        iterator it = begin();
        while (it != end())
        {
          num += ((*it).first == k);
          ++it;
        }
        return num;
      }
      std::pair< const_iterator, const_iterator > equal_range (const Key & k) const
      {
        const_iterator it = find(k);
        return std::pair< const_iterator, const_iterator >{it, it};
      }
      std::pair< iterator, iterator > equal_range (const Key & k)
      {
        iterator it = find(k);
        return std::pair< iterator, iterator >{it, it};
      }

    private:
      node * headNode_;
      size_t size_;
      Compare comp;

      node * findBase(const Key & k)
      {
        node * nodeNow = headNode_;
        while ((nodeNow->data.first) != k)
        {
          if (comp((nodeNow->data.first), k))
          {
            nodeNow = (nodeNow->right);
          }
          else
          {
            nodeNow = (nodeNow->left);
          }
          if (nodeNow == nullptr)
          {
            return headNode_;
          }
        }
        return nodeNow;
      }
  };
}

#endif
