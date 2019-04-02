/*
 * main.cpp
 *
 *  Created on: Dec 11, 2015
 *      Author: maddy
 */

#include <stdlib.h>
#include <iostream>
#include <limits.h>
#include <vector>
#include <list>
#include <fstream>
#include <stack>
#include <queue>
#include <boost/graph/adjacency_list.hpp>
#include "d_matrix.h"
#include "d_except.h"
#include "heapV.h"

using namespace boost;
using namespace std;


struct VertexProperties;
struct EdgeProperties;

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;

#define LargeValue 99999999
int numberofnodes;

struct VertexProperties
{
   pair<int,int> cell; // maze cell (x,y) value
   Graph::vertex_descriptor pred; // predecessor node
   int weight;
   bool visited;
   bool marked;
};

// Create a struct to hold properties for each edge
struct EdgeProperties
{
   int weight;
   bool visited;
   bool marked;
};

void clearVisited(Graph &g)
{
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
	// Loop over all nodes in the graph
	for (Graph::vertex_iterator vItr= vItrRange.first; vItr != vItrRange.second; ++vItr)
	{
		g[*vItr].visited = false;
	}

}

// Mark all nodes in g as not visited.

void setNodeWeights(Graph &g, int w)
{
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
	// Loop over all nodes in the graph
	for (Graph::vertex_iterator vItr= vItrRange.first; vItr != vItrRange.second; ++vItr)
	{
		g[*vItr].weight = w;
	}


}

void clearMarked(Graph &g)
{
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
	//mark the cleared values
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
		{
			g[*vItr].marked = false;
		}
}

void initializeGraph(Graph &g, ifstream &fin)
{
	EdgeProperties e;

	int i, j;
	fin >> numberofnodes;
	Graph::vertex_descriptor v;

	// Add nodes.
	for (int i = 0; i < numberofnodes; i++)
	{
		v = add_vertex(g);
	}

	while (fin.peek() != '.')
	{
		fin >> i >> j >> e.weight;
		add_edge(i, j, e, g);
	}
}

void findSpanningForest(Graph &g, Graph &sf)
{
	clearVisited(g);
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
	{
		Graph::vertex_descriptor v = *vItr;
		if (!g[v].visited)
		{
			g[v].visited = true;
			Graph::vertex_descriptor start;
			start = add_vertex(sf);
			sf[start] = g[v];
			stack <Graph::vertex_descriptor> s;
			s.push(v);
			while (!s.empty())
			{
				v = s.top();
				s.pop();
				pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange2 = adjacent_vertices(v, g);
				//check if current vertex is visited
				for (Graph::adjacency_iterator vItr = vItrRange2.first; vItr != vItrRange2.second; ++vItr)
				{
					if (!g[*vItr].visited)
					{
						g[*vItr].visited = true;
						g[*vItr].pred = v;
						s.push(*vItr);
						Graph::vertex_descriptor temp;
						temp = add_vertex(sf);
						sf[temp] = g[*vItr];
						pair<Graph::edge_descriptor, bool> checkEdge = edge(v, *vItr, g);
						EdgeProperties e;
						e.weight = g[checkEdge.first].weight;
						add_edge(v, *vItr, e, sf);
					}
				}
			}
		}
	}
}

void printSpanningForest(Graph &sf)
{
	cout <<"\nSpanning Forest Info\n" << endl;
	int totalWeight = 0, numEdges = 0, numNodes = 0;

	pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(sf);
	for (Graph::edge_iterator eItr = eItrRange.first; eItr != eItrRange.second; ++eItr)
	{
		cout << "Edge Coordinates = " << *eItr << endl;
		cout << "Edge Weight = " << sf[*eItr].weight << endl;
		totalWeight += sf[*eItr].weight;
		cout << "Visited = " << sf[*eItr].visited << endl;
		cout << "Marked =" << sf[*eItr].marked << endl << endl;
		numEdges++;
	}
	cout << "\n# Nodes = " << numberofnodes << endl;
	cout << "# Edges = " << numEdges << endl;
	cout << "Total Weight = " << totalWeight << endl;
}

