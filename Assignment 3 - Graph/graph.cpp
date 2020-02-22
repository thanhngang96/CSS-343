#include "graph.h"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <queue>
#include <utility>

using namespace std;

//============================================================================
//constructor when graph is empty
Graph::Graph(bool DirectionalEdges)
{
	this->DirectionalEdges = DirectionalEdges;
	EdgeCount = 0;
	VertexCount = 0;
}

//============================================================================
//destructor - deletes all vertices
Graph::~Graph() 
{
	//go through each vertex and delete all of its Neighbors
	for (int I = 0; I < Vertices.size(); I++) 
	{
		Vertex* Temp = Vertices.at(I);
		for (int J = 0; J < Temp->Neighbors.size(); J++)
		{
			delete Temp->Neighbors.at(J);
		}
		Temp->Neighbors.clear();
		delete Temp;
	}
	//deletes all vertices
	Vertices.clear();
	EdgeCount = 0;
	VertexCount = 0;
}

//============================================================================
//readFile - read graph data from text file
bool Graph::readFile(const string &Filename)
{
	ifstream MyFile(Filename);
	if (MyFile.is_open())
	{
		//read the number of vertices
		int Vertices;
		MyFile >> Vertices;

		string From, To;
		int Weight;
		
		//read, connect vertices, and set weight.
		for (int I = 0; I < Vertices; I++)
		{
			MyFile >> From >> To >> Weight;
			connect(From, To, Weight);
		}
		//close file after being used.
		MyFile.close();
		return true;
	}
	//failed to read file
	return false;
}

//============================================================================
//verticesSize - get vertices size
int Graph::verticesSize() const
{
	return VertexCount; 
}

//============================================================================
//edgesSize - get edges size
int Graph::edgesSize() const 
{
	return EdgeCount; 
}

//============================================================================
//neighborsSize - get neighbors size
int Graph::neighborsSize(const string &Label) const
{
	//go through all vertices and check if Label is in the graph
	for (auto& Vertex : Vertices)
	{
		//found Label in the graph
		if (Vertex->Label == Label)
		{
			return Vertex->Neighbors.size();
		}
	}
	//when vertex not found
	return -1;
}

//============================================================================
// retrieve
// retrieve a vertex with a given label, insert Vert if found
bool Graph::retrieve(const string& Label, Vertex*& Vert) const
{
	for (auto& Vertex : Vertices) 
	{
		if (Vertex->Label == Label) 
		{
			Vert = Vertex;
			return true;
		}
	}
	return false;
}

//============================================================================
// add
// add a new vertex to graph
bool Graph::add(const string &Label) 
{
	//check if Label is in the graph
	if (contains(Label))
	{
		return false;
	}
	//add new vertex with the given label.
	auto V = new Vertex(Label);
	Vertices.push_back(V);
	VertexCount++;
	return true;
}

//============================================================================
// contains
// return true if vertex already in graph */
bool Graph::contains(const std::string &Label) const 
{ 
	//go through all vertices and check if Label is in the graph
	for (auto& Vertex : Vertices)
	{
		//found Label in the graph
		if (Vertex->Label == Label)
		{
			return true;
		}
	}
	return false;
}

//============================================================================
// getEdgesAsString
// get all edges and weight as string
string Graph::getEdgesAsString(const string &Label) const
{
	string EdgesStr = "";
	//if Vertex found
	if (contains(Label))
	{
		Vertex* Vert = nullptr;
		retrieve(Label, Vert);
		// check if there is only one vertex in the graph
		if (Vert->Neighbors.empty())
		{
			return EdgesStr;
		}
		// add first edge to EdgesStr
		EdgesStr = Vert->Neighbors.at(0)->To->Label + "("
			+ to_string(Vert->Neighbors.at(0)->Weight) + ")";
		// add other edges to EdgesStr
		for (auto I = Vert->Neighbors.begin() + 1; I != Vert->Neighbors.end(); ++I)
		{
			//add label to EdgesStr
			EdgesStr += "," + (*I)->To->Label;
			//add weight to EdgesStr
			EdgesStr += "(" + to_string((*I)->Weight) + ")";
		}
	}
	return EdgesStr;
}

