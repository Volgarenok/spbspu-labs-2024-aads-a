#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

template<typename Key, typename Value, typename Compare = std::less<Key>>
class BinarySearchTree {
private:
    struct Node {
        Key key;
        Value value;
        Node* left;
        Node* right;

        Node(const Key& k, const Value& v) : key(k), value(v), left(nullptr), right(nullptr) {}
    };

    Node* root;
    Compare compare;

public:
    BinarySearchTree() : root(nullptr) {}

    void push(const Key& k, const Value& v) {
        root = push(root, k, v);
    }

    Value get(const Key& k) const {
        Node* node = find(root, k);
        return (node != nullptr) ? node->value : Value();
    }

    Value drop(const Key& k) {
        Value result;
        root = drop(root, k, result);
        return result;
    }

    void print() const {
        print(root);
    }

private:
    Node* push(Node* node, const Key& k, const Value& v) {
        if (node == nullptr)
            return new Node(k, v);
        
        if (compare(k, node->key))
            node->left = push(node->left, k, v);
        else if (compare(node->key, k))
            node->right = push(node->right, k, v);
        else
            node->value = v;
        
        return node;
    }

    Node* find(Node* node, const Key& k) const {
        if (node == nullptr || k == node->key)
            return node;
        
        if (compare(k, node->key))
            return find(node->left, k);
        
        return find(node->right, k);
    }

    Node* drop(Node* node, const Key& k, Value& result) {
        if (node == nullptr)
            return nullptr;

        if (compare(k, node->key))
            node->left = drop(node->left, k, result);
        else if (compare(node->key, k))
            node->right = drop(node->right, k, result);
        else {
            result = node->value;
            if (node->left == nullptr) {
                Node* rightChild = node->right;
                delete node;
                return rightChild;
            }
            if (node->right == nullptr) {
                Node* leftChild = node->left;
                delete node;
                return leftChild;
            }
            Node* minRight = findMin(node->right);
            node->key = minRight->key;
            node->value = minRight->value;
            node->right = drop(node->right, minRight->key, result);
        }
        return node;
    }

    Node* findMin(Node* node) const {
        if (node == nullptr)
            return nullptr;
        
        while (node->left != nullptr)
            node = node->left;
        
        return node;
    }

    void print(Node* node) const {
        if (node == nullptr)
            return;
        
        print(node->left);
        std::cout << node->key << " " << node->value << " ";
        print(node->right);
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " filename\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << argv[1] << "\n";
        return 1;
    }

    std::map<std::string, BinarySearchTree<int, std::string>> dictionaries;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty())
            continue;
        
        std::istringstream iss(line);
        std::string dataset;
        iss >> dataset;
        BinarySearchTree<int, std::string>& dictionary = dictionaries[dataset];

        int key;
        std::string value;
        while (iss >> key >> value) {
            dictionary.push(key, value);
        }
    }

    std::string command;
    while (std::cin >> command) {
        if (command == "print") {
            std::string dataset;
            std::cin >> dataset;
            auto it = dictionaries.find(dataset);
            if (it != dictionaries.end()) {
                it->second.print();
                std::cout << std::endl;
            } else {
                std::cout << "<EMPTY>" << std::endl;
            }
        } else if (command == "complement" || command == "intersect" || command == "union") {
            std::string newdataset, dataset1, dataset2;
            std::cin >> newdataset >> dataset1 >> dataset2;
            auto it1 = dictionaries.find(dataset1);
            auto it2 = dictionaries.find(dataset2);
            if (it1 != dictionaries.end() && it2 != dictionaries.end()) {
                BinarySearchTree<int, std::string> result;
                if (command == "complement") {
                    // Complement operation
                    for (auto& pair : it1->second) {
                        if (!it2->second.get(pair.first)) {
                            result.push(pair.first, pair.second);
                        }
                    }
                } else if (command == "intersect") {
                    // Intersection operation
                    for (auto& pair : it1->second) {
                        if (it2->second.get(pair.first)) {
                            result.push(pair.first, pair.second);
                        }
                    }
                } else if (command == "union") {
                    // Union operation
                    for (auto& pair : it1->second) {
                        result.push(pair.first, pair.second);
                    }
                    for (auto& pair : it2->second) {
                        if (!result.get(pair.first)) {
                            result.push(pair.first, pair.second);
                        }
                    }
                }
                dictionaries[newdataset] = result;
            } else {
                std::cout << "<INVALID COMMAND>" << std::endl;
            }
        } else {
            std::cout << "<INVALID COMMAND>" << std::endl;
        }
    }

    return 0;
}

