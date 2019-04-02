/*
 * main.cpp
 *
 *  Created on: Nov 9, 2015
 *      Author: maddy
 */


#include <iostream>
#include <limits.h>
#include <vector>
#include <list>
#include <fstream>
#include <queue>
#include <cstdlib>
#include "heapV.h"
#include "maze.h"

#include <boost/graph/adjacency_list.hpp>

using namespace boost;
using namespace std;

struct VertexProperties;
struct EdgeProperties;

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;

#define LargeValue 99999999


void clearVisited(Graph &g)
// Mark all nodes in g as not visited.
{
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vRange = vertices(g);
		// for loop for nodes
		for (Graph::vertex_iterator v= vRange.first; v != vRange.second; ++v)
		{
			g[*v].visited = false;
		}

}

void setNodeWeights(Graph &g, int w)
// Set all node weights to w.
{
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vRange = vertices(g);
	// for loop for nodes
	for (Graph::vertex_iterator v= vRange.first; v != vRange.second; ++v)
	{
		g[*v].weight = w;
	}

}

void clearMarked(Graph &g)
{
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vRange = vertices(g);

	for (Graph::vertex_iterator v = vRange.first; v != vRange.second; ++v)
		{
			g[*v].marked = false;
		}
}

void initializeGraph(Graph &g,
		     Graph::vertex_descriptor &start,
		     Graph::vertex_descriptor &end,
		     ifstream &fin)
// Initialize g using data from fin.  Set start and end equal
// to the start and end nodes.
{
   EdgeProperties e;

   int n, i, j;
   int startId, endId;
   fin >> n;
   fin >> startId >> endId;
   Graph::vertex_descriptor v;

   // Add nodes.
   for (int i = 0; i < n; i++)
   {
      v = add_vertex(g);
      if (i == startId)
	 start = v;
      if (i == endId)
	 end = v;
   }

   while (fin.peek() != '.')
   {
      fin >> i >> j >> e.weight;
      add_edge(i,j,e,g);
   }
}


void relax(Graph &g,  Graph::vertex_descriptor u, Graph::vertex_descriptor v)
{
	pair<Graph::edge_descriptor, bool> checkEdge = edge(u, v, g);
	if ( (g[v].weight > g[u].weight + g[checkEdge.first].weight) && checkEdge.second)
	{
		g[v].weight = g[u].weight + g[checkEdge.first].weight;
		g[v].pred = u;

	}
}

bool dijskstra(Graph &g, Graph::vertex_descriptor &s)
{
	setNodeWeights(g, LargeValue); //set node weights to infinity
	g[s].weight = 0; //sets the start weight to zero due to it having zero distance
	vector<Graph::vertex_descriptor> q;

	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
	{
		q.push_back(*vItr); //push vertices onto q
	}
	heapV <Graph::vertex_descriptor, Graph> minheap;
	minheap.initializeMinHeap(q, g); //push nodes onto min Heap

	while (minheap.size() != 0)
	{
		Graph::vertex_descriptor u = minheap.extractMinHeapMinimum(g); //extracts minimum
		for (int i = 0; i < minheap.size(); i++)
		{
			Graph::vertex_descriptor v = minheap.getItem(i);
			//check if u and v make an edge for the minheap
			pair<Graph::edge_descriptor, bool> checkEdge = edge(u, v, g);
			if (checkEdge.second)
			{
				relax(g, u, v);
				minheap.minHeapDecreaseKey(minheap.getIndex(v), g);
			}
		}
	}

	//Check if path is reachable
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange2 = vertices(g);
	for (Graph::vertex_iterator vItr = vItrRange2.first; vItr != vItrRange2.second; ++vItr)
	{
		if (g[*vItr].weight == LargeValue)
		{
			return false; //if a node is unreachable, return false
		}
	}
	return true;
}


bool bellmanFord(Graph &g, Graph::vertex_descriptor &s)
{
	setNodeWeights(g, LargeValue); //LargeValue represents infinity
	g[s].weight = 0; //sets start node distance to zero

	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);
	//Relax the paths for Bellman Ford
	for (Graph::vertex_iterator vItr = vItrRange.first; vItr != vItrRange.second; ++vItr)
	 {
		pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(g);
		for (Graph::edge_iterator eItr = eItrRange.first; eItr != eItrRange.second; ++eItr)
		{
			Graph::vertex_descriptor u = source(*eItr, g);
			Graph::vertex_descriptor v = target(*eItr, g);
			relax(g, u, v);
		}
	}

	//Check for negative weights
	pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange2 = edges(g);
	for (Graph::edge_iterator eItr = eItrRange2.first; eItr != eItrRange2.second; ++eItr)
	{
		Graph::vertex_descriptor u = source(*eItr, g);
		Graph::vertex_descriptor v = target(*eItr, g);
		pair<Graph::edge_descriptor, bool> checkEdge = edge(u, v, g);
		if (g[v].weight > g[u].weight + g[checkEdge.first].weight)
		{
			return false; //check if there is a negative weight
		}
	}
	return true;
}




void printPath(Graph &g, Graph::vertex_descriptor &start, Graph::vertex_descriptor &end)
{
	if (g[end].weight == LargeValue)
	{
		cout << "Shortest Path Does Not Exist" << endl;
	}
	else
	{
		Graph::vertex_descriptor tempNode = end;
		vector<Graph::vertex_descriptor> path;

		while (tempNode != start)
		{
			path.push_back(tempNode);
			tempNode = g[tempNode].pred;
		}

		path.push_back(start);
		while (path.size() != 0)
		{
			tempNode = path.back();
			cout << "Node #"<< tempNode + 1 << endl;
			path.pop_back();
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

	Graph g;
	Graph::vertex_descriptor start;
	Graph::vertex_descriptor end;

      	cout<<"Graph Initialized"<<endl;
      	initializeGraph(g, start, end, fin);
	fin.close();

	cout <<"Starting Dijsktra"<<endl;
	bool result_D;
	result_D = dijskstra(g, start);
	if (result_D)
	{
		cout << "Shortest Path Exists" << endl;
		printPath(g, start, end);
	}
	else
	{
		cout << "Shortest Path Does Not Exist" << endl;
	}

	cout << "Starting Bellman-Ford"<<endl;
	bool result_BF;
	result_BF = bellmanFord(g, start);
	if (result_BF)
	{
		cout << "0 negative cycles found" << endl;
		printPath(g, start, end);
	}
	  else
	{
		cout << "Negative cycle found" << endl;
	}

   }
   catch (rangeError &ex)
{
	   cout << ex.what() << endl;
	   exit(1);
   }
}