bool isConnected(Graph &g)
{
	clearVisited(g);
	//push first vertex on queue
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
	Graph::vertex_iterator v1 = vItrRange.first;
	Graph::vertex_iterator v2 = vItrRange.second;
	Graph::vertex_descriptor v = *v1;
	queue<Graph::vertex_descriptor> q;
	q.push(v);
	g[v].visited = true;
	//use bfs from the first node onto other nodes
	while (!q.empty())
	{
		v = q.front();
		q.pop();
		pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange = adjacent_vertices(v, g);
		for (Graph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
		{
			if (!g[*vItr].visited)
			{
				q.push(*vItr);
			}
			g[*vItr].visited = true;
		}
	}
	//if there are any unvisited nodes, it's not connected
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange2 = vertices(g);
	for (Graph::vertex_iterator vItr = vItrRange2.first; vItr != vItrRange2.second -1; ++vItr)
	{
		if (!g[*vItr].visited)
		{
			return false;
		}
	}
	return true;
}

bool isCyclic(Graph &g)
{
	//push node onto queue
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
	{
		clearVisited(g);
		Graph::vertex_descriptor v = *vItr;
		stack<Graph::vertex_descriptor> s;
		s.push(v);
		g[v].visited = true;
		while (!s.empty())
		{
			v = s.top();
			s.pop();
			pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange = adjacent_vertices(v, g);
			for (Graph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
			{
				if ((*vItr) == g[v].pred)
				{
				}
				else if (!g[*vItr].visited)
				{
					s.push(*vItr);
					g[*vItr].pred = v;
					g[*vItr].visited = true;
				}
				else if (g[*vItr].visited)
				{
					return true;
				}
			}
		}
	}
	return false;
}

ostream& operator<<(ostream& ostr, const Graph& g)
{
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);

		int count=0;
		// Loop over all nodes in the graph
		for (Graph::vertex_iterator vItr= vItrRange.first; vItr != vItrRange.second; ++vItr)
		{
			count++;
			ostr<<"\nVertex #: "<<count;
			ostr << "\nVertex Coordinates: (" << g[*vItr].cell.first  << ", " << g[*vItr].cell.second << ")";
			ostr << "\nWeighted Value: " << g[*vItr].weight;
			if(g[*vItr].visited)
			{
				ostr << "\nVisited Value -> true";
			}
			else
			{
				ostr << "\nVisited Value -> false";
			}
			if(g[*vItr].marked)
			{
				ostr << "\nMarked Value -> true\n";
			}
			else
			{
				ostr << "\nMarked Value -> false\n";
			}

		}

		count=0;
		pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(g);

		// Loop over all edges in the graph
		for (Graph::edge_iterator eItr= eItrRange.first; eItr != eItrRange.second; ++eItr)
		{
			count++;
			ostr<<"\nEdge #: "<<count;
			ostr << "\nVertex Source of Edge: " << source(*eItr,g) + 1 << "\nVertex Target of Edge: " << target(*eItr,g) + 1;
			if(g[*eItr].visited)
			{
				ostr << "\nVisited Value -> true";
			}
			else
			{
				ostr << "\nVisited Value -> false";
			}
			if(g[*eItr].marked)
			{
				ostr << "\nMarked Value -> true\n";
			}
			else
			{
				ostr << "\nMarked Value -> false\n";
			}
		}
		return ostr;

}

void msfPrim(Graph &g, Graph &sf)
{
	clearVisited(g);
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
	{
		Graph::vertex_descriptor v = *vItr;
		//check if visited
		if (!g[v].visited)
		{
			g[v].visited = true;
			Graph::vertex_descriptor start;
			start = add_vertex(sf);
			sf[start] = g[v];
			int weight;
			heapV <Graph::edge_descriptor, Graph> minheap;
			vector <Graph::edge_descriptor> edgeVector;
			//find adjacent nodes to current node for adding edges
			pair<Graph::adjacency_iterator, Graph::adjacency_iterator> vItrRange = adjacent_vertices(v, g);
			for (Graph::adjacency_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
			{
				pair<Graph::edge_descriptor, bool> checkEdge = edge(v, *vItr, g);
				weight = g[checkEdge.first].weight;
				Graph::vertex_descriptor target1 = target(checkEdge.first, g);
				Graph::vertex_descriptor source1 = source(checkEdge.first, g);

				//check for conflicts
				if (checkEdge.second && (g[target1].visited && !g[source1].visited) || (!g[target1].visited && g[source1].visited))
				{
					edgeVector.push_back(checkEdge.first);
				}

			}
			minheap.initializeMinHeap(edgeVector, g);

			while (!edgeVector.empty())
			{
				edgeVector.pop_back();
			}

			while (minheap.size() != 0)
			{
				Graph::edge_descriptor e = minheap.extractMinHeapMinimum(g);
				Graph::vertex_descriptor target2 = target(e, g);
				Graph::vertex_descriptor source2 = source(e, g);

				//check for conflicts
				if (g[target2].visited && !g[source2].visited)
				{
					g[source2].visited = true;
					start = add_vertex(sf);
					sf[start] = g[source2];
					EdgeProperties edgeProps;
					edgeProps.weight = g[e].weight;
					add_edge(target2, source2, edgeProps, sf);
				}
				//check for conflicts
				if (!g[target2].visited && g[source2].visited)
				{
					g[target2].visited = true;
					start = add_vertex(sf);
					sf[start] = g[target2];
					EdgeProperties edgeProps;
					edgeProps.weight = g[e].weight;
					add_edge(source2, target2, edgeProps, sf);
				}

				pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(g);
				for (Graph::edge_iterator eItr = eItrRange.first; eItr != eItrRange.second; ++eItr)
				{
					Graph::vertex_descriptor target3 = target(*eItr, g);
					Graph::vertex_descriptor source3 = source(*eItr, g);
					weight = g[*eItr].weight;

					//check for conflicts
					if ((g[target3].visited && !g[source3].visited) || (!g[target3].visited && g[source3].visited))
					{
						edgeVector.push_back(*eItr);
					}
				}

				while (minheap.size() != 0)
				{
					minheap.extractMinHeapMinimum(g);
				}

				minheap.initializeMinHeap(edgeVector, g);
				while (!edgeVector.empty())
				{
					edgeVector.pop_back();
				}
			}
		}
	}
}

int main()
{
try
   {
	ifstream fin;
	   	string fileName;

		cout<<"Select the file to open\n";
		cin >>fileName;

	      	fin.open(fileName.c_str());
	      	if (!fin)
	      	{
		      cerr << "Cannot open " << fileName << endl;
		      exit(1);
	      	}

		Graph g, sf, msf;
	      	cout<<"Graph initialized"<<endl;
	      	initializeGraph(g, fin);
		fin.close();

		if (isConnected(g))
		{
			cout << "\nGraph -> connected\n";
		}
		else
		{
			cout << "\nGraph -> not connected\n";
		}

		if (isCyclic(g))
		{
			cout << "\nGraph -> cyclic.\n";
		}
		else
		{
			cout << "\nGraph -> not cyclic\n";
		}

		findSpanningForest(g, sf);
		printSpanningForest(sf);


		if (isConnected(sf))
		{
			cout << "\nSpanning forest -> connected\n";
		}
		else
		{
			cout << "\nSpanning forest -> not connected\n";
		}

		if (isCyclic(sf))
		{
			cout << "\nSpanning forest -> cyclic.\n";
		}
		else
		{
			cout << "\nSpanning forest -> not cyclic\n\n";
		}
		cout<<"Using Prim's..."<<endl;
		msfPrim(g, msf);
		printSpanningForest(msf);


		if (isConnected(msf))
		{
			cout << "\nSpanning forest -> connected\n";
		}
		else
		{
			cout << "\nSpanning forest ->s not connected\n";
		}

		if (isCyclic(msf))
		{
			cout << "\nSpanning forest -> cyclic.\n";
		}
		else
		{
			cout << "\nSpanning forest -> not cyclic\n\n";
		}

	   }

   catch (rangeError &ex)
   {
         cerr << ex.what() << endl;
         exit(1);
   }
   return 0;
}


