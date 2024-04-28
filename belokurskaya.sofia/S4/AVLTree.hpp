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
    deleteSubTree(root_);
  }

  void insert(const T& value)
  {
    root_ = insertRecursive(root_, value);
  }

  void pop(const T & value)
  {
    root_ = popRecursive(root_, value);
  }

  bool contains(const T & value) const
  {
    return containsRecursive(root_, value);
  }

  T search(const T & value)
  {
    return searchRecursive(root_, value)->data;
  }

  size_t getHeight()
  {
    return getHeight(root_);
  }

  void print()
  {
    print(root_, 2);
  }

private:
  struct Node
  {
    T data;
    Node * left;
    Node * right;
    size_t height;
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
      newNode->data = node->data;
      newNode->left = deepCopy(node->left);
      newNode->right = deepCopy(node->right);
      newNode->height = node->height;
      return newNode;
    }
  }

  Node * insertRecursive(Node * node, const T & value)
  {
    if (node == nullptr)
    {
      return new Node{ value, nullptr, nullptr, 1 };
    }

    if (value < node->data)
    {
      if (node->left == nullptr)
      {
        node->left = new Node{ value, nullptr, nullptr, 1 };
      }
      else
      {
        node->left = insertRecursive(node->left, value);
      }
    }
    else if (value > node->data)
    {
      if (node->right == nullptr)
      {
        node->right = new Node{ value, nullptr, nullptr, 1 };
      }
      else
      {
        node->right = insertRecursive(node->right, value);
      }
    }
    else
    {
      throw std::invalid_argument("Inserting a duplicate into the AVLTree is not allowed");
    }

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    size_t balance = getBalance(node);

    if (balance > 1 && node->left && value < node->left->data)
    {
      return rightRotate(node);
    }
    if (balance < -1 && node->right && value > node->right->data)
    {
      return leftRotate(node);
    }
    if (balance > 1 && node->left && value > node->left->data)
    {
      if (node->left && node->left->left && value > node->left->left->data)
      {
        node->left = leftRotate(node->left);
      }
      return rightRotate(node);
    }
    if (balance < -1 && node->right && value < node->right->data)
    {
      if (node->right && node->right->right && value < node->right->right->data)
      {
        node->right = rightRotate(node->right);
      }
      return leftRotate(node);
    }

    return node;
  }

  size_t getHeight(Node * node)
  {
    if (node == nullptr)
    {
      return 0;
    }
    return node->height;
  }

  size_t getBalance(Node * node)
  {
    if (node == nullptr)
    {
      return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
  }

  Node * rightRotate(Node * node)
  {
    Node * nextLeftNode = node->left;
    Node * newRightSubtree = nextLeftNode->right;

    nextLeftNode->right = node;
    node->left = newRightSubtree;

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    nextLeftNode->height = 1 + std::max(getHeight(nextLeftNode->left), getHeight(nextLeftNode->right));

    return nextLeftNode;
  }

  Node* leftRotate(Node * node)
  {
    Node * nextRightNode = node->right;
    Node * newLeftSubtree = nextRightNode->left;

    nextRightNode->left = node;
    node->right = newLeftSubtree;

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    nextRightNode->height = 1 + std::max(getHeight(nextRightNode->left), getHeight(nextRightNode->right));

    return nextRightNode;
  }

  Node * searchRecursive(Node * node, const T & value)
  {
    if (node == nullptr || node->data == value)
    {
      return node;
    }
    if (value < node->data)
    {
      return searchRecursive(node->left, value);
    }
    return searchRecursive(node->right, value);
  }

  void deleteSubTree(Node * node)
  {
    if (node)
    {
      deleteSubTree(node->left);
      deleteSubTree(node->right);
      delete node;
    }
  }

  Node * popRecursive(Node * node, const T & value)
  {
    if (node == nullptr)
    {
      return node;
    }

    if (value < node->data)
    {
      node->left = popRecursive(node->left, value);
    }
    else if (value > node->data)
    {
      node->right = popRecursive(node->right, value);
    }
    else
    {
      if (node->left == nullptr)
      {
        Node * temp = node->right;
        delete node;
        return temp;
      }
      else if (node->right == nullptr)
      {
        Node * temp = node->left;
        delete node;
        return temp;
      }

      Node * temp = minValueNode(node->right);
      node->data = temp->data;
      node->right = popRecursive(node->right, temp->data);
    }

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

    if (balance > 1 && getBalance(node->left) >= 0)
    {
      return rightRotate(node);
    }
    if (balance > 1 && getBalance(node->left) < 0)
    {
      node->left = leftRotate(node->left);
      return rightRotate(node);
    }
    if (balance < -1 && getBalance(node->right) <= 0)
    {
      return leftRotate(node);
    }
    if (balance < -1 && getBalance(node->right) > 0)
    {
      node->right = rightRotate(node->right);
      return leftRotate(node);
    }

    return node;
  }

  Node * minValueNode(Node * node)
  {
    Node * current = node;

    while (current && current->left != nullptr)
    {
      current = current->left;
    }

    return current;
  }

  bool containsRecursive(Node * node, const T & value) const
  {
    if (node == nullptr)
    {
      return false;
    }

    if (value < node->data)
    {
      return containsRecursive(node->left, value);
    }
    else if (value > node->data)
    {
      return containsRecursive(node->right, value);
    }
    else
    {
      return true;
    }
  }

  void print(Node * root, int space)
  {
    if (root == nullptr)
    {
      return;
    }

    int count = 5;

    space += count;

    print(root->right, space);

    std::cout << std::setw(space) << root->data << "\n";

    print(root->left, space);
  }
};
#endif
