#ifndef COLLECTION_COMMANDS_HPP
#define COLLECTION_COMMANDS_HPP

#include <iostream>
#include <string>
#include "red_black_tree.hpp"
#include "input_output_collection.hpp"
#include "number_format.hpp"

namespace erohin
{
  using texts_source = RedBlackTree< std::string, std::string >;

  void addTextCommand(texts_source & text_context, std::istream & input, std::ostream &);
  void removeTextCommand(texts_source & text_context, std::istream & input, std::ostream &);
  void createDictCommand(collection & dict_context, const texts_source & text_context, std::istream & input, std::ostream &);
  void removeDictCommand(collection & dict_context, std::istream & input, std::ostream &);
  void printCommand(const collection & dict_context, std::istream & input, std::ostream & output, numformat_t numformat);
  void countCommand(const collection & dict_context, std::istream & input, std::ostream & output);
  void sortCommand(const collection & dict_context, std::istream & input, std::ostream & output, numformat_t numformat);
  void findCommand(const collection & dict_context, std::istream & input, std::ostream & output, numformat_t numformat);
  void topCommand(collection & dict_context, std::istream & input, std::ostream &);
  void bottomCommand(collection & dict_context, std::istream & input, std::ostream &);
  void differCommand(collection & dict_context, std::istream & input, std::ostream &);
  void uniteCommand(collection & dict_context, std::istream & input, std::ostream &);
  void intersectCommand(collection & dict_context, std::istream & input, std::ostream &);

  namespace detail
  {
    template< class T1, class T2 >
    size_t getNumber(const std::pair< T1, T2 > & pair)
    {
      return std::get< size_t >(pair);
    }

    template< class T1, class T2 >
    size_t countTotalNumber(const RedBlackTree< T1, T2 > & dict)
    {
      size_t total_number = 0;
      auto begin = dict.cbegin();
      auto end = dict.cend();
      while (begin != end)
      {
        total_number += getNumber< T1, T2 >(*(begin++));
      }
      return total_number;
    }

    template< class Dict, class DictIter >
    void insertNumDifferentRecords(Dict & dict, size_t count, DictIter begin, DictIter end)
    {
      size_t current_count = 0;
      while (begin != end && current_count < count)
      {
        auto list_begin = begin->second.cbegin();
        auto list_end = begin->second.cend();
        while (list_begin != list_end)
        {
          dict.insert(std::make_pair(*list_begin, begin->first));
          ++list_begin;
        }
        ++begin;
        ++current_count;
      }
    }
  }
}

#endif
