#include "collection_commands.hpp"
#include <iostream>
#include <fstream>
#include <limits>
#include "list.hpp"
#include "string_format.hpp"
#include "dictionary_record.hpp"
#include "number_format.hpp"


void erohin::addTextCommand(texts_source & text_context, std::istream & input, std::ostream &)
{
  std::string text_name[2];
  input >> text_name[0] >> text_name[1];
  std::fstream file(text_name[1], std::fstream::in);
  file.close();
  if (!file)
  {
    throw std::runtime_error("addtext: cannot read the file");
  }
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
  text_context.erase(found_iter);
}

namespace erohin
{
  bool isNewDictionary(const collection & dict_context, const std::string & new_dict_name);
  void createDictionary(Dictionary & dict, const std::string & file_name);
}

void erohin::createDictCommand(collection & dict_context, const texts_source & text_context, std::istream & input, std::ostream &)
{
  std::string name[2];
  input >> name[0] >> name[1];
  if (!isNewDictionary(dict_context, name[0]))
  {
    throw std::logic_error("creadict: dictionary has already existed");
  }
  Dictionary temp_dict;
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
  void printDictionary(const Dictionary & dict, std::ostream & output, numformat_t numformat);
}

void erohin::printCommand(const collection & dict_context, std::istream & input, std::ostream & output, numformat_t numformat)
{
  std::string dict_name;
  input >> dict_name;
  const Dictionary & dict = dict_context.at(dict_name);
  printDictionary(dict, output, numformat);
}

void erohin::countCommand(const collection & dict_context, std::istream & input, std::ostream & output)
{
  std::string dict_name;
  input >> dict_name;
  const Dictionary & dict = dict_context.at(dict_name);
  size_t total_number = detail::countTotalNumber(dict.records);
  size_t unique_number = dict.records.size();
  output << "words: " << total_number << "; unique words: " << unique_number << "\n";
}

namespace erohin
{
  using sorted_dictionary = RedBlackTree< size_t, List< std::string > >;
  void createSortedDictionary(sorted_dictionary & sorted_dict, const Dictionary & source);
  void printSortedDictionary(const sorted_dictionary & sorted_dict, std::ostream & output, numformat_t numformat);
}

void erohin::sortCommand(const collection & dict_context, std::istream & input, std::ostream & output, numformat_t numformat)
{
  std::string dict_name;
  input >> dict_name;
  const Dictionary & dict = dict_context.at(dict_name);
  sorted_dictionary sorted_dict;
  createSortedDictionary(sorted_dict, dict);
  printSortedDictionary(sorted_dict, output, numformat);
}

void erohin::findCommand(const collection & dict_context, std::istream & input, std::ostream & output, numformat_t numformat)
{
  std::string name[2];
  input >> name[0] >> name[1];
  const Dictionary & dict = dict_context.at(name[0]);
  auto found_iter = dict.records.find(name[1]);
  if (found_iter != dict.records.cend())
  {
    size_t total_number = detail::countTotalNumber(dict.records);
    output << FormattedRecord(Record(*found_iter), total_number, numformat) << "\n";
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
  if (!input || !num || !isNewDictionary(dict_context, dict_name[0]))
  {
    throw std::logic_error("top: wrong argument input");
  }
  const Dictionary & dict = dict_context.at(dict_name[1]);
  sorted_dictionary sorted_dict;
  createSortedDictionary(sorted_dict, dict);
  Dictionary temp_dict;
  detail::insertNumDifferentRecords(temp_dict.records, num, sorted_dict.crbegin(), sorted_dict.crend());
  dict_context[dict_name[0]] = std::move(temp_dict);
}

void erohin::bottomCommand(collection & dict_context, std::istream & input, std::ostream &)
{
  std::string dict_name[2];
  size_t num = 0;
  input >> dict_name[0] >> dict_name[1] >> num;
  if (!input || !num || !isNewDictionary(dict_context, dict_name[0]))
  {
    throw std::logic_error("bottom: wrong argument input");
  }
  const Dictionary & dict = dict_context.at(dict_name[1]);
  sorted_dictionary sorted_dict;
  createSortedDictionary(sorted_dict, dict);
  Dictionary temp_dict;
  detail::insertNumDifferentRecords(temp_dict.records, num, sorted_dict.cbegin(), sorted_dict.cend());
  dict_context[dict_name[0]] = std::move(temp_dict);
}

namespace erohin
{
  using record_pair = std::pair< std::string, size_t >;
  using dict_pair = std::pair< Dictionary, Dictionary >;
  record_pair createDifferenceRecord(const record_pair & pair, const Dictionary & dict);
  void makeDifference(Dictionary & dict, const dict_pair & source);
}

void erohin::differCommand(collection & dict_context, std::istream & input, std::ostream &)
{
  std::string dict_name[3];
  input >> dict_name[0] >> dict_name[1] >> dict_name[2];
  if (!isNewDictionary(dict_context, dict_name[0]))
  {
    throw std::logic_error("differ: dictionary has already existed");
  }
  const Dictionary & first_dict = dict_context.at(dict_name[1]);
  const Dictionary & second_dict = dict_context.at(dict_name[2]);
  Dictionary temp_dict;
  makeDifference(temp_dict, std::make_pair(first_dict, second_dict));
  if (temp_dict.records.empty())
  {
    throw std::underflow_error("differ: empty difference of two dictionaries");
  }
  dict_context[dict_name[0]] = std::move(temp_dict);
}

namespace erohin
{
  void makeUnion(Dictionary & dict, const dict_pair & source);
}

void erohin::uniteCommand(collection & dict_context, std::istream & input, std::ostream &)
{
  std::string dict_name[3];
  input >> dict_name[0] >> dict_name[1] >> dict_name[2];
  if (!isNewDictionary(dict_context, dict_name[0]))
  {
    throw std::logic_error("unite: dictionary has already existed");
  }
  const Dictionary & first_dict = dict_context.at(dict_name[1]);
  const Dictionary & second_dict = dict_context.at(dict_name[2]);
  Dictionary temp_dict;
  makeUnion(temp_dict, std::make_pair(first_dict, second_dict));
  dict_context[dict_name[0]] = std::move(temp_dict);
}

namespace erohin
{
  void makeIntersection(Dictionary & dict, const dict_pair & source);
}

void erohin::intersectCommand(collection & dict_context, std::istream & input, std::ostream &)
{
  std::string dict_name[3];
  input >> dict_name[0] >> dict_name[1] >> dict_name[2];
  if (!isNewDictionary(dict_context, dict_name[0]))
  {
    throw std::logic_error("intersect: dictionary has already existed");
  }
  const Dictionary & first_dict = dict_context.at(dict_name[1]);
  const Dictionary & second_dict = dict_context.at(dict_name[2]);
  Dictionary temp_dict;
  makeIntersection(temp_dict, std::make_pair(first_dict, second_dict));
  if (temp_dict.records.empty())
  {
    throw std::underflow_error("differ: empty difference of two dictionaries");
  }
  dict_context[dict_name[0]] = std::move(temp_dict);
}

bool erohin::isNewDictionary(const collection & dict_context, const std::string & new_dict_name)
{
  auto found_iter = dict_context.find(new_dict_name);
  return found_iter == dict_context.cend();
}

void erohin::createDictionary(Dictionary & dict, const std::string & file_name)
{
  std::fstream file;
  file.open(file_name);
  if (!file)
  {
    throw std::runtime_error("File reading error");
  }
  Dictionary temp_dict;
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
      ++temp_dict.records[word];
    }
    file >> WordInContextFormat{ word, max_size };
  }
  dict = std::move(temp_dict);
  file.close();
}

void erohin::printDictionary(const Dictionary & dict, std::ostream & output, numformat_t numformat)
{
  size_t total_number = detail::countTotalNumber(dict.records);
  auto begin = dict.records.cbegin();
  auto end = dict.records.cend();
  while (begin != end)
  {
    output << FormattedRecord(*begin, total_number, numformat) << "\n";
    ++begin;
  }
}

void erohin::createSortedDictionary(sorted_dictionary & sorted_dict, const Dictionary & source)
{
  auto begin = source.records.cbegin();
  auto end = source.records.cend();
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

erohin::record_pair erohin::createDifferenceRecord(const record_pair & pair, const Dictionary & dict)
{
  auto found_iter = dict.records.find(pair.first);
  size_t num = found_iter != dict.records.cend() ? found_iter->second : 0;
  return std::make_pair(pair.first, pair.second - num);
}

void erohin::makeDifference(Dictionary & dict, const dict_pair & source)
{
  auto begin = source.first.records.cbegin();
  auto end = source.first.records.cend();
  while (begin != end)
  {
    dict.records.insert(createDifferenceRecord(*begin, source.second));
    ++begin;
  }
}

void erohin::makeUnion(Dictionary & dict, const dict_pair & source)
{
  auto begin = source.first.records.cbegin();
  auto end = source.first.records.cend();
  while (begin != end)
  {
    dict.records[begin->first] += begin->second;
    ++begin;
  }
  begin = source.second.records.cbegin();
  end = source.second.records.cend();
  while (begin != end)
  {
    auto iter_pair = dict.records.insert(*begin);
    if (!iter_pair.second)
    {
      dict.records[begin->first] += begin->second;
    }
    ++begin;
  }
}

void erohin::makeIntersection(Dictionary & dict, const dict_pair & source)
{
  auto begin = source.first.records.cbegin();
  auto end = source.first.records.cend();
  while (begin != end)
  {
    auto found_iter = source.second.records.find(begin->first);
    if (found_iter != source.second.records.cend())
    {
      dict.records.insert(std::make_pair(begin->first, std::min(begin->second, found_iter->second)));
    }
    ++begin;
  }
}
