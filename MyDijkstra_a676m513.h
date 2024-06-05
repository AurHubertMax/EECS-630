#ifndef _MY_DIJKSTRA_H_
#define _MY_DIJKSTRA_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
#include <stack>
#include <utility>
#include <algorithm>
#include <tuple>

typedef unsigned int NodeType;
typedef unsigned int WeightType;
typedef std::vector<std::vector<std::pair<NodeType, WeightType>>> GraphType; // graph as adjacent list

/*------------------------------------------------------------------------------
 ShortestPath_Dijkstra
  Find and print the shortest path from source to end using the Dijkstra's algorithm

 Vairables:
   - graph: the input graph
   - source: the source node
   - end: the target node
   - path_len: the the summation of weights of all edges in the shortest path
   - path: the shortest path represented as a list of nodes

------------------------------------------------------------------------------*/
void ShortestPath_Dijkstra(
    const GraphType& graph,
    const NodeType & source,
    const NodeType & end,
    WeightType & path_len,
    std::vector<NodeType> & path)
{
  /*------ CODE BEGINS ------*/
  std::vector<WeightType> dist(graph.size(), INT_MAX);
  std::vector<NodeType> prev(graph.size(), -1);
  std::priority_queue<std::pair<WeightType, NodeType>, std::vector<std::pair<WeightType, NodeType>>, std::greater<std::pair<WeightType, NodeType>>> pq;
  dist[source] = 0;
  pq.push({0, source});
  while (!pq.empty())
  {
    WeightType d;
    NodeType u;
    std::tie(d, u) = pq.top();
    pq.pop();
    if (u == end)
    {
      break;
    }
    if (d > dist[u])
    {
      continue;
    }
    for (size_t i = 0; i < graph[u].size(); i++)
    {
      NodeType v = graph[u][i].first;
      WeightType w = graph[u][i].second;
      if (dist[v] > dist[u] + w)
      {
        dist[v] = dist[u] + w;
        prev[v] = u;
        pq.push({dist[v], v});
      }
    }
  }
  path_len = dist[end];
  path.clear();
  for (NodeType at = end; at != -1; at = prev[at])
  {
    path.push_back(at);
  }
  std::reverse(path.begin(), path.end());
  /*------ CODE ENDS ------*/
}



#endif
