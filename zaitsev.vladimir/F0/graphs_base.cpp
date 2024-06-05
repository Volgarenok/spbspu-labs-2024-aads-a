#include "graphs_base.hpp"

void zaitsev::createGraph(base_t& graphs, const args_flist& args, std::ostream&)
{
  size_t args_nmb = std::distance(args.cbegin(), args.cend());
  const std::string& arg = *(++args.cbegin());
  if (args_nmb != 2)
  {
    throw std::invalid_argument("Invalid number of arguments");
  }
  if (graphs.find(arg) != graphs.end())
  {
    throw std::invalid_argument("Graph with name \"" + arg + "\", already exists.");
  }
  graphs[arg];
}

void zaitsev::deleteGraph(base_t& graphs, const args_flist& args, std::ostream&)
{
  size_t args_nmb = std::distance(args.cbegin(), args.cend());
  const std::string& arg = *(++args.cbegin());
  if (args_nmb != 2)
  {
    throw std::invalid_argument("Invalid number of arguments");
  }
  auto pos = graphs.find(arg);
  if (pos == graphs.end())
  {
    throw std::invalid_argument("Graph with name \"" + arg + "\", doesn't exist.");
  }
  else
  {
    graphs.erase(pos);
  }
}

void zaitsev::addVertex(base_t& graphs, const args_flist& args, std::ostream&)
{
  size_t args_nmb = std::distance(args.cbegin(), args.cend());
  args_flist::const_iterator arg = args.cbegin();
  if (args_nmb != 3)
  {
    throw std::invalid_argument("Invalid number of arguments");
  }
  const std::string& graph_name = *(++arg);
  const std::string& vertex_name = *(++arg);
  auto it = graphs.find(graph_name);
  if (it == graphs.end())
  {
    throw std::invalid_argument("No graph \"" + graph_name + "\" in the base");
  }
  if (it->second.find(vertex_name) != it->second.end())
  {
    throw std::invalid_argument("Vertex \"" + vertex_name + "\" already exists");
  }
  it->second.insert({ vertex_name, unit_t{} });
}

void zaitsev::addEdge(base_t& graphs, const args_flist& args, std::ostream&)
{
  size_t args_nmb = std::distance(args.cbegin(), args.cend());
  args_flist::const_iterator arg = args.cbegin();
  if (args_nmb > 6 || args_nmb < 5 || (args_nmb == 5 && (*std::next(arg))[0] == '-'))
  {
    throw std::invalid_argument("Invalid number of arguments");
  }
  bool check = false;
  if (args_nmb == 6)
  {
    ++arg;
    if (*arg != "-check")
    {
      throw std::invalid_argument("Invalid option");
    }
    check = true;
  }
  const std::string& graph = *(++arg);
  const std::string& begin = *(++arg);
  const std::string& end = *(++arg);
  int value = std::stoi(*(++arg));
  auto it_graph = graphs.find(graph);
  if (it_graph == graphs.end())
  {
    throw std::invalid_argument("Such graph doesn't found");
  }
  auto it_beg = it_graph->second.find(begin);
  if (it_beg != it_graph->second.end())
  {
    if (!check || (check && it_beg->second.find(end) == it_beg->second.end()))
    {
      it_beg->second[end] = value;
    }
    else
    {
      throw std::invalid_argument("Edge already exists");
    }
  }
  else
  {
    std::pair< std::string, unit_t > to_add = { begin, unit_t{} };
    to_add.second.insert({ end, value });
    it_graph->second.insert(std::move(to_add));
  }
  if (it_graph->second.find(end) == it_graph->second.end())
  {
    it_graph->second.insert({ end, unit_t{} });
  }
}

void zaitsev::mergeGraphs(base_t& graphs, const args_flist& args, std::ostream&)
{
  size_t args_nmb = std::distance(args.cbegin(), args.cend());
  args_flist::const_iterator arg = args.cbegin();
  if (args_nmb > 5 || args_nmb < 4 || (args_nmb == 4 && (*std::next(arg))[0] == '-'))
  {
    throw std::invalid_argument("Invalid number of arguments");
  }
  bool check = false;
  if (args_nmb == 5)
  {
    ++arg;
    if (*arg != "-check")
    {
      throw std::invalid_argument("Invalid option");
    }
    check = true;
  }
  const std::string& new_nm = *(++arg);
  const std::string& nm_1 = *(++arg);
  const std::string& nm_2 = *(++arg);
  if (graphs.find(new_nm) != graphs.end() || graphs.find(nm_1) == graphs.end() || graphs.find(nm_2) == graphs.end())
  {
    throw std::invalid_argument("Invalid arguments");
  }
  graph_t new_graph = graphs.find(nm_2)->second;
  const graph_t& graph_1_inst = graphs.find(nm_1)->second;

  for (auto& i : graph_1_inst)
  {
    if (new_graph.find(i.first) == new_graph.end())
    {
      new_graph.insert(i);
    }
    else
    {
      for (auto& j : i.second)
      {
        if (!check)
        {
          new_graph[i.first][j.first] = j.second;
        }
        else
        {
          if (new_graph[i.first].find(j.first) == new_graph[i.first].end())
          {
            new_graph[i.first][j.first] = j.second;
          }
          else
          {
            throw std::invalid_argument("Graphs have same edges and cannot be merged");
          }
        }
      }
    }
  }
  graphs[new_nm] = std::move(new_graph);
  return;
}
