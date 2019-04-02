// Sample solution for project #5

#ifndef MAZE_H_
#define MAZE_H_

#include <iostream>
#include <limits.h>
#include <list>
#include <fstream>
#include <queue>
#include <vector>
#include <stack>

#include "d_except.h"
#include "d_matrix.h"
#include <boost/graph/adjacency_list.hpp>

#define LargeValue 99999999

using namespace std;
using namespace boost;

struct VertexProperties;
struct EdgeProperties;

typedef adjacency_list<vecS, vecS, bidirectionalS, VertexProperties, EdgeProperties> Graph;

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


class maze
{
public:
   maze(ifstream &fin);
   void print(int,int,int,int);
   bool isLegal(int i, int j);
   void mapMazeToGraph(Graph &g);
   void printPath(string methodName, Graph::vertex_descriptor end,
                        stack<Graph::vertex_descriptor> &s,
                        Graph g);
   int numRows(){return rows;};
   int numCols(){return cols;};
   friend ostream& operator<<(ostream& ostr, const Graph& g);
   matrix<Graph::vertex_descriptor> Mapper;

private:
   int rows; // number of rows in the maze
   int cols; // number of columns in the maze12 a
   Graph::vertex_descriptor start;
   Graph::vertex_descriptor end;

   matrix<bool> value;
};

maze::maze(ifstream &fin)
// Initializes a maze by reading values from fin.  Assumes that the
// number of rows and columns indicated in the file are correct.
{
   fin >> rows;
   fin >> cols;

   char x;

   value.resize(rows,cols);
   for (int i = 0; i <= rows-1; i++)
      for (int j = 0; j <= cols-1; j++)
      {
         fin >> x;
         if (x == 'O')
            value[i][j] = true;
         else
            value[i][j] = false;
      }
   Mapper.resize(rows,cols);

}

void maze::print(int goalI, int goalJ, int currI, int currJ)
// Print out a maze, with the goal and current cells marked on the
// board.
{
   cout << endl;

   if (goalI < 0 || goalI > rows || goalJ < 0 || goalJ > cols)
      throw rangeError("Bad value in maze::print");

   if (currI < 0 || currI > rows || currJ < 0 || currJ > cols)
      throw rangeError("Bad value in maze::print");

   for (int i = 0; i <= rows-1; i++)
   {
      for (int j = 0; j <= cols-1; j++)
      {
	 if (i == goalI && j == goalJ)
	    cout << "*";
	 else
	    if (i == currI && j == currJ)
	       cout << "+";
	    else
	       if (value[i][j])
		  cout << " ";
	       else
		  cout << "X";
      }
      cout << endl;
   }
   cout << endl;
}

bool maze::isLegal(int i, int j)
// Return the value stored at the (i,j) entry in the maze, indicating
// whether it is legal to go to cell (i,j).
{
   if (i < 0 || i > rows || j < 0 || j > cols)
      throw rangeError("Bad value in maze::isLegal");

   return value[i][j];
}

void maze::mapMazeToGraph(Graph &g)
// Create a graph g that represents the legal moves in the maze m.
{
	Graph::vertex_descriptor desc;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (isLegal(i, j)){
				desc = add_vertex(g);
				g[desc].cell.first = i;
				g[desc].cell.second = j;
				Mapper[i][j] = desc;
			}
		}
	}


	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (isLegal(i, j)){
				if (i>0 && isLegal(i - 1, j))
				{
					add_edge(Mapper[i][j], Mapper[i - 1][j], g);
				}
				if (i < rows - 1 && isLegal(i + 1, j)){
					add_edge(Mapper[i][j], Mapper[i + 1][j], g);
				}
				if (j>0 && isLegal(i, j-1)){
					add_edge(Mapper[i][j], Mapper[i][j-1], g);
				}
				if (j < cols - 1 && isLegal(i, j+1))
				{
					add_edge(Mapper[i][j], Mapper[i][j+1], g);
				}

			}
		}
	}
}

void maze::printPath(string methodName, Graph::vertex_descriptor end,
		stack<Graph::vertex_descriptor> &s,Graph g)
{
		cout << methodName << endl;
		Graph::vertex_descriptor v;
		int size =  s.size();

		while (!s.empty())
		{
			cout << "Step Number #" <<size-(s.size()-1);
			v = s.top();
			s.pop();
			cout << "  ("<< g[v].cell.first << ", " << g[v].cell.second << ")\n";
			cout << "+ indicates Position in graph " <<endl;
			print(g[end].cell.first, g[end].cell.second, g[v].cell.first, g[v].cell.second);
		}
}

ostream& operator<<(ostream& ostr, const Graph& g)
{
	pair<Graph::vertex_iterator, Graph::vertex_iterator> vItrRange = vertices(g);

		int count=0;
		// Loop over all nodes in the graph
		for (Graph::vertex_iterator vItr= vItrRange.first; vItr != vItrRange.second; ++vItr)
		{
			count++;
			ostr<<"\nVertex Number: "<<count;
			ostr << "\nVertex Coordinates: (" << g[*vItr].cell.first  << ", " << g[*vItr].cell.second << ")";
			ostr << "\nWeighted Value: " << g[*vItr].weight;
			if(g[*vItr].visited)
			{
				ostr << "\nVisited Value: true";
			}
			else
			{
				ostr << "\nVisited Value: false";
			}
			if(g[*vItr].marked)
			{
				ostr << "\nMarked Value: true\n";
			}
			else
			{
				ostr << "\nMarked Value: false\n";
			}

		}

		count=0;
		pair<Graph::edge_iterator, Graph::edge_iterator> eItrRange = edges(g);

		// Loop over all edges in the graph
		for (Graph::edge_iterator eItr= eItrRange.first; eItr != eItrRange.second; ++eItr)
		{
			count++;
			ostr<<"\nEdge Number: "<<count;
			ostr << "\nVertex Source of Edge: " << source(*eItr,g) + 1 << "\nVertex Target of Edge: " << target(*eItr,g) + 1;
			if(g[*eItr].visited)
			{
				ostr << "\nVisited Value: true";
			}
			else
			{
				ostr << "\nVisited Value: false";
			}
			if(g[*eItr].marked)
			{
				ostr << "\nMarked Value: true\n";
			}
			else
			{
				ostr << "\nMarked Value: false\n";
			}
		}
		return ostr;

}



#endif /* MAZE_H_ */
