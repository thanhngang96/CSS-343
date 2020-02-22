/**
 * A graph is made up of vertices and edges.
 * Vertex labels are unique.
 * A vertex can be connected to other vertices via weighted, directed edge.
 * A vertex cannot connect to itself or have multiple edges to the same vertex
 */

#ifndef GRAPH_H
#define GRAPH_H

#include "edge.h"
#include "vertex.h"
#include <map>
#include <string>

using namespace std;

class Graph {
public:
  // constructor, empty graph
  explicit Graph(bool DirectionalEdges = true);

  /** destructor, delete all vertices and edges */
  ~Graph();

  // @return true if vertex added, false if it already is in the graph
  bool add(const string &Label);

  // @return true if vertex is in the graph
  bool contains(const string &Label) const;

  // @return total number of vertices
  int verticesSize() const;

  // Add an edge between two vertices, create new vertices if necessary
  // A vertex cannot connect to itself, cannot have P->P
  // For digraphs (directed graphs), only one directed edge allowed, P->Q
  // Undirected graphs must have P->Q and Q->P with same weight
  // @return true if successfully connected
  bool connect(const string &From, const string &To, int Weight = 0);

  // Remove edge from graph
  // @return true if edge successfully deleted
  bool disconnect(const string &From, const string &To);

  // @return total number of edges
  int edgesSize() const;

  // @return number of edges from given vertex, -1 if vertex not found
  int neighborsSize(const string &Label) const;

  // @return true if found a vertex with the same label, retrieve it using Vert
  bool retrieve(const string& Label, Vertex*& Vert) const;

  // @return string representing edges and weights, "" if vertex not found
  // A-3->B, A-5->C should return B(3),C(5)
  string getEdgesAsString(const string &Label) const;

  // Read edges from file
  // first line of file is an integer, indicating number of edges
  // each line represents an edge in the form of "string string int"
  // vertex labels cannot contain spaces
  // @return true if file successfully read
  bool readFile(const string &Filename);

  // depth-first traversal starting from given startLabel
  void dfs(const string &StartLabel, void Visit(const string &Label));

  //dfsHelper - helper method for dfs function dfs method
  void dfsHelper(Vertex* Vert, void Visit(const string& Label));

  // breadth-first traversal starting from startLabel
  // call the function visit on each vertex label */
  void bfs(const string &StartLabel, void Visit(const string &Label));

  // dijkstra's algorithm to find shortest distance to all other vertices
  // and the path to all other vertices
  // Path cost is recorded in the map passed in, e.g. weight["F"] = 10
  // How to get to the vertex is recorded previous["F"] = "C"
  // @return a pair made up of two map objects, Weights and Previous
  pair<map<string, int>, map<string, string>>
  dijkstra(const string &StartLabel) const;

  // @return shortest edges from each vertex among all vertices
  vector<Edge*> findShortestEdges(vector<Vertex*> VisitedVertices) const;

  // @return a shortest edge from all edges
  Edge* findAShortestEdge(vector<Edge*> Edges, map<string, int> Weights)
	  const;
  // @return edge with minimum weight in Edges
  Edge* minWeightEdge(vector<Edge*> Edges) const;

  // minimum spanning tree
  // ONLY works for NONDIRECTED graphs
  // ASSUMES the edge [P->Q] has the same weight as [Q->P]
  // @return length of the minimum spanning tree or -1 if start vertex not
  int mst(const string &StartLabel,
          void Visit(const string &From, const string &To, int Weight)) const;

private:
  // default is directional edges is true,
  // can only be modified when graph is initially created
  // when set to false,
  // create 2 edges, one from P->Q and another from Q->P with same weight
  bool DirectionalEdges;

  //counting number of edges
  int EdgeCount; 

  //counting number of vertices
  int VertexCount;

  //all vertices in the graph
  vector<Vertex*> Vertices;
};

#endif // GRAPH_H