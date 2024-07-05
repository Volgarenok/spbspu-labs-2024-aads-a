#ifndef NODE_HPP
#define NODE_HPP
namespace vyzhanov
{
    template<typename T>
    struct Node
    {
        T data_;
        Node<T>* next_;
        Node<T>* prev_;
    };

}
#endif
