#include "cmd.hpp"

void ishmuratov::create_dict(dict_t & dictionaries, std::istream & input)
{
  unit_t content;
  std::string name;
  input >> name;
  if (dictionaries.find(name) == dictionaries.end())
  {
    dictionaries.insert(std::make_pair(name, content));
  }
  else
  {
    throw std::out_of_range("Dictionary already exists!");
  }
}

void ishmuratov::delete_dict(dict_t & dictionaries, std::istream & input)
{
  std::string name;
  input >> name;
  if (dictionaries.find(name) == dictionaries.end())
  {
    throw std::out_of_range("Dictionary doesn't exists!");
  }
  dictionaries.erase(name);
}

void ishmuratov::add_key(dict_t & dictionaries, std::istream & input)
{
  std::string name;
  std::string key;
  std::string value;
  value_t values;

  input >> name >> key >> value;
  values.pushBack(value);

  if (dictionaries.find(name) == dictionaries.end())
  {
    throw std::out_of_range("Dictionary doesn't exists!");
  }
  dictionaries.at(name).insert(std::make_pair(key, values));
}

void ishmuratov::add_value(dict_t & dictionaries, std::istream & input)
{
  std::string name;
  std::string key;
  std::string value;

  input >> name >> key >> value;

  if (dictionaries.find(name) == dictionaries.end())
  {
    throw std::out_of_range("Dictionary doesn't exists!");
  }
  dictionaries.at(name).at(key).pushBack(value);
}

void ishmuratov::remove_key(dict_t & dictionaries, std::istream & input)
{
  std::string name;
  std::string key;

  input >> name >> key;

  if (dictionaries.find(name) == dictionaries.end())
  {
    throw std::out_of_range("Dictionary doesn't exists!");
  }
  dictionaries.at(name).erase(key);
}

void ishmuratov::print_dict(dict_t & dictionaries, std::istream & input, std::ostream & output)
{
  std::string name;
  input >> name;

  if (dictionaries.find(name) == dictionaries.end())
  {
    throw std::out_of_range("Dictionary doesn't exists!");
  }

  for (auto pair = dictionaries.at(name).cbegin(); pair != dictionaries.at(name).cend(); ++pair)
  {
    output << pair->first << "\n";
    size_t count = 1;
    for (auto value = pair->second.cbegin(); value != pair->second.cend(); ++value)
    {
      output << count << ". " << *value << "\n";
      ++count;
    }
    output << "\n";
  }
}