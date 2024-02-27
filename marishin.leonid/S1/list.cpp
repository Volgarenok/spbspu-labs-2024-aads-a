#include <iostream>
#include <sstream>
#include <map>

template<typename T>
class List {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& data) : data(data), next(nullptr) {}
    };

    Node* head;
    Node* tail;

public:
    List() : head(nullptr), tail(nullptr) {}

    ~List() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push_back(const T& data) {
        if (!head) {
            head = new Node(data);
            tail = head;
            return;
        }
        tail->next = new Node(data);
        tail = tail->next;
    }

    class Iterator {
    private:
        Node* current;

    public:
        Iterator(Node* node) : current(node) {}

        T& operator*() const {
            return current->data;
        }

        Iterator& operator++() {
            current = current->next;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };

    Iterator begin() const {
        return Iterator(head);
    }

    Iterator end() const {
        return Iterator(nullptr);
    }

    bool empty() const {
        return head == nullptr;
    }

    T front() const {
        return head->data;
    }

    void pop_front() {
        if (!head)
            return;
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    size_t size() const {
        size_t count = 0;
        Node* temp = head;
        while (temp) {
            ++count;
            temp = temp->next;
        }
        return count;
    }
};

int main() {
    std::map<std::string, List<int>> sequences;

    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        std::string name;
        int num;
        iss >> name;
        while (iss >> num) {
            sequences[name].push_back(num);
        }
    }

    if (sequences.empty()) {
        std::cout << "0" << std::endl;
        return 0;
    }

    // Print sequence names
    for (const auto& seq : sequences) {
        std::cout << seq.first << " ";
    }
    std::cout << std::endl;

    // Print sequences
    bool has_elements = true;
    size_t max_size = 0;
    while (has_elements) {
        has_elements = false;
        for (const auto& seq : sequences) {
            auto& list = seq.second;
            if (!list.empty()) {
                std::cout << list.front() << " ";
                list.pop_front();
                has_elements = true;
            }
        }
        std::cout << std::endl;
    }

    // Print sums
    for (const auto& seq : sequences) {
        max_size = std::max(max_size, seq.second.size());
    }
    int* sums = new int[max_size]();
    for (const auto& seq : sequences) {
        size_t i = 0;
        for (int num : seq.second) {
            sums[i] += num;
            ++i;
        }
    }
    for (size_t i = 0; i < max_size; ++i) {
        std::cout << sums[i] << " ";
    }
    std::cout << std::endl;

    delete[] sums;

    return 0;
}
