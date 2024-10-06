#include "commandCollection.hpp"

belokurskaya::CommandCollection::CommandCollection():
  entries(nullptr),
  capacity(0),
  size(0)
{}

belokurskaya::CommandCollection::~CommandCollection()
{
  delete[] entries;
}

void belokurskaya::CommandCollection::add(const std::string& name, fnc func)
{
  if (size == capacity)
  {
    resize();
  }
  entries[size].name = name;
  entries[size].func = func;
  size++;
}

fnc* belokurskaya::CommandCollection::find(const std::string& name)
{
  for (size_t i = 0; i < size; ++i)
  {
    if (entries[i].name == name)
    {
      return &entries[i].func;
    }
  }
  return nullptr;
}

fnc belokurskaya::CommandCollection::at(const std::string& name)
{
  fnc* func = find(name);
  if (func != nullptr)
  {
    return *func;
  }
  throw std::out_of_range("Command not found");
}

void belokurskaya::CommandCollection::resize()
{
  capacity = (capacity == 0) ? 2 : capacity * 2;
  CommandEntry* new_entries = new CommandEntry[capacity];
  for (size_t i = 0; i < size; ++i)
  {
    new_entries[i] = std::move(entries[i]);
  }
  delete[] entries;
  entries = new_entries;
}