//============================================================================
// connect
// connect a vertex from another vertex
bool Graph::connect(const string &From, const string &To, int Weight)
{
	//check if vertex connects to itself
	if (From == To)
	{
		return false;
	}
	//construct vertices, and edge to add to graph
	// if Vertices don't exist, then add them
	Vertex* Vert1 = nullptr;
	if (!retrieve(From, Vert1)) {
		Vert1 = new Vertex(From);
		Vertices.push_back(Vert1);
		VertexCount++;
	}
	Vertex* Vert2 = nullptr;
	if (!retrieve(To, Vert2)) {
		Vert2 = new Vertex(To);
		Vertices.push_back(Vert2);
		VertexCount++;
	}
	bool EdgeAdded = false;
	auto Edge1 = new Edge(Vert1, Vert2, Weight);
	//go through all neighbers of From vertex 
	for (int I = 0; I < Vert1->Neighbors.size(); I++)
	{
		//check if edge already in the graph
		Edge* Temp = Vert1->Neighbors.at(I);
		if (From == Temp->From->Label && To == Temp->To->Label)
		{
			delete Edge1;
			return false;
		}
		//compare Edge to add and its current neighbor 
		//to sort them in alphabetically order
		if (To < Temp->To->Label)
		{
			Vert1->Neighbors.insert(Vert1->Neighbors.begin() + I, Edge1);
			EdgeAdded = true;
			EdgeCount++;
			break;
		}
	}
	//add Edge1 to Vert1's neighbors
	if (!EdgeAdded)
	{
		Vert1->Neighbors.push_back(Edge1);
		EdgeCount++;
	}

	//add the opposite edge for non-directional graph
	bool OpEdgeAdded = false;
	if (!DirectionalEdges)
	{
		//construct Edge2 edge to add to vertices
		auto Edge2 = new Edge(Vert2, Vert1, Weight);
		//go through all neighbers of To vertex 
		for (int I = 0; I < Vert2->Neighbors.size(); I++)
		{
			//check if edge already in the graph
			Edge* Temp = Vert2->Neighbors.at(I);
			if (From == Temp->From->Label && To == Temp->To->Label)
			{
				delete Edge2;
				return false;
			}
			//compare Edge to add and its current neighbor 
			//to sort them in alphabetically order
			if (To < Temp->To->Label)
			{
				Vert2->Neighbors.insert(Vert2->Neighbors.begin() + I, Edge2);
				OpEdgeAdded = true;
				break;
			}
		}
		//check if the opposite edge is not added
		//add Edge2 edge to Vert2 vertex's neighbors
		if (!OpEdgeAdded)
		{
			Vert2->Neighbors.push_back(Edge2);
		}
	}
	return true;
}

//============================================================================
// disconnect
// disconnect a vertex from another vertex
bool Graph::disconnect(const string &From, const string &To)
{ 
	//check if From vertex is in the graph
	Vertex* Vert = nullptr;
	if (!retrieve(From, Vert))
	{
		return false;
	}
	//go through all From vertex's neighbors
	for (int I = 0; I < Vert->Neighbors.size(); I++)
	{
		//check if Edge1 exists
		Edge* Edge1 = Vert->Neighbors.at(I);
		if (From == Edge1->From->Label && To == Edge1->To->Label)
		{
			//remove all edges from Vert vertex's neighbors
			Vert->Neighbors.erase(Vert->Neighbors.begin() + I);
			delete Edge1;
			Edge1 = nullptr;
			EdgeCount--;

			//check if graph is non-directional graph
			if (!DirectionalEdges)
			{
				//check if Edge2 exists
				Vertex* Vert2 = nullptr;
				retrieve(To, Vert2);
				//go through all To vertex's neighbors
				for (int J = 0; J < Vert2->Neighbors.size(); J++)
				{
					Edge* Edge2 = Vert2->Neighbors.at(J);
					if (To == Edge2->From->Label && From == Edge2->To->Label)
					{
						//remove all edges from Vert2 vertex's neighbors
						Vert2->Neighbors.erase(Vert2->Neighbors.begin() + J);
						delete Edge2;
						Edge2 = nullptr;
						break;
					}
				}				
			}
			return true;
		}
	}	
	return false; 
}

//============================================================================
// dfs
// depth-first search
void Graph::dfs(const string &StartLabel, void Visit(const string &Label)) 
{
	//set all vertices not visited
	for (auto& Vert : Vertices)
	{
		Vert->IsVisited = false;
	}
	//check if StartLabel is in the graph
	Vertex* Vert = nullptr;
	if (!retrieve(StartLabel, Vert))
	{
		return;
	}
	//call helper function to do DFS
	dfsHelper(Vert, Visit); 
}

