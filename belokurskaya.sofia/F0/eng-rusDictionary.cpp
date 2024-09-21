#include "eng-rusDictionary.hpp"

#include <functional>

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
  return words_.at(eng);
}

size_t belokurskaya::EngRusDict::getCountWords() const
{
  return words_.size();
}

size_t belokurskaya::EngRusDict::getCountTranslations(const std::string& eng) const
{
  return words_.at(eng).size();
}

void belokurskaya::EngRusDict::display(std::ostream& out) const
{
  words_.display(out, "\n");
  out << "\n";
}

void belokurskaya::EngRusDict::addTranslation(const std::string& eng, const std::string& translation)
{
  words_[eng].insert(getLettersToLower(translation));
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
  words_[getLettersToLower(eng)] = MyVector< std::string >();
}

void belokurskaya::EngRusDict::removeWord(const std::string& eng)
{
  words_.erase(eng);
}

bool belokurskaya::EngRusDict::containsWord(const std::string& word) const
{
  return words_.find(word) != words_.end();
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
  for (const std::pair< std::string, MyVector< std::string > >& pair : other.words_)
  {
    try
    {
      words_.at(pair.first).erase(pair.second.begin(), pair.second.end());
    }
    catch (const std::out_of_range&)
    {
      continue;
    }
  }
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
  EngRusDict newDict;
  for (const std::pair< std::string, MyVector< std::string > >& pair : erd2.words_)
  {
    if (erd1.words_.find(pair.first) != erd1.words_.end())
    {
      newDict.words_[pair.first];
      const MyVector< std::string >& translations = erd1.words_.at(pair.first);
      newDict.words_.at(pair.first).insert(translations.begin(), translations.end());
    }
  }
  return newDict;
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
