#include "cmds.hpp"
#include <stdexcept>
#include <list/list.hpp>
#include <tree/binarySearchTree.hpp>

void strelyaev::addDictionary(std::istream& in, Tree< std::string, Tree< std::string, List< std::string > > >& dictionaries)
{
  std::string name = "";
  in >> name;
  if (dictionaries.find(name) != dictionaries.end())
  {
    throw std::logic_error("<ALREADY EXISTS>");
  }
  Tree< std::string, List< std::string > > new_dict = {};
  dictionaries[name] = new_dict;
}

void strelyaev::deleteDictionary(std::istream& in,
    Tree< std::string, Tree< std::string, List< std::string > > >& dictionaries)
{
  std::string name = "";
  in >> name;
  if (dictionaries.find(name) == dictionaries.end())
  {
    throw std::logic_error("<BOOK NOT FOUND>");
  }
  dictionaries.erase(name);
}

void strelyaev::addWord(std::istream& in,
    Tree< std::string, Tree< std::string, List< std::string > > >& dictionaries)
{
  std::string name = "";
  in >> name;
  if (dictionaries.find(name) == dictionaries.end())
  {
    throw std::logic_error("<BOOK NOT FOUND>");
  }
  Tree< std::string, List< std::string > >& needed_dict = dictionaries[name];
  std::string word = "";
  std::string translation = "";
  in >> word >> translation;
  needed_dict[word].push_back(translation);
}

void strelyaev::removeWord(std::istream& in,
    Tree< std::string, Tree< std::string, List< std::string > > >& dictionaries)
{
  std::string name = "";
  in >> name;
  if (dictionaries.find(name) == dictionaries.end())
  {
    throw std::logic_error("<BOOK NOT FOUND>");
  }
  Tree< std::string, List< std::string > >& needed_dict = dictionaries[name];
  std::string word = "";
  in >> word;
  if (needed_dict.find(word) == needed_dict.end())
  {
    throw std::logic_error("<WORD NOT FOUND>");
  }
  needed_dict.erase(word);
}

void strelyaev::translate(std::ostream& out,
    std::istream& in,
    const Tree< std::string, Tree< std::string, List< std::string > > >& dictionaries)
{
  std::string name = "";
  std::string eng_word = "";
  in >> name >> eng_word;
  if (dictionaries.find(name) == dictionaries.cend())
  {
    throw std::logic_error("<BOOK NOT FOUND>");
  }
  const Tree< std::string, List< std::string > >& needed_dict = dictionaries.at(name);

  if (needed_dict.find(eng_word) == needed_dict.cend())
  {
    throw std::logic_error("<WORD NOT FOUND>");
  }
  const List< std::string > translations = needed_dict.at(eng_word);
  out << eng_word << " ";
  for (auto it = translations.cbegin(); it != translations.cend(); ++it)
  {
    out << *it << " ";
  }
  out << "\n";
  return;
}

void strelyaev::mergeDictionaries(std::istream& in,
    Tree< std::string, Tree< std::string, List< std::string > > >& dictionaries)
{
  std::string first_name, second_name;
  in >> first_name >> second_name;

  if (dictionaries.find(first_name) == dictionaries.end() || dictionaries.find(second_name) == dictionaries.end())
  {
    throw std::logic_error("<BOOK NOT FOUND>");
  }

  Tree< std::string, List< std::string > >& first = dictionaries[first_name];
  const Tree< std::string, List< std::string > >& second = dictionaries[second_name];

  for (auto it = second.cbegin(); it != second.cend(); ++it)
  {
    const std::string& key = it->first;
    const List< std::string >& values = it->second;
    if (first.find(key) != first.end())
    {
      List< std::string >& first_list = first[key];
      for (auto value_it = values.cbegin(); value_it != values.cend(); ++value_it)
      {
        first_list.push_back(*value_it);
      }
    }
    else
    {
      first[key] = values;
    }
  }
}

