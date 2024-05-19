#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <queue>
#include <stdexcept>

template<typename Key, typename Value>
class BinarySearchTree {
public:
    struct Node {
        std::pair<Key, Value> key_value;
        Node* left = nullptr;
        Node* right = nullptr;
        Node(const Key& key, const Value& value) : key_value(key, value) {}
    };

    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree() { clear(root); }

    void insert(const Key& key, const Value& value) {
        if (root == nullptr) {
            root = new Node(key, value);
        } else {
            insert(root, key, value);
        }
    }

    template<typename F>
    F traverse_lnr(F f) const {
        if (!root) return f;
        std::stack<Node*> stack;
        Node* current = root;
        while (!stack.empty() || current) {
            if (current) {
                stack.push(current);
                current = current->left;
            } else {
                current = stack.top();
                stack.pop();
                f(current->key_value);
                current = current->right;
            }
        }
        return f;
    }

    template<typename F>
    F traverse_rnl(F f) const {
        if (!root) return f;
        std::stack<Node*> stack;
        Node* current = root;
        while (!stack.empty() || current) {
            if (current) {
                stack.push(current);
                current = current->right;
            } else {
                current = stack.top();
                stack.pop();
                f(current->key_value);
                current = current->left;
            }
        }
        return f;
    }

    template<typename F>
    F traverse_breadth(F f) const {
        if (!root) return f;
        std::queue<Node*> queue;
        queue.push(root);
        while (!queue.empty()) {
            Node* current = queue.front();
            queue.pop();
            f(current->key_value);
            if (current->left) queue.push(current->left);
            if (current->right) queue.push(current->right);
        }
        return f;
    }

private:
    Node* root;

    void insert(Node* node, const Key& key, const Value& value) {
        if (key < node->key_value.first) {
            if (node->left == nullptr) {
                node->left = new Node(key, value);
            } else {
                insert(node->left, key, value);
            }
        } else if (key > node->key_value.first) {
            if (node->right == nullptr) {
                node->right = new Node(key, value);
            } else {
                insert(node->right, key, value);
            }
        }
    }

    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }
};
