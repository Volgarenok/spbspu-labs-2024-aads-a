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

void ishmuratov::print_dict(const dict_t & dictionaries, std::istream & input, std::ostream & output)
{
  std::string name;
  input >> name;

  if (dictionaries.find(name) == dictionaries.cend())
  {
    throw std::out_of_range("Dictionary doesn't exists!");
  }
  if (dictionaries.at(name).empty())
  {
    throw std::underflow_error("This dictionary is empty!");
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
    auto check = pair;
    if (++check != dictionaries.at(name).cend())
    {
      output << "\n";
    }
  }
}

void ishmuratov::get_value(const dict_t & dictionaries, std::istream & input, std::ostream & output)
{
  std::string name;
  std::string key;
  input >> name >> key;
  if (dictionaries.find(name) == dictionaries.cend())
  {
    throw std::out_of_range("Dictionary doesn't exists!");
  }
  if (dictionaries.at(name).find(key) == dictionaries.at(name).cend())
  {
    throw std::out_of_range("Key wasn't found!");
  }

  auto found_key = dictionaries.at(name).at(key);
  size_t count = 1;
  for (auto value = found_key.cbegin(); value != found_key.cend(); ++value)
  {
    output << count << ". " << *value << "\n";
    ++count;
  }
}

void ishmuratov::save(const dict_t & dictionaries, std::istream &input, std::ostream & output)
{
  std::string name;
  input >> name;
  if (dictionaries.find(name) == dictionaries.cend())
  {
    throw std::out_of_range("Dictionary doesn't exists!");
  }
  output << name << "\n";
  for (auto pair = dictionaries.at(name).cbegin(); pair != dictionaries.at(name).cend(); ++pair)
  {
    output << pair->first;
    for (auto value = (pair->second.cbegin()); value != pair->second.cend(); ++value)
    {
      output << " " << *value;
    }
    output << "\n";
  }
  output << "\n";
}

void ishmuratov::read(ishmuratov::dict_t &dictionaries, std::istream & input)
{
  std::string name;
  input >> name;
}

void ishmuratov::renamedict(dict_t & dictionaries, std::istream & input)
{
  std::string name;
  std::string new_name;
  input >> name >> new_name;
  if (dictionaries.find(name) == dictionaries.end())
  {
    throw std::out_of_range("Non existent dictionary!");
  }
  if (dictionaries.find(new_name) != dictionaries.end())
  {
    throw std::out_of_range("Dictionary with this name already exist!");
  }

  dictionaries.insert(std::make_pair(new_name, dictionaries.at(name)));
  dictionaries.erase(name);
}

void ishmuratov::intersect(dict_t &dictionaries, std::istream &input)
{
  std::string new_name;
  std::string first_name;
  std::string second_name;
  input >> new_name >> first_name >> second_name;

  if (dictionaries.find(first_name) == dictionaries.end() || dictionaries.find(second_name) == dictionaries.end())
  {
    throw std::out_of_range("Non existent dictionary!");
  }

  unit_t temp = intersect_impl(dictionaries.at(first_name), dictionaries.at(second_name));

  while (input >> second_name)
  {
    temp = intersect_impl(temp, dictionaries.at(second_name));
    if (input.get() == '\n')
    {
      break;
    }
  }
  dictionaries.insert(std::make_pair(new_name, temp));
}

ishmuratov::unit_t ishmuratov::intersect_impl(const unit_t & first, const unit_t & second)
{
  unit_t intersect_dict;
  for (auto pair = first.cbegin(); pair != first.cend(); ++pair)
  {
    if (second.find(pair->first) != second.cend())
    {
      intersect_dict.insert(std::make_pair(pair->first, first.at(pair->first)));
    }
  }
  return intersect_dict;
}

void ishmuratov::uniond(ishmuratov::dict_t &dictionaries, std::istream &input)
{
  std::string new_name;
  std::string first_name;
  std::string second_name;
  input >> new_name >> first_name >> second_name;

  if (dictionaries.find(first_name) == dictionaries.end() || dictionaries.find(second_name) == dictionaries.end())
  {
    throw std::out_of_range("Non existent dictionary!");
  }

  unit_t temp = union_impl(dictionaries.at(first_name), dictionaries.at(second_name));

  while (input >> second_name)
  {
    temp = union_impl(temp, dictionaries.at(second_name));
    if (input.get() == '\n')
    {
      break;
    }
  }
  dictionaries.insert(std::make_pair(new_name, temp));
}

ishmuratov::unit_t ishmuratov::union_impl(const ishmuratov::unit_t &first, const ishmuratov::unit_t &second)
{
  unit_t union_dict;
  for (auto pair = first.cbegin(); pair != first.cend(); ++pair)
  {
    union_dict.insert(std::make_pair(pair->first, first.at(pair->first)));
  }
  for (auto pair = second.cbegin(); pair != second.cend(); ++pair)
  {
    if (union_dict.find(pair->first) == union_dict.end())
    {
      union_dict.insert(std::make_pair(pair->first, second.at(pair->first)));
    }
  }
  return union_dict;
}