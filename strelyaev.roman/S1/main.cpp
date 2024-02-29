#include "list.hpp"
#include <iostream>

int main()
{
  strelyaev::Node< int >* head = nullptr;
  head = new strelyaev::Node< int >{0};
  strelyaev::Node< int >* tail = head;
  strelyaev::List< int >* test_list = new strelyaev::List< int >{head, tail};
  for (int i = 1; i < 10; i++)
  {
    strelyaev::Node< int >* temp_node = new strelyaev::Node< int >{i};
    test_list->tail_->next_ = temp_node;
    temp_node->prev_ = tail;
    test_list->tail_ = temp_node;
  }
  int i  =0;
  while (test_list->head_->next_)
  {
    std::cout << "Node " << i << ":\n"
              << "Value: " << test_list->head_->value_ << "\n"
              << "Have previous?: ";
    if (test_list->head_->prev_)
    {
      std::cout << "YES\n";
    }
    else
    {
      std::cout << "NO\n";
    }
    std::cout << "Have next?: ";
    if (test_list->head_->next_)
    {
      std::cout << "YES\n";
    }
    else
    {
      std::cout << "NO\n";
    }
    i++;
    test_list->head_ = test_list->head_->next_;
    std::cout << "=====================================================================\n";
  }
}
