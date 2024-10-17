#include "path_search.hpp"
#include <string>
#include <algorithm>
#include <iomanip>
#include <limits>
#include "stream_guard.hpp"

using std::pair;
using std::string;

constexpr int inf = std::numeric_limits< int >::max();

template< typename T >
struct Array
{
  Array() = delete;
  Array(size_t size):
    size_(size),
    vals_(reinterpret_cast<T*>(new char[sizeof(T) * size]))
  {}
  Array(size_t size, const T& val):
    size_(size),
    vals_(reinterpret_cast< T* >(new char[sizeof(T) * size]))
  {
    size_t i = 0;
    try
    {
      for (; i < size_; ++i)
      {
        new (vals_ + i) T(val);
      }
    }
    catch (...)
    {
      for (size_t j = 0; j < i; ++j)
      {
        vals_[j].~T();
      }
      delete[] reinterpret_cast< char* >(vals_);
      throw;
    }
  }
  Array(const Array& other):
    size_(other.size_),
    vals_(reinterpret_cast< T* >(new char[sizeof(T) * other.size_]))
  {
    size_t i = 0;
    try
    {
      for (; i < size_; ++i)
      {
        new (vals_ + i) T(other[i]);
      }
    }
    catch (...)
    {
      for (size_t j = 0; j < i; ++j)
      {
        vals_[j].~T();
      }
      delete[] reinterpret_cast< char* >(vals_);
      throw;
    }
  }
  Array(Array&& other) noexcept:
    size_(other.size_),
    vals_(other.vals_)
  {
    other.size_ = 0;
    other.vals_ = 0;
  }
  ~Array()
  {
    for (size_t i = 0; i < size_; ++i)
    {
      vals_[i].~T();
    }
    delete[] reinterpret_cast<char*>(vals_);
  }
  size_t size() const
  {
    return size_;
  }
  T* begin()
  {
    return vals_;
  }
  const T* begin() const
  {
    return vals_;
  }
  T* end()
  {
    return vals_ + size_;
  }
  const T* end() const
  {
    return vals_ + size_;
  }
  T& operator[](size_t index)
  {
    return vals_[index];
  }
  const T& operator[](size_t index) const
  {
    return vals_[index];
  }
private:
  size_t size_;
  T* vals_;
};

struct edge
{
  size_t a;
  size_t b;
  int val;
};

zaitsev::Map< string, size_t > convertToIndexes(const zaitsev::graph_t& graph);
Array< Array< int > > createAdjacencyMatrix(const zaitsev::graph_t& graph);
Array< edge > extractEdges(const zaitsev::graph_t& graph);
Array< Array< int > > calcPathsFloyd(const zaitsev::graph_t& graph);
pair< Array< int >, Array< size_t > > calcPathsFord(const Array< edge >& edges, size_t begin, size_t vert_nmb);

void zaitsev::findShortestDistance(const base_t& graphs, const args_flist& args, std::ostream& out)
{
  size_t args_nmb = std::distance(args.cbegin(), args.cend());
  args_flist::const_iterator arg = args.cbegin();
  if (args_nmb != 4)
  {
    throw std::invalid_argument("Invalid number of arguments");
  }
  const std::string& graph_name = *(++arg);
  const std::string& begin_name = *(++arg);
  const std::string& end_name = *(++arg);
  base_t::const_iterator graph_pos = graphs.find(graph_name);
  if (graph_pos == graphs.end())
  {
    throw std::invalid_argument("Graph doesn't exist");
  }
  graph_t::const_iterator graph_beg = graph_pos->second.find(begin_name);
  graph_t::const_iterator graph_end = graph_pos->second.find(end_name);
  if (graph_beg == graph_pos->second.end() || graph_end == graph_pos->second.end())
  {
    throw std::invalid_argument("Vertex doesn't exist");
  }
  Map< string, size_t > indexes = convertToIndexes(graph_pos->second);
  Array< edge > edges = extractEdges(graph_pos->second);
  pair< Array< int >, Array< size_t > > dist_with_prev = calcPathsFord(edges, indexes[begin_name], indexes.size());

  if (dist_with_prev.first[indexes[begin_name]] == inf)
  {
    throw std::invalid_argument("Graph contains negative weight cycles");
  }
  if (dist_with_prev.first[indexes[end_name]] == inf)
  {
    throw std::invalid_argument("End vertex cannot be reached");
  }
  if (dist_with_prev.first[indexes[begin_name]] == inf)
  {
    out << "Vertex \"" << end_name << "\" is unreachable from \"" << begin_name << "\".\n";
  }
  else
  {
    out << dist_with_prev.first[indexes[end_name]] << '\n';
  }
  return;
}

void zaitsev::findShortestPathTtrace(const base_t& graphs, const args_flist& args, std::ostream& out)
{
  size_t args_nmb = std::distance(args.cbegin(), args.cend());
  args_flist::const_iterator arg = args.cbegin();
  if (args_nmb != 4)
  {
    throw std::invalid_argument("Invalid number of arguments");
  }
  const std::string& graph_name = *(++arg);
  const std::string& begin_name = *(++arg);
  const std::string& end_name = *(++arg);
  base_t::const_iterator graph_pos = graphs.find(graph_name);
  if (graph_pos == graphs.end())
  {
    throw std::invalid_argument("Graph doesn't exist");
  }
  const graph_t& graph = graph_pos->second;
  if (graph.find(begin_name) == graph.end() || graph.find(end_name) == graph.end())
  {
    throw std::invalid_argument("Vertex doesn't exist");
  }
  Map< string, size_t > indexes = convertToIndexes(graph);
  Array< edge > edges = extractEdges(graph);
  pair< Array< int >, Array< size_t > > dist_with_prev = calcPathsFord(edges, indexes[begin_name], indexes.size());

  if (dist_with_prev.first[indexes[begin_name]] == inf)
  {
    throw std::invalid_argument("Graph contains negative weight cycles");
  }
  if (dist_with_prev.first[indexes[end_name]] == inf)
  {
    throw std::invalid_argument("End vertex cannot be reached");
  }
  if (dist_with_prev.first[indexes[begin_name]] == inf)
  {
    out << "Vertex \"" << end_name << "\" is unreachable from \"" << begin_name << "\".\n";
  }
  else
  {
    ForwardList< string >path = { end_name };
    size_t i = indexes[end_name];
    while (path.front() != begin_name)
    {
      i = dist_with_prev.second[i];
      path.push_front(std::next(graph.begin(), i)->first);
    }
    out << path.front();
    for (auto i = ++path.begin(); i != path.end(); ++i)
    {
      out << "->" << *i;
    }
    out << '\n';
  }
  return;
}

void zaitsev::printShortestPathsMatrix(const base_t& graphs, const args_flist& args, std::ostream& out)
{
  size_t args_nmb = std::distance(args.cbegin(), args.cend());
  if (args_nmb != 2)
  {
    throw std::invalid_argument("Invalid number of arguments");
  }
  const std::string& arg = *(++args.cbegin());
  base_t::const_iterator it = graphs.find(arg);
  if (it == graphs.end())
  {
    throw std::invalid_argument("Graph with name \"" + arg + "\", doesn't exists.");
  }
  if (it->second.empty())
  {
    out << "Graph is empty.\n";
    return;
  }
  Array< Array< int > > distances = calcPathsFloyd(it->second);
  size_t max_int_len = std::to_string(std::numeric_limits< int >::lowest()).size();
  auto get_len = [](const std::pair< string, unit_t >& a)
    {
      return a.first.size();
    };
  auto need_to_extend = [&](const size_t len)
    {
      return len < max_int_len;
    };

  Array< size_t > names_length(it->second.size());
  std::transform(it->second.begin(), it->second.end(), names_length.begin(), get_len);
  size_t names_column_width = *(std::max_element(names_length.begin(), names_length.end()));
  std::replace_if(names_length.begin(), names_length.end(), need_to_extend, max_int_len);
  string names_indent(names_column_width, ' ');
  string indent(2, ' ');
  StreamGuard guard(out);

  out << names_indent;
  size_t i = 0;
  for (graph_t::const_iterator ii = it->second.begin(); ii != it->second.end(); ++ii)
  {
    out << indent << std::left << std::setw(names_length[i]) << ii->first;
  }
  out << '\n';
  i = 0;
  for (graph_t::const_iterator ii = it->second.begin(); ii != it->second.end(); ++ii)
  {
    out << std::left << std::setw(names_column_width) << ii->first;
    for (size_t j = 0; j < distances.size(); ++j)
    {
      if (distances[i][j] == inf)
      {
        out << indent << std::left << std::setw(names_length[i]) << "inf";
      }
      else
      {
        out << indent << std::left << std::setw(names_length[i]) << distances[i][j];
      }
    }
    out << '\n';
    ++i;
  }
  return;
}