//============================================================================
// dfsHelper
// helper method for dfs function dfs method
void Graph::dfsHelper(Vertex* Vert, void Visit(const string& Label))
{
	//base case when Vert is nullptr
	if (Vert == nullptr)
	{
		return;
	}
	Vert->IsVisited = true; 
	Visit(Vert->Label);
	//Recur for all the vertices adjacent to Vert vertex 
	for (int I = 0; I < Vert->Neighbors.size(); I++) 
	{
		Vertex* Temp = Vert->Neighbors.at(I)->To;
		if (!Temp->IsVisited) 
			dfsHelper(Temp, Visit); 
	}
}
//============================================================================
// bfs
// breadth-first search
void Graph::bfs(const string &StartLabel, void Visit(const string &Label)) 
{
	//set all vertices not visited
	for (auto& Vert : Vertices)
	{
		Vert->IsVisited = false;
	}
	//check if StartLabel is in the graph
	Vertex* Vert = nullptr;
	if (!retrieve(StartLabel, Vert))
	{
		return;
	}
	//Vert is checked, so it is visited
	Vert->IsVisited = true;

	//create a queue and push Vert vertex to the queue
	queue<Vertex*> Q;
	Q.push(Vert);
	while (!Q.empty())
	{
		//put Temp vertex infront of the queue
		//and then pop the first element of the queue
		Vertex* Temp = Q.front(); 
		Q.pop(); 
		Visit(Temp->Label); 
		//go through Temp vertex neighbors
		//set them visited while pushing them into the queue
		for (int I = 0; I < Temp->Neighbors.size(); I++)
		{
			Vertex* V = Temp->Neighbors.at(I)->To;
			if (!V->IsVisited) 
			{ 
				V->IsVisited = true; 
				Q.push(V); 
			}
		}
	}
}

//============================================================================
// dijkstra
// store the weights in a map
// store the previous label in a map
pair<map<string, int>, map<string, string>>
Graph::dijkstra(const string &StartLabel) const
{
  map<string, int> Weights;
  map<string, string> Previous;

  //go through all vertices and mark them unvisited
  for (auto& Vert : Vertices)
  {
	  Vert->IsVisited = false;
  }

  //check if StartLabel is in the graph
  Vertex* Vert = nullptr;
  if (!retrieve(StartLabel, Vert))
  {
	  return make_pair(Weights, Previous);
  }
  //create a vector of vertex pointers to hold visited vertices
  vector<Vertex*> VisitedVertices; 
  //visited the first element
  Vert->IsVisited = true; 
  //store Vert in visited vertices vector
  VisitedVertices.push_back(Vert);

  //go through all visited vertices
  for (int I = 0; I < VisitedVertices.size(); I++) 
  {
	  //create ShortestEdges vector from each visited vertex
	  vector<Edge*> ShortestEdges = findShortestEdges(VisitedVertices);
	  //set Temp as the shortest edge
	  Edge* Temp = findAShortestEdge(ShortestEdges, Weights);
	  //Stop when all vertices are visited
	  if (Temp == nullptr)
	  {
		  break;
	  }
	  //set Temp-To edge as visited
	  //and push it to visited vertices vector
	  Temp->To->IsVisited = true;
	  VisitedVertices.push_back(Temp->To);
	  //find Temp-From edge in Weights and Previous map
	  auto It = Weights.find(Temp->From->Label);
	  //if the edge is not in the map
	  //insert Temp's Label and Weight
	  if (It == Weights.end())
	  {
		
		  Weights.emplace(Temp->To->Label, Temp->Weight);
		  Previous.emplace(Temp->To->Label, Temp->From->Label);
	  }
	  //otherwise 
	  else
	  {
		  Weights.emplace(Temp->To->Label, (*It).second + Temp->Weight);
		  Previous.emplace(Temp->To->Label, Temp->From->Label);
	  }
  }
  return make_pair(Weights, Previous);
}

//============================================================================
// findShortestEdges
// find all shortest edges from each vertex in visited vertices
vector<Edge*> Graph::findShortestEdges(vector<Vertex*> VisitedVertices) const
{
	//create a vector to hold all shortest edges 
	vector<Edge*> ShortestEdges;
	//go through all visited edges
	for (int I = 0; I < VisitedVertices.size(); I++)
	{
		//create TempNeighbors vector to hold all neighbors of vertex at I
		vector<Edge*> TempNeighbors = VisitedVertices.at(I)->Neighbors;
		//create an edge pointer to the shortest edge from vertex at I
		Edge* ShortestEdge;
		//check if TempNeighbors has no neighbors
		//erase vertex at I from VisitedVertices
		//then go to the next vertex
		if (TempNeighbors.empty())
		{
			VisitedVertices.erase(VisitedVertices.begin() + I);
			I--;
			continue;
		}
		int E = 0;
		// set ShortestEdge to first Neighbor
		ShortestEdge = TempNeighbors.at(E);
		//ShortestEdge has been Visited
		while ((E + 1 < TempNeighbors.size()) && (ShortestEdge->To->IsVisited))
		{
			//set ShortestEdge to next TempNeighbors
			ShortestEdge = TempNeighbors.at(++E);
		}
		//go through all neighbors of TempNeighbors
		for (int J = E + 1; J < TempNeighbors.size(); J++)
		{
			//check if its neighbors has been visited
			//go to the next vertex
			Edge* TempEdge = TempNeighbors.at(J);
			if (TempEdge->To->IsVisited)
			{
				continue;
			}
			//check if TempEdge's weight is smaller than ShortestEdge's weight
			if (TempEdge->Weight < ShortestEdge->Weight)
			{
				ShortestEdge = TempEdge;
			}
		}
		//check if ShortestEdge is nullptr or has been visited,
		//erase vertex at I from VisitedVertices
		//then go to the next vertex
		if (ShortestEdge == nullptr || ShortestEdge->To->IsVisited)
		{
			VisitedVertices.erase(VisitedVertices.begin() + I);
			I--;
			continue; 
		}
		//add the shortest edge to ShortestEdges vector
		ShortestEdges.push_back(ShortestEdge);
	}
	return ShortestEdges;
}