void strelyaev::getIntersection(std::istream& in,
    Tree< std::string, Tree< std::string, List< std::string > > >& dictionaries)
{
  std::string new_dict_name, first_name, second_name;
  in >> new_dict_name >> first_name >> second_name;

  if (dictionaries.find(first_name) == dictionaries.end() || dictionaries.find(second_name) == dictionaries.end())
  {
    throw std::logic_error("<BOOK NOT FOUND>");
  }

  const Tree< std::string, List< std::string > >& first_dict = dictionaries[first_name];
  const Tree< std::string, List< std::string > >& second_dict = dictionaries[second_name];
  Tree< std::string, List< std::string > > result_dict = {};

  for (auto it1 = first_dict.cbegin(); it1 != first_dict.cend(); ++it1)
  {
    const std::string& word = it1->first;
    const List< std::string >& first_translations = it1->second;

    auto it2 = second_dict.find(word);
    if (it2 != second_dict.cend())
    {
      const List< std::string >& second_translations = it2->second;
      List< std::string > common_translations;

      for (auto trans_it = first_translations.cbegin(); trans_it != first_translations.cend(); ++trans_it)
      {
        for (auto second_trans_it = second_translations.cbegin(); second_trans_it != second_translations.cend(); ++second_trans_it)
        {
          if (*trans_it == *second_trans_it)
          {
            common_translations.push_back(*trans_it);
          }
        }
      }

      if (!common_translations.empty())
      {
        result_dict[word] = common_translations;
      }
    }
  }
  dictionaries[new_dict_name] = result_dict;
}

void strelyaev::getCombining(std::istream& in,
    Tree< std::string, Tree< std::string, List< std::string > > >& dictionaries)
{
  std::string new_dict_name, first_name, second_name;
  in >> new_dict_name >> first_name >> second_name;

  if (dictionaries.find(first_name) == dictionaries.end() || dictionaries.find(second_name) == dictionaries.end())
  {
    throw std::logic_error("<BOOK NOT FOUND>");
  }

  const Tree< std::string, List< std::string > >& first_dict = dictionaries[first_name];
  const Tree< std::string, List< std::string > >& second_dict = dictionaries[second_name];
  Tree< std::string, List< std::string > > result_dict = {};

  for (auto it = first_dict.cbegin(); it != first_dict.cend(); ++it)
  {
    result_dict.insert(*it);
  }

  for (auto it = second_dict.cbegin(); it != second_dict.cend(); ++it)
  {
    const std::string& word = it->first;
    const List< std::string >& translations = it->second;
    auto result_it = result_dict.find(word);
    if (result_it != result_dict.end())
    {
      List< std::string >& result_translations = result_it->second;
      for (auto trans_it = translations.cbegin(); trans_it != translations.cend(); ++trans_it)
      {
        bool found = false;
        for (auto res_it = result_translations.begin(); res_it != result_translations.end(); ++res_it)
        {
          if (*res_it == *trans_it)
          {
            found = true;
            break;
          }
        }
        if (!found)
        {
          result_translations.push_back(*trans_it);
        }
      }
    }
    else
    {
      result_dict.insert(*it);
    }
  }
  dictionaries[new_dict_name] = result_dict;
}

void strelyaev::getDifference(std::istream& in,
    Tree< std::string, Tree< std::string, List< std::string > > >& dictionaries)
{
  std::string new_dict_name = "";
  std::string first_name = "";
  std::string second_name = "";
  std::string comparison_type = "";
  in >> new_dict_name >> first_name >> second_name >> comparison_type;

  if (dictionaries.find(first_name) == dictionaries.end() || dictionaries.find(second_name) == dictionaries.end())
  {
    throw std::logic_error("<BOOK NOT FOUND>");
  }

  Tree< std::string, List< std::string > >& first_dict = dictionaries[first_name];
  Tree< std::string, List< std::string > >& second_dict = dictionaries[second_name];
  Tree< std::string, List< std::string > > result_dict = {};

  if (comparison_type == "translation")
  {
    for (auto it = first_dict.cbegin(); it != first_dict.cend(); ++it)
    {
      const std::string& word = it->first;
      const List< std::string >& first_translations = it->second;
      auto second_it = second_dict.find(word);
      if (second_it != second_dict.end())
      {
        const List< std::string >& second_translations = second_it->second;
        List< std::string > difference_translations = {};

        for (auto trans_it = first_translations.cbegin(); trans_it != first_translations.cend(); ++trans_it)
        {
          bool found = false;
          for (auto second_trans_it = second_translations.cbegin(); second_trans_it != second_translations.cend(); ++second_trans_it)
          {
            if (*trans_it == *second_trans_it)
            {
              found = true;
              break;
            }
          }
          if (!found)
          {
            difference_translations.push_back(*trans_it);
          }
        }

        if (!difference_translations.empty())
        {
          result_dict[word] = difference_translations;
        }
      }
      else
      {
        result_dict[word] = first_translations;
      }
    }
  }
  else
  {
    for (auto it = first_dict.cbegin(); it != first_dict.cend(); ++it)
    {
      if (second_dict.find(it->first) == second_dict.end())
      {
        result_dict.insert(*it);
      }
    }
  }
  dictionaries[new_dict_name] = result_dict;
}
