#include "eng-rusDictionary.hpp"

#include <functional>

using Str = std::string;

belokurskaya::EngRusDict::EngRusDict()
{}

belokurskaya::EngRusDict::EngRusDict(const EngRusDict& other)
{
  words_ = other.words_;
}

belokurskaya::EngRusDict::EngRusDict(EngRusDict&& other) noexcept:
  words_(std::move(other.words_))
{
  other.clear();
}

belokurskaya::EngRusDict::~EngRusDict()
{
  clear();
}

void belokurskaya::EngRusDict::clear()
{
  words_.clear();
}

belokurskaya::MyVector< Str > belokurskaya::EngRusDict::getTranslations(const Str& eng) const
{
  try
  {
    return words_.SEARCH(eng);
  }
  catch (const std::invalid_argument&)
  {
    return MyVector< Str >();
  }
}

size_t belokurskaya::EngRusDict::getCountWords() const
{
  return words_.size();
}

size_t belokurskaya::EngRusDict::getCountTranslations(const Str& eng) const
{
  try
  {
    return words_.SEARCH(eng).size();
  }
  catch (const std::invalid_argument&)
  {
    return 0;
  }
}

void belokurskaya::EngRusDict::display(std::ostream& out) const
{
  words_.display(out, "\n");
  out << "\n";
}

void belokurskaya::EngRusDict::addTranslation(const Str& eng, const Str& translation)
{
  words_.at(eng).insert(getLettersToLower(translation));
}

void belokurskaya::EngRusDict::removeTranslation(const Str& eng, const Str& translation)
{
  if (!words_.contains(eng))
  {
    throw std::invalid_argument("Invalid argument");
  }
  MyVector< Str >& translations = words_.SEARCH(eng);
  translations.erase(translations.findIndexElement(translation));
}

void belokurskaya::EngRusDict::addWord(const Str& eng)
{
  if (!containsOnlyEnglishLetters(eng))
  {
    throw std::invalid_argument("Invalid argument");
  }
  words_.INSERT(getLettersToLower(eng), MyVector< Str >());
}

void belokurskaya::EngRusDict::removeWord(const Str& eng)
{
  words_.erase(eng);
}

bool belokurskaya::EngRusDict::containsWord(const Str& word) const
{
  return words_.exists(word);
}

bool belokurskaya::EngRusDict::containsTranslation(const Str& eng, const Str& translation) const
{
  auto it = words_.find(eng);
  if (it != BinarySearchTree< Str, MyVector< Str >, std::less< Str > >::Iterator(words_.end()))
  {
    const MyVector< Str >& translations = it->value;
    for (const Str& trans : translations)
    {
      if (trans == translation)
      {
        return true;
      }
    }
  }
  return false;
}

belokurskaya::MyVector< Str > belokurskaya::EngRusDict::getWords() const
{
  MyVector< Str > allWords;
  for (const auto& pair : words_)
  {
    allWords.insert(pair.first);
  }
  return allWords;
}

void belokurskaya::EngRusDict::addWordFromEngRusDict(const EngRusDict& other)
{
  for (const Str& key : other.words_.getAllKeys())
  {
    if (words_.contains(key))
    {
      MyVector< Str >& translations = words_.SEARCH(key);
      for (const Str& translation : other.words_.SEARCH(key))
      {
        bool alreadyPresent = false;
        for (const Str& existingTranslation : translations)
        {
          if (existingTranslation == translation)
          {
            alreadyPresent = true;
            break;
          }
        }
        if (!alreadyPresent)
        {
          translations.push_back(translation);
        }
      }
    }
    else
    {
      MyVector< Str > newTranslations;
      for (const Str& translation : other.words_.SEARCH(key))
      {
        newTranslations.push_back(translation);
      }
      words_.INSERT(key, newTranslations);
    }
  }
}

void belokurskaya::EngRusDict::removeWordFromEngRusDict(const EngRusDict& other)
{
  words_.deleteElements(other.words_);
}

belokurskaya::EngRusDict& belokurskaya::EngRusDict::operator=(const belokurskaya::EngRusDict& other)
{
  words_ = other.words_;
  return *this;
}

Str belokurskaya::EngRusDict::getLettersToLower(Str word)
{
  for (auto& c : word)
  {
    c = std::tolower(c);
  }
  return word;
}

bool belokurskaya::EngRusDict::containsOnlyEnglishLetters(const Str& word) const
{
  bool result = true;
  for (const char& c : word)
  {
    if (!std::isalpha(c))
    {
      result = false;
      break;
    }
  }
  return result;
}

belokurskaya::EngRusDict belokurskaya::getIntersectionWithEngRusDict(const EngRusDict& erd1, const EngRusDict& erd2)
{
  EngRusDict result;
  for (Str& key : erd2.words_.getAllKeys())
  {
    if (erd1.words_.contains(key))
    {
      result.addWord(key);
      for (Str& translation : getIntersectionVector(erd1.words_.SEARCH(key), erd2.words_.SEARCH(key)))
      {
        result.addTranslation(key, translation);
      }
    }
  }
  return result;
}

belokurskaya::EngRusDict belokurskaya::getDifferenceWithEngRusDict(const EngRusDict& erd1, const EngRusDict& erd2)
{
  EngRusDict result;
  for (Str& key : erd2.words_.getAllKeys())
  {
    if (!erd1.words_.contains(key))
    {
      result.addWord(key);
      for (Str& translation : erd2.words_.SEARCH(key))
      {
        result.addTranslation(key, translation);
      }
    }
  }
  for (Str& key : erd1.words_.getAllKeys())
  {
    if (!erd2.words_.contains(key))
    {
      result.addWord(key);
      for (Str& translation : erd1.words_.SEARCH(key))
      {
        result.addTranslation(key, translation);
      }
    }
  }
  return result;
}
