#include "input_output.hpp"

void vojuck::inputLine(std::istream & in, vojuck::paired_list & vertical)
{
  in >> vertical.first; // импортируем типа название ("first", "second") в первый элемент пары
  size_t number; // сюда будем вводить элементики:3
  while (in >> number)
  {
    vertical.second.push_front(number);
  }
}

void vojuck::inputLists(std::istream & in, vojuck::List< vojuck::paired_list > & result)
{
  while (!in.eof())
  {
    in.clear();
    vojuck::paired_list line;
    inputLine(in, line);
    result.push_front(line);
  }
}
