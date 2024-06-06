#include <iostream>
namespace vyzhanov
{
    template<typename T>
    struct Node
    {
        T data_;
        Node<T>* next_;
        Node<T>* prev_;
    };

    template<typename T>
    struct List
    {
        List() :head(nullptr), tail(nullptr) {};
        ~List();
        void Add(T data);
        void Show();
        void delElem();
        void fill(T start, T last, T value);
    private:
        Node<T>* head;
        Node<T>* tail;
    };
}
template<typename T>
void vyzhanov::List<T>::Add(T Data)
{
    vyzhanov::Node<T>* newNode = new vyzhanov::Node<T>;
    vyzhanov::Node<T>* start = head;
    if (start != nullptr)
    {
        while (start->next_ != nullptr)
        {
            start = start->next_;
        }
    }
    newNode->data_ = Data;
    newNode->prev_ = newNode->next_;
    newNode->next_ = nullptr;
    if (start != nullptr)
        start->next_ = newNode;
    else
        head = newNode;
    tail = newNode;
}

template<typename T>
void vyzhanov::List<T>::Show()
{
    Node<T>* temp = head;
    while (temp != nullptr)
    {
        std::cout << temp->data_ << " ";
        temp = temp->next_;
    }
    std::cout << "\n";
}

template<typename T>
vyzhanov::List<T>::~List()
{
    while (head)
    {
        vyzhanov::Node<T>* newHead;
        newHead = head->next_;
        delete head;
        head = newHead;
    }
    delete head;
}

template<typename T>
void vyzhanov::List<T>::delElem()
{

}
