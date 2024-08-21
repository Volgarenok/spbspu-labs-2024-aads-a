#include "dictionaryCollection.hpp"

belokurskaya::DictionaryCollection::DictionaryCollection():
  entries(nullptr),
  capacity(0),
  size(0)
{}

belokurskaya::DictionaryCollection::~DictionaryCollection()
{
  delete[] entries;
}

void belokurskaya::DictionaryCollection::add(const std::string& name, Dictionary dict)
{
  if (size == capacity)
  {
    resize();
  }
  entries[size].name = name;
  entries[size].dict = std::move(dict);
  size++;
}

Dictionary* belokurskaya::DictionaryCollection::find(const std::string& name)
{
  for (size_t i = 0; i < size; ++i)
  {
    if (entries[i].name == name)
    {
      return &entries[i].dict;
    }
  }
  return nullptr;
}

void belokurskaya::DictionaryCollection::resize()
{
  capacity = (capacity == 0) ? 2 : capacity * 2;
  DictionaryEntry* new_entries = new DictionaryEntry[capacity];
  for (size_t i = 0; i < size; ++i)
  {
    new_entries[i] = std::move(entries[i]);
  }
  delete[] entries;
  entries = new_entries;
}
