#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <iostream>
#include <iomanip>

template <class T>

class AVLTree
{
public:
  AVLTree():
    root_(nullptr) {}

  AVLTree(const AVLTree< T >& other)
  {
    root_ = deepCopy(other.root_);
  }

  AVLTree(AVLTree< T >&& other) noexcept:
    root_(other.root_)
  {
    other.root_ = nullptr;
  }

  ~AVLTree()
  {
    clear();
  }

  void clear()
  {
    removeSubTree(root_);
    root_ = nullptr;
  }

  void insert(const T & value)
  {
    root_ = insertRecursive(root_, value);
  }

  void remove(const T & value)
  {
    root_ = removeRecursive(root_, value);
  }

  void addElements(const AVLTree< T >& other)
  {
    addElementsRecursive(other.root_);
  }

  void removeElements(const AVLTree< T >& other)
  {
    removeElementsRecursive(root_, other.root_);
  }

  bool contains(const T & value) const
  {
    return containsRecursive(root_, value);
  }

  T search(const T & value)
  {
    return searchRecursive(root_, value)->data;
  }

  size_t getCountElements() const
  {
    return getCountElementsRecursive(root_);
  }

  size_t getHeight()
  {
    return getHeight(root_);
  }

  AVLTree< T >& operator=(const AVLTree< T >& other)
  {
    if (this != &other)
    {
      removeSubTree(root_);
      root_ = deepCopy(other.root_);
    }
    return *this;
  }

  friend std::ostream& operator<<(std::ostream& os, const AVLTree< T >& tree)
  {
    os << tree.root_;
    return os;
  }

  void display() const
  {
    std::cout << *this << getCountElements() << "\n";
  }

private:
  struct Node
  {
    T data_;
    Node * left_;
    Node * right_;
    size_t height_;

    Node():
      left_(nullptr), right_(nullptr), height_(1) {}
    Node(const T & data):
      data_(data), left_(nullptr), right_(nullptr), height_(1) {}
  };

  Node * root_;

  Node * deepCopy(Node * node)
  {
    if (node == nullptr)
    {
      return nullptr;
    }
    else
    {
      Node * newNode = new Node;
      newNode->data_ = node->data_;
      newNode->left_ = deepCopy(node->left_);
      newNode->right_ = deepCopy(node->right_);
      newNode->height_ = node->height_;
      return newNode;
    }
  }

  Node * insertRecursive(Node * node, const T & value)
  {
    if (node == nullptr)
    {
      return new Node(value);
    }

    if (value < node->data_)
    {
      if (node->left_ == nullptr)
      {
        node->left_ = new Node(value);
      }
      else
      {
        node->left_ = insertRecursive(node->left_, value);
      }
    }
    else if (value > node->data_)
    {
      if (node->right_ == nullptr)
      {
        node->right_ = new Node(value);
      }
      else
      {
        node->right_ = insertRecursive(node->right_, value);
      }
    }
    else
    {
      throw std::invalid_argument("Inserting a duplicate into the AVLTree is not allowed");
    }

    node->height_ = 1 + std::max(getHeight(node->left_), getHeight(node->right_));

    size_t balance = getBalance(node);

    if (balance > 1 && node->left_ && value < node->left_->data_)
    {
      return rightRotate(node);
    }
    if (balance < -1 && node->right_ && value > node->right_->data_)
    {
      return leftRotate(node);
    }
    if (balance > 1 && node->left_ && value > node->left_->data_)
    {
      if (node->left_ && node->left_->left_ && value > node->left_->left_->data_)
      {
        node->left_ = leftRotate(node->left_);
      }
      return rightRotate(node);
    }
    if (balance < -1 && node->right_ && value < node->right_->data_)
    {
      if (node->right_ && node->right_->right_ && value < node->right_->right_->data_)
      {
        node->right_ = rightRotate(node->right_);
      }
      return leftRotate(node);
    }

    return node;
  }