//============================================================================
// findAShortestEdge 
// find a shortest edge among All edges
Edge* Graph::findAShortestEdge(vector<Edge*> Edges, map<string, int> Weights)
const
{
	//check if Edges is empty
	if (Edges.empty())
	{
		return nullptr;
	}
	//set ShortestEdge to the first element of Edges
	Edge* ShortestEdge = Edges.at(0);
	//go through all Edges
	for (int I = 1; I < Edges.size(); I++) 
	{	
		//find edge with shortest path from From vertex
		Edge* TempEdge = Edges.at(I);
		auto ItShortest = Weights.find(ShortestEdge->From->Label);
		auto ItTemp = Weights.find(TempEdge->From->Label);

		//set the shortest path length
		int ShortestPath;
		if (ItShortest == Weights.end())
		{
			ShortestPath = 0;
		}
		else
		{
			ShortestPath = (*ItShortest).second;
		}
		//set the temp path length
		int TempPath;
		if (ItTemp == Weights.end())
		{
			TempPath = 0;
		}
		else
		{
			TempPath = (*ItTemp).second;
		}
		//compare edges to pick the shortest one
		if ((TempEdge->Weight + TempPath) < (ShortestEdge->Weight + ShortestPath))
		{
			ShortestEdge = TempEdge;
		}
	}
	return ShortestEdge;
}

//============================================================================
 /* minimum spanning tree
 * @param function to be called on each edge
 * @return length of the minimum spanning tree or -1 if start vertex not found
 */
int Graph::mst(const string &StartLabel,
               void Visit(const string &From, const string &To,
                          int Weight)) const 
{
	//check if graph is not directional
	assert(!DirectionalEdges);
	//go through all vertices and mark them unvisited
	for (auto& Vert : Vertices)
	{
		Vert->IsVisited = false;
	}
	//check if start vertex is in the graph
	Vertex* Vert = nullptr;
	if (!retrieve(StartLabel, Vert))
	{
		return -1;
	}
	Vert->IsVisited = true;
	//create minimum spanning tree vector
	vector<Vertex*> MSTree; 
	//push Vert to MSTree vector
	MSTree.push_back(Vert);
	//create total edge weight of MSTree
	int TotalEdgeWeight = 0; 
	//go through all vertices in MSTree
	for (int I = 0; I < MSTree.size(); I++)
	{
		// find shortest edges that hasn't been visited
		vector<Edge*> ShortestEdges = findShortestEdges(MSTree);
		Edge* TempEdge = minWeightEdge(ShortestEdges);
		if (TempEdge == nullptr)
		{
			break;
		}
		//set TempEdge-To edge as visited
		TempEdge->To->IsVisited = true;
		//push the visited vertex to MSTree
		MSTree.push_back(TempEdge->To);

		Visit(TempEdge->From->Label, TempEdge->To->Label, TempEdge->Weight);
		TotalEdgeWeight += TempEdge->Weight;
	}
	return TotalEdgeWeight;
}
//============================================================================
// minEdge
// find edge with minimum weight in Edges vector
Edge* Graph::minWeightEdge(vector<Edge*> Edges) const
{
	//check if vector is empty 
	if (Edges.empty())
	{
		return nullptr;
	}
	//set edge with minimum weight the first element of Edges vector 
	Edge* MinEdge = Edges.at(0);
	//go through all Edges to find minimum weight edge
	for (int I = 1; I < Edges.size(); I++)
	{
		Edge* Temp = Edges.at(I);
		//compare  Temp's weight and MinEdge's weight
		//to determine the edge with minimum weight
		if (Temp->Weight < MinEdge->Weight)
		{
			MinEdge = Temp;
		}
	}
	return MinEdge;
}