#include "commands.hpp"
#include <fstream>

piyavkin::iterator getDict(std::istream& in, piyavkin::dic_t dicts)
{
  std::string name = "";
  in >> name;
  piyavkin::iterator it = dicts.find(name);
  if (it == dicts.end())
  {
    throw std::out_of_range("");
  }
  return it;
}

void change(std::istream& in, piyavkin::tree_t& dic)
{
  size_t val = 0;
  std::string key = "";
  in >> key >> val;
  if (in)
  {
    auto dicIt = dic.find(key);
    if (dicIt != dic.end())
    {
      dic.erase(key);
    }
    dic.insert(std::pair< std::string, size_t >(key, val));
  }
}

std::pair< piyavkin::iterator, bool > add(std::istream& in, piyavkin::dic_t& dicts)
{
  std::string name = "";
  in >> name;
  return dicts.insert(std::make_pair(name, piyavkin::tree_t()));
}

void piyavkin::print(std::istream& in, std::ostream& out, const dic_t& dicts)
{
  std::string nameDict = "";
  in >> nameDict;
  auto it = dicts.find(nameDict);
  if (it != dicts.cend())
  {
    out << nameDict << '\n';
    tree_t dict = it->second;
    for (auto dictIt = dict.cbegin(); dictIt != dict.cend(); ++dictIt)
    {
      out << dictIt->first << ' ' << dictIt->second << '\n';
    }
  }
  else
  {
    throw std::out_of_range("");
  }
}

piyavkin::iterator piyavkin::addDict(std::istream& in, dic_t& dicts)
{
  auto pair = add(in, dicts);
  if (pair.second)
  {
    throw std::out_of_range(pair.first->first);
  }
  return pair.first;
}

piyavkin::iterator piyavkin::cmdChange(std::istream& in, dic_t& dicts)
{
  auto it = getDict(in, dicts);
  change(in, it->second);
  return it;
}

piyavkin::iterator piyavkin::makeDict(std::istream& in, dic_t& dicts)
{
  iterator it = add(in, dicts).first;
  it->second.clear();
  std::string nameFile = "";
  in >> nameFile;
  std::ifstream file(nameFile);
  if (!file.is_open())
  {
    throw std::out_of_range("");
  }
  while (file)
  {
    change(file, it->second);
  }
  return it;
}

piyavkin::iterator piyavkin::intersect(std::istream& in, dic_t& dicts)
{
  std::string newDic = "";
  std::string lhs = "";
  std::string rhs = "";
  in >> newDic >> lhs >> rhs;
  const tree_t rhsTree = dicts.at(rhs);
  const tree_t lhsTree = dicts.at(lhs);
  auto rhsIt = rhsTree.cbegin();
  tree_t newTree;
  for (auto it = lhsTree.cbegin(); it != lhsTree.cend(); ++it)
  {
    if (rhsIt->first == it->first)
    {
      newTree.insert(std::pair< std::string, size_t >(it->first, std::min(it->second, rhsIt->second)));
      if (rhsIt != rhsTree.cend())
      {
        ++rhsIt;
      }
    }
    else if (rhsIt->first < it->first)
    {
      while (rhsIt != rhsTree.cend() && rhsIt->first < it->first)
      {
        ++rhsIt;
      }
    }
  }
  if (dicts.find(newDic) != dicts.end())
  {
    dicts.erase(newDic);
  }
  return dicts.insert(std::pair< std::string, tree_t >(newDic, newTree)).first;
}

piyavkin::iterator unionImpl(piyavkin::dic_t& dicts, const std::string& newDic, const std::string& lhs, const std::string& rhs)
{
  using namespace piyavkin;
  const tree_t rhsTree = dicts.at(rhs);
  const tree_t lhsTree = dicts.at(lhs);
  tree_t newTree;
  for (auto lhsIt = lhsTree.cbegin(); lhsIt != lhsTree.cend(); ++lhsIt)
  {
    newTree.insert(std::pair< std::string, size_t >(*lhsIt));
  }
  for (auto it = rhsTree.cbegin(); it != rhsTree.cend(); ++it)
  {
    auto lhsVal = newTree.find(it->first);
    if (lhsVal == newTree.end())
    {
      newTree.insert(std::pair< std::string, size_t >(*it));
    }
    else
    {
      if (lhsVal->second < it->second)
      {
        newTree.erase(it->first);
        newTree.insert(std::pair< std::string, size_t >(*it));
      }
    }
  }
  if (dicts.find(newDic) != dicts.end())
  {
    dicts.erase(newDic);
  }
  return dicts.insert(std::pair< std::string, tree_t >(newDic, newTree)).first;
}

piyavkin::iterator piyavkin::unionD(std::istream& in, dic_t& dicts)
{
  std::string newDic = "";
  std::string lhs = "";
  std::string rhs = "";
  in >> newDic >> lhs >> rhs;
  return unionImpl(dicts, newDic, lhs, rhs);
}

piyavkin::iterator piyavkin::uniqueD(std::istream& in, dic_t& dicts)
{
  std::string newDic = "";
  std::string lhs = "";
  std::string rhs = "";
  in >> newDic >> lhs >> rhs;
  const tree_t rhsTree = dicts.at(rhs);
  const tree_t lhsTree = dicts.at(lhs);
  auto rhsIt = rhsTree.cbegin();
  tree_t newTree;
  for (auto it = lhsTree.cbegin(); it != lhsTree.cend(); ++it)
  {
    if (rhsIt->first < it->first)
    {
      newTree.insert(std::pair< std::string, size_t >(*it));
      while (rhsIt != rhsTree.cend() && rhsIt->first < it->first)
      {
        ++rhsIt;
      }
    }
    else if (rhsIt->first > it->first)
    {
      newTree.insert(std::pair< std::string, size_t >(*it));
    }
    else
    {
      if (rhsIt != rhsTree.cend())
      {
        ++rhsIt;
      }
    }
  }
  if (dicts.find(newDic) != dicts.end())
  {
    dicts.erase(newDic);
  }
  return dicts.insert(std::pair< std::string, tree_t >(newDic, newTree)).first;
}

piyavkin::iterator piyavkin::addDtoD(std::istream& in, dic_t& dicts)
{
  std::string lhs = "";
  std::string rhs = "";
  in >> lhs >> rhs;
  return unionImpl(dicts, lhs, lhs, rhs);
}