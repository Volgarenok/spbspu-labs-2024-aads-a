#include "eng-rusDictionary.hpp"

#include <functional>
#include <algorithm>

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

belokurskaya::MyVector< std::string > belokurskaya::EngRusDict::getTranslations(const std::string& eng) const
{
  try
  {
    return words_.SEARCH(eng);
  }
  catch (const std::invalid_argument&)
  {
    return MyVector< std::string >();
  }
}

size_t belokurskaya::EngRusDict::getCountWords() const
{
  return words_.size();
}

size_t belokurskaya::EngRusDict::getCountTranslations(const std::string& eng) const
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

void belokurskaya::EngRusDict::addTranslation(const std::string& eng, const std::string& translation)
{
  words_.at(eng).insert(getLettersToLower(translation));
}

void belokurskaya::EngRusDict::removeTranslation(const std::string& eng, const std::string& translation)
{
  if (!words_.contains(eng))
  {
    throw std::invalid_argument("Invalid argument");
  }
  MyVector< std::string >& translations = words_.SEARCH(eng);
  translations.erase(translations.findIndexElement(translation));
}

void belokurskaya::EngRusDict::addWord(const std::string& eng)
{
  if (!containsOnlyEnglishLetters(eng))
  {
    throw std::invalid_argument("Invalid argument");
  }
  words_.INSERT(getLettersToLower(eng), MyVector< std::string >());
}

void belokurskaya::EngRusDict::removeWord(const std::string& eng)
{
  words_.erase(eng);
}

bool belokurskaya::EngRusDict::containsWord(const std::string& word) const
{
  return words_.exists(word);
}

bool belokurskaya::EngRusDict::containsTranslation(const std::string& eng, const std::string& translation) const
{
  auto it = words_.find(eng);
  if (it != words_.end())
  {
    return (it->second.find(translation) != it->second.end());
  }
  return false;
}

belokurskaya::MyVector< std::string > belokurskaya::EngRusDict::getWords() const
{
  MyVector< std::string > allWords;
  for (const auto& pair : words_)
  {
    allWords.insert(pair.first);
  }
  return allWords;
}

void belokurskaya::EngRusDict::addWordFromEngRusDict(const EngRusDict& other)
{
  for (const std::string& key : other.words_.getAllKeys())
  {
    if (words_.contains(key))
    {
      MyVector< std::string >& translations = words_.SEARCH(key);
      for (const std::string& translation : other.words_.SEARCH(key))
      {
        if (!translations.contains(translation))
        {
          translations.push_back(translation);
        }
      }
      std::sort(translations.begin(), translations.end());
    }
    else
    {
      words_.INSERT(key, other.words_.SEARCH(key));
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

std::string belokurskaya::EngRusDict::getLettersToLower(std::string word)
{
  for (auto& c : word)
  {
    c = std::tolower(c);
  }
  return word;
}

bool belokurskaya::EngRusDict::containsOnlyEnglishLetters(const std::string& word) const
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
  for (std::string& key : erd2.words_.getAllKeys())
  {
    if (erd1.words_.contains(key))
    {
      result.addWord(key);
      for (std::string& translation : getIntersectionVector(erd1.words_.SEARCH(key), erd2.words_.SEARCH(key)))
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
  for (std::string& key : erd2.words_.getAllKeys())
  {
    if (!erd1.words_.contains(key))
    {
      result.addWord(key);
      for (std::string& translation : erd2.words_.SEARCH(key))
      {
        result.addTranslation(key, translation);
      }
    }
  }
  for (std::string& key : erd1.words_.getAllKeys())
  {
    if (!erd2.words_.contains(key))
    {
      result.addWord(key);
      for (std::string& translation : erd1.words_.SEARCH(key))
      {
        result.addTranslation(key, translation);
      }
    }
  }
  return result;
}
