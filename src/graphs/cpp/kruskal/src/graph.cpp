
#include "graph.h"
#include <algorithm>
#include <iterator>
#include <sstream>

template <class T> Vertex<T>::Vertex() {}

template <class T> Vertex<T>::Vertex(T _value) : value(_value) {}

template <class T>
Vertex<T>::Vertex(const Vertex<T> &vertex) : value(vertex.value) {}

template <class T> bool Vertex<T>::operator==(const Vertex<T> &other) const {
  return value == other.value;
}

template <class T> bool Vertex<T>::operator!=(const Vertex<T> &other) const {
  return value != other.value;
}

template <class T> bool Vertex<T>::operator<(const Vertex<T> &other) const {
  return value < other.value;
}

template <class T>
size_t HashFunction<T>::operator()(const Vertex<T> &vertex) const {
  return std::hash<T>()(vertex.value);
}

template <class T>
Edge<T>::Edge(Vertex<T> _source, Vertex<T> _destination, int _distance)
    : source(_source), destination(_destination), distance(_distance) {}

template <class T> bool Edge<T>::operator==(const Edge<T> &other) const {
  return source == other.source && destination == other.destination &&
         distance == other.distance;
}

template <class T> bool Edge<T>::operator!=(const Edge<T> &other) const {
  return source != other.source || destination != other.destination ||
         distance != other.distance;
}

template <class T> bool Edge<T>::operator<(const Edge<T> &other) const {
  return distance < other.distance;
}

template <class T> Graph<T>::Graph() {}

template <class T>
Graph<T>::Graph(
    std::unordered_map<Vertex<T>, std::vector<Edge<T>>, HashFunction<T>>
        adjcDict)
    : adjcDict(adjcDict) {}

template <class T> void Graph<T>::addEdge(Edge<T> edge) {
  auto source = edge.source;
  auto destination = edge.destination;

  if (contains(source))
    adjcDict[source].emplace_back(edge);

  else
    adjcDict[source] = std::vector<Edge<T>>{edge};

  if (!contains(destination))
    adjcDict[destination] = std::vector<Edge<T>>{};
}

template <class T>
void Graph<T>::addEdge(Vertex<T> source, Vertex<T> destination, int distance) {
  addEdge(Edge<T>(source, destination, distance));
}

template <class T> void Graph<T>::addVertex(Vertex<T> vertex) {
  if (!contains(vertex))
    adjcDict[vertex] = std::vector<Edge<T>>{};
}

template <class T> std::vector<Vertex<T>> Graph<T>::vertices() const {
  std::vector<Vertex<T>> result;

  for (const auto &[key, _] : adjcDict)
    result.emplace_back(key);

  return result;
}

template <class T>
std::vector<Edge<T>> Graph<T>::edgesFromVertex(const Vertex<T> vertex) const {
  if (!contains(vertex))
    throw std::invalid_argument("Graph<T> doesn't contain given vertex.");

  return adjcDict.at(vertex);
}

template <class T> std::vector<Edge<T>> Graph<T>::edges() const {
  std::vector<Edge<T>> result;

  for (auto [vertex, _edges] : adjcDict) {
    std::copy(_edges.begin(), _edges.end(), std::back_inserter(result));
  }

  return result;
}

template <class T> bool Graph<T>::contains(const Vertex<T> vertex) const {
  return adjcDict.find(vertex) != adjcDict.end();
}

template <class T>
bool Graph<T>::connected(const Vertex<T> source,
                         const Vertex<T> destination) const {
  if (!contains(source) || !contains(destination))
    return false;

  for (auto &edge : adjcDict.at(source)) {
    if (edge.destination == destination)
      return true;
  }

  return false;
}

template <class T> unsigned int Graph<T>::size() const {
  return adjcDict.size();
}

template <class T> bool Graph<T>::empty() const { return adjcDict.empty(); }

template <class T> std::string Graph<T>::toString() const {
  std::string result;

  for (auto const &[vertex, edges] : adjcDict) {

    std::ostringstream oss;
    for (const auto &edge : edges) {
      oss << std::to_string(edge.destination.value) + ", ";
    }

    auto edgesStr = oss.str();

    if (edgesStr.size() > 1)
      edgesStr.erase(edgesStr.size() - 2);

    result += std::to_string(vertex.value) + " : " + edgesStr + "\n";
  }

  if (result.size() > 1)
    result.erase(result.size() - 1);

  return result;
}

template class Vertex<int>;
template class Vertex<float>;
template class Vertex<double>;
template class Vertex<char>;

template class Edge<int>;
template class Edge<float>;
template class Edge<double>;
template class Edge<char>;

template class Graph<int>;
template class Graph<float>;
template class Graph<double>;
template class Graph<char>;
