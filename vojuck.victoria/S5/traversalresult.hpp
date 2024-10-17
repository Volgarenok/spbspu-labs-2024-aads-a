#ifndef TRAVERSALRESULT_HPP
#define TRAVERSALRESULT_HPP

namespace vojuck
{
  struct TraversalResult
  {
    long long sum;
    std::string values;

    TraversalResult() : sum(0), values("") {}

    void operator()(const std::pair<const int, std::string>& key_value)
    {
        // Проверка на переполнение при добавлении
      if ((key_value.first > 0 && sum > std::numeric_limits<long long>::max() - key_value.first) ||
          (key_value.first < 0 && sum < std::numeric_limits<long long>::min() - key_value.first))
      {
        throw std::overflow_error("overflow sum.");
      }
      sum += key_value.first;

      if (!values.empty())
      {
        values += " ";
      }
        values += key_value.second;
    }
  };
}
#endif
