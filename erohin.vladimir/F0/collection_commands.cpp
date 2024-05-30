#include "collection_commands.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <limits>
#include <iterator>
#include "list.hpp"
#include "format.hpp"
#include "dictionary_record.hpp"
#include "number_format.hpp"

void erohin::addTextCommand(texts_source & text_context, std::istream & input, std::ostream &)
{
  std::string text_name[2];
  input >> text_name[0] >> text_name[1];
  auto iter_pair = text_context.insert(std::make_pair(text_name[0], text_name[1]));
  if (!iter_pair.second)
  {
    throw std::logic_error("addtext: bad insertion into texts source");
  }
}

void erohin::removeTextCommand(texts_source & text_context, std::istream & input, std::ostream &)
{
  std::string text_name;
  input >> text_name;
  auto found_iter = text_context.find(text_name);
  if (found_iter == text_context.end())
  {
    throw std::logic_error("removetext: bad removal from texts source");
  }
  text_context.erase(text_name);
}

namespace erohin
{
  bool isNewDictionary(const collection & dict_context, const std::string & new_dict_name);
  void createDictionary(dictionary & dict, const std::string & file_name);
}

void erohin::createDictCommand(collection & dict_context, const texts_source & text_context, std::istream & input, std::ostream &)
{
  std::string name[2];
  input >> name[0] >> name[1];
  if (!isNewDictionary(dict_context, name[0]))
  {
    throw std::logic_error("creadict: dictionary has already existed");
  }
  dictionary temp_dict;
  createDictionary(temp_dict, text_context.at(name[1]));
  dict_context[name[0]] = std::move(temp_dict);
}

void erohin::removeDictCommand(collection & dict_context, std::istream & input, std::ostream &)
{
  std::string dict_name;
  input >> dict_name;
  auto found_iter = dict_context.find(dict_name);
  if (found_iter == dict_context.end())
  {
    throw std::logic_error("removetext: bad removal from dictionary collection");
  }
  dict_context.erase(found_iter);
}

namespace erohin
{
  void printDictionary(const dictionary & dict, std::ostream & output, numformat_t numformat);
}

void erohin::printCommand(const collection & dict_context, std::istream & input, std::ostream & output, numformat_t numformat)
{
  std::string dict_name;
  input >> dict_name;
  const dictionary & dict = dict_context.at(dict_name);
  printDictionary(dict, output, numformat);
}

void erohin::countCommand(const collection & dict_context, std::istream & input, std::ostream & output)
{
  std::string dict_name;
  input >> dict_name;
  const dictionary & dict = dict_context.at(dict_name);
  size_t total_number = detail::countTotalNumber(dict);
  size_t unique_number = dict.size();
  output << "words: " << total_number << "; unique words: " << unique_number << "\n";
}

namespace erohin
{
  using sorted_dictionary = RedBlackTree< size_t, List< std::string > >;
  void createSortedDictionary(sorted_dictionary & sorted_dict, const dictionary & source);
  void printSortedDictionary(const sorted_dictionary & sorted_dict, std::ostream & output, numformat_t numformat);
}

void erohin::sortCommand(const collection & dict_context, std::istream & input, std::ostream & output, numformat_t numformat)
{
  std::string dict_name;
  input >> dict_name;
  const dictionary & dict = dict_context.at(dict_name);
  sorted_dictionary sorted_dict;
  createSortedDictionary(sorted_dict, dict);
  printSortedDictionary(sorted_dict, output, numformat);
}

void erohin::findCommand(const collection & dict_context, std::istream & input, std::ostream & output, numformat_t numformat)
{
  std::string name[2];
  input >> name[0] >> name[1];
  const dictionary & dict = dict_context.at(name[0]);
  auto found_iter = dict.find(name[1]);
  if (found_iter != dict.cend())
  {
    size_t total_number = detail::countTotalNumber(dict);
    output << createFormattedRecord(Record(*found_iter), total_number, numformat) << "\n";
  }
  else
  {
    throw std::logic_error("find: cannot find word");
  }
}

void erohin::topCommand(collection & dict_context, std::istream & input, std::ostream &)
{
  std::string dict_name[2];
  size_t num = 0;
  input >> dict_name[0] >> dict_name[1] >> num;
  if (!input || !isNewDictionary(dict_context, dict_name[0]))
  {
    throw std::logic_error("top: wrong argument input");
  }
  const dictionary & dict = dict_context.at(dict_name[1]);
  sorted_dictionary sorted_dict;
  createSortedDictionary(sorted_dict, dict);
  dictionary temp_dict;
  detail::insertNumRecords(temp_dict, num, sorted_dict.crbegin(), sorted_dict.crend());
  dict_context[dict_name[0]] = std::move(temp_dict);
}

void erohin::bottomCommand(collection & dict_context, std::istream & input, std::ostream &)
{
  std::string dict_name[2];
  size_t num = 0;
  input >> dict_name[0] >> dict_name[1] >> num;
  if (!input || !isNewDictionary(dict_context, dict_name[0]))
  {
    throw std::logic_error("bottom: wrong argument input");
  }
  const dictionary & dict = dict_context.at(dict_name[1]);
  sorted_dictionary sorted_dict;
  createSortedDictionary(sorted_dict, dict);
  dictionary temp_dict;
  detail::insertNumRecords(temp_dict, num, sorted_dict.cbegin(), sorted_dict.cend());
  dict_context[dict_name[0]] = std::move(temp_dict);
}

namespace erohin
{
  record_pair makeDifference(const record_pair & pair, const dictionary & dict);
}

void erohin::differCommand(collection & dict_context, std::istream & input, std::ostream &)
{
  std::string dict_name[3];
  input >> dict_name[0] >> dict_name[1] >> dict_name[2];
  if (!isNewDictionary(dict_context, dict_name[0]))
  {
    throw std::logic_error("differ: dictionary has already existed");
  }
  const dictionary & first_dict = dict_context.at(dict_name[1]);
  const dictionary & second_dict = dict_context.at(dict_name[2]);
  dictionary temp_dict;
  auto begin = first_dict.cbegin();
  auto end = first_dict.cend();
  while (begin != end)
  {
    temp_dict.insert(makeDifference(*begin, second_dict));
    ++begin;
  }
  if (temp_dict.empty())
  {
    throw std::underflow_error("differ: Empty difference of two dictionaries");
  }
  dict_context[dict_name[0]] = std::move(temp_dict);
}

void erohin::uniteCommand(collection & dict_context, std::istream & input, std::ostream &)
{
  std::string dict_name[3];
  input >> dict_name[0] >> dict_name[1] >> dict_name[2];
  if (!isNewDictionary(dict_context, dict_name[0]))
  {
    throw std::logic_error("unite: dictionary has already existed");
  }
  const dictionary & first_dict = dict_context.at(dict_name[1]);
  const dictionary & second_dict = dict_context.at(dict_name[2]);
  dictionary temp_dict;
  auto begin = first_dict.cbegin();
  auto end = first_dict.cend();
  while (begin != end)
  {
    temp_dict[begin->first] += begin->second;
    ++begin;
  }
  begin = second_dict.cbegin();
  end = second_dict.cend();
  while (begin != end)
  {
    auto iter_pair = temp_dict.insert(*begin);
    if (!iter_pair.second)
    {
      temp_dict[begin->first] += begin->second;
    }
    ++begin;
  }
  if (temp_dict.empty())
  {
    throw std::underflow_error("unite: Empty union of two dictionaries");
  }
  dict_context[dict_name[0]] = std::move(temp_dict);
}

void erohin::intersectCommand(collection & dict_context, std::istream & input, std::ostream &)
{
  std::string dict_name[3];
  input >> dict_name[0] >> dict_name[1] >> dict_name[2];
  if (!isNewDictionary(dict_context, dict_name[0]))
  {
    throw std::logic_error("intersect: dictionary has already existed");
  }
  const dictionary & first_dict = dict_context.at(dict_name[1]);
  const dictionary & second_dict = dict_context.at(dict_name[2]);
  dictionary temp_dict;
  auto begin = first_dict.cbegin();
  auto end = first_dict.cend();
  while (begin != end)
  {
    auto found_iter = second_dict.find(begin->first);
    if (found_iter != second_dict.cend())
    {
      temp_dict.insert(std::make_pair(begin->first, std::min(begin->second, found_iter->second)));
    }
    ++begin;
  }
  if (temp_dict.empty())
  {
    throw std::underflow_error("differ: Empty difference of two dictionaries");
  }
  dict_context[dict_name[0]] = std::move(temp_dict);
}

bool erohin::isNewDictionary(const collection & dict_context, const std::string & new_dict_name)
{
  auto found_iter = dict_context.find(new_dict_name);
  return found_iter == dict_context.cend();
}

void erohin::createDictionary(dictionary & dict, const std::string & file_name)
{
  std::fstream file;
  file.open(file_name);
  if (!file)
  {
    throw std::runtime_error("File reading error");
  }
  dictionary temp_dict;
  std::string word;
  size_t max_size = std::numeric_limits< size_t >::max();
  file >> WordInContextFormat{ word, max_size };
  while (!file.eof())
  {
    if (file.fail())
    {
      file.clear();
    }
    else
    {
      ++temp_dict[word];
    }
    file >> WordInContextFormat{ word, max_size };
  }
  dict = std::move(temp_dict);
  file.close();
}

void erohin::printDictionary(const dictionary & dict, std::ostream & output, numformat_t numformat)
{
  size_t total_number = detail::countTotalNumber(dict);
  auto begin = dict.cbegin();
  auto end = dict.cend();
  while (begin != end)
  {
    output << FormattedRecord(*begin, total_number, numformat) << "\n";
    ++begin;
  }
}

void erohin::createSortedDictionary(sorted_dictionary & sorted_dict, const dictionary & source)
{
  auto begin = source.cbegin();
  auto end = source.cend();
  sorted_dictionary temp_dict;
  while (begin != end)
  {
    temp_dict[begin->second].push_front(begin->first);
    ++begin;
  }
  auto sort_begin = temp_dict.begin();
  auto sort_end = temp_dict.end();
  while (sort_begin != sort_end)
  {
    sort_begin->second.sort();
    ++sort_begin;
  }
  sorted_dict = std::move(temp_dict);
}

void erohin::printSortedDictionary(const sorted_dictionary & sorted_dict, std::ostream & output, numformat_t numformat)
{
  size_t total_number = detail::countTotalNumber(sorted_dict);
  auto begin = sorted_dict.crbegin();
  auto end = sorted_dict.crend();
  while (begin != end)
  {
    auto list_begin = begin->second.cbegin();
    auto list_end = begin->second.cend();
    while (list_begin != list_end)
    {
      output << FormattedRecord(std::make_pair(*list_begin, begin->first), total_number, numformat) << "\n";
      ++list_begin;
    }
    ++begin;
  }
}

erohin::record_pair erohin::makeDifference(const record_pair & pair, const dictionary & dict)
{
  auto found_iter = dict.find(pair.first);
  size_t num = found_iter != dict.cend() ? found_iter->second : 0;
  return std::make_pair(pair.first, pair.second - num);
}