  Node * removeRecursive(Node * node, const T & value)
  {
    if (node == nullptr)
    {
      return node;
    }

    if (value < node->data_)
    {
      node->left_ = removeRecursive(node->left_, value);
    }
    else if (value > node->data_)
    {
      node->right_ = removeRecursive(node->right_, value);
    }
    else
    {
      if (node->left_ == nullptr)
      {
        Node * temp = node->right_;
        delete node;
        return temp;
      }
      else if (node->right_ == nullptr)
      {
        Node * temp = node->left_;
        delete node;
        return temp;
      }

      Node * temp = getMinValueNode(node->right_);
      node->data_ = temp->data_;
      node->right_ = removeRecursive(node->right_, temp->data_);
    }

    node->height_ = 1 + std::max(getHeight(node->left_), getHeight(node->right_));

    size_t balance = getBalance(node);

    if (balance > 1 && getBalance(node->left_) >= 0)
    {
      return rightRotate(node);
    }
    if (balance > 1 && getBalance(node->left_) < 0)
    {
      node->left_ = leftRotate(node->left_);
      return rightRotate(node);
    }
    if (balance < -1 && getBalance(node->right_) <= 0)
    {
      return leftRotate(node);
    }
    if (balance < -1 && getBalance(node->right_) > 0)
    {
      node->right_ = rightRotate(node->right_);
      return leftRotate(node);
    }

    return node;
  }

  void addElementsRecursive(Node * node)
  {
    if (node != nullptr)
    {
      insert(node->data_);
      addElementsRecursive(node->left_);
      addElementsRecursive(node->right_);
    }
  }

  void removeElementsRecursive(Node * thisNode, Node * otherNode)
  {
    if (otherNode != nullptr)
    {
      remove(otherNode->data_);
      removeElementsRecursive(thisNode, otherNode->left_);
      removeElementsRecursive(thisNode, otherNode->right_);
    }
  }

  size_t getCountElementsRecursive(Node * node) const
  {
    if (node == nullptr)
    {
      return 0;
    }
    return 1 + getCountElementsRecursive(node->left_) + getCountElementsRecursive(node->right_);
  }

  size_t getHeight(Node * node) const
  {
    if (node == nullptr)
    {
      return 0;
    }
    return node->height_;
  }

  size_t getBalance(Node * node) const
  {
    if (node == nullptr)
    {
      return 0;
    }
    return getHeight(node->left_) - getHeight(node->right_);
  }

  Node * rightRotate(Node * node)
  {
    if (node == nullptr || node->left_ == nullptr || node->left_->right_ == nullptr)
    {
      return node;
    }

    Node * nextLeftNode = node->left_;
    Node * newRightSubtree = nextLeftNode->right_;

    nextLeftNode->right_ = node;
    node->left_ = newRightSubtree;

    node->height_ = 1 + std::max(getHeight(node->left_), getHeight(node->right_));
    nextLeftNode->height_ = 1 + std::max(getHeight(nextLeftNode->left_), getHeight(nextLeftNode->right_));

    return nextLeftNode;
  }

  Node * leftRotate(Node * node)
  {
    if (node == nullptr || node->right_ == nullptr || node->right_->left_ == nullptr)
    {
      return node;
    }

    Node * nextRightNode = node->right_;
    Node * newLeftSubtree = nextRightNode->left_;

    nextRightNode->left_ = node;
    node->right_ = newLeftSubtree;

    node->height_ = 1 + std::max(getHeight(node->left_), getHeight(node->right_));
    nextRightNode->height_ = 1 + std::max(getHeight(nextRightNode->left_), getHeight(nextRightNode->right_));

    return nextRightNode;
  }

  void removeSubTree(Node * node)
  {
    if (node != nullptr)
    {
      removeSubTree(node->left_);
      removeSubTree(node->right_);
      delete node;
    }
  }

  Node * searchRecursive(Node * node, const T & value)
  {
    if (node == nullptr)
    {
      throw std::invalid_argument("There is no specified element");
    }
    if (node->data_ == value)
    {
      return node;
    }
    if (value < node->data_)
    {
      return searchRecursive(node->left_, value);
    }
    return searchRecursive(node->right_, value);
  }

  Node * getMinValueNode(Node * node) const
  {
    Node * current = node;

    while (current && current->left_ != nullptr)
    {
      current = current->left_;
    }

    return current;
  }

  bool containsRecursive(Node * node, const T & value) const
  {
    if (node == nullptr)
    {
      return false;
    }

    if (value < node->data_)
    {
      return containsRecursive(node->left_, value);
    }
    else if (value > node->data_)
    {
      return containsRecursive(node->right_, value);
    }
    else
    {
      return true;
    }
  }
};
#endif