void zaitsev::checkNegativeWeightCycles(const base_t& graphs, const args_flist& args, std::ostream& out)
{
  size_t args_nmb = std::distance(args.cbegin(), args.cend());
  if (args_nmb != 2)
  {
    throw std::invalid_argument("Invalid number of arguments");
  }
  const std::string& arg = *(++args.cbegin());
  base_t::const_iterator it = graphs.find(arg);
  if (it == graphs.end())
  {
    throw std::invalid_argument("Graph with name \"" + arg + "\", doesn't exists.");
  }
  Array< Array< int > > distances = calcPathsFloyd(it->second);
  bool negative_cycles = false;
  for (size_t i = 0; i < distances.size(); ++i)
  {
    if (distances[i][i] < 0)
    {
      negative_cycles = true;
      break;
    }
  }
  out << "Graph " << (negative_cycles ? "contains" : "doesn't contain") << " a negative weight cycle\n";
}

zaitsev::Map< string, size_t > convertToIndexes(const zaitsev::graph_t& graph)
{
  using namespace zaitsev;
  Map< string, size_t > vert_indexes;
  size_t index = 0;
  for (auto& i : graph)
  {
    vert_indexes[i.first] = index;
    ++index;
  }
  return vert_indexes;
}

Array< Array< int > > createAdjacencyMatrix(const zaitsev::graph_t& graph)
{
  using namespace zaitsev;
  Array< Array< int > > matrix(graph.size(), Array< int >(graph.size(), inf));
  Map< string, size_t > vert_indexes = convertToIndexes(graph);

  size_t i = 0;
  for (auto& vert : graph)
  {
    for (auto& it_j : vert.second)
    {
      matrix[i][vert_indexes[it_j.first]] = it_j.second;
    }
    ++i;
  }
  return matrix;
}

Array< edge > extractEdges(const zaitsev::graph_t& graph)
{
  using namespace zaitsev;

  Map< string, size_t > vert_indexes = convertToIndexes(graph);
  size_t edges_nmb = 0;
  for (auto& i : graph)
  {
    edges_nmb += i.second.size();
  }
  Array< edge > edges_list(edges_nmb);
  size_t i = 0, k = 0;
  for (auto& it_i : graph)
  {
    for (auto& it_j : it_i.second)
    {
      edges_list[k] = { i, vert_indexes[it_j.first], it_j.second };
      ++k;
    }
    ++i;
  }
  return edges_list;
}

pair< Array< int >, Array< size_t > > calcPathsFord(const Array< edge >& edges, size_t begin, size_t vert_nmb)
{
  Array< int > dist(vert_nmb, inf);
  dist[begin] = 0;
  Array< size_t > prev(vert_nmb, vert_nmb + 1);
  bool changed = true;
  size_t phase_nmb = 0;
  while (changed && phase_nmb < vert_nmb + 1)
  {
    changed = false;
    for (size_t j = 0; j < edges.size(); ++j)
    {
      if (dist[edges[j].a] < inf && dist[edges[j].b] > dist[edges[j].a] + edges[j].val)
      {
        dist[edges[j].b] = dist[edges[j].a] + edges[j].val;
        prev[edges[j].b] = edges[j].a;
        changed = true;
      }
    }
    ++phase_nmb;
  }
  if (phase_nmb == vert_nmb + 1)
  {
    std::fill(dist.begin(), dist.end(), inf);
  }

  return { dist, prev };
}

Array< Array< int > > calcPathsFloyd(const zaitsev::graph_t& graph)
{
  Array< Array< int > > dist = createAdjacencyMatrix(graph);
  for (size_t k = 0; k < dist.size(); ++k)
  {
    for (size_t i = 0; i < dist.size(); ++i)
    {
      for (size_t j = 0; j < dist.size(); ++j)
      {
        if (dist[i][k] < inf && dist[k][j] < inf)
        {
          dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
        }
      }
    }
  }
  return dist;
}
