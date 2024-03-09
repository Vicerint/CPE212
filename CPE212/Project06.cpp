// Michael Agnew
// Project 06, Graphs
// Project Due Date: November 26th, 2023
// CPE 212/02, Based Professor James



#include "graph.h"


Graph::Graph()
{
  vertices = NULL;
}									
  // Graph()
  // Constructor initializes vertices linked list to empty

Graph::~Graph()
{
  while (vertices != NULL)
  {

    VertexNode* tempV = vertices;
    vertices = vertices->nextVertex;
    EdgeNode* edgePtr = tempV->edgePtr;


    while (edgePtr != NULL)
    {
      EdgeNode* tempE = edgePtr;

      edgePtr = edgePtr->nextPtr;
      
      delete tempE;
    }

    delete tempV;
  }	
}
  // ~Graph()
  // For each VertexNode in the vertices list, Destructor deallocates all EdgeNodes before
  // deallocating the VertexNode itself


void Graph::AddVertex(string v)
{
  if (!IsPresent(v))
  {
    VertexNode* newV = new VertexNode; // allocating a new node

    newV->vname = v; // setting the new vertex pointer's name to v 
    newV->mark = false; // setting the mark to false because new vertex 
    newV->edgePtr = NULL; // setting the edge to null because it's a new vertex bruh
    newV->nextVertex = vertices; // putting the slot after the new vertex at vertices

    vertices = newV; // setting vertices to new vertex 
  }
}		
  // AddVertex()
  // Adds vertex to graph assuming vertex not already present

void Graph::AddEdge(string s, string d, int w)
{
  VertexNode* source = WhereIs(s);
  VertexNode* desV = WhereIs(d);

  EdgeNode* newE; // making a new node temp
  try 
  {
    newE = new EdgeNode; // allocating a NEW NODE 
  }
  catch (bad_alloc) // catch those bad boys
  {
    throw (GraphFull());
  }


  newE->destination = desV; // setting the destination of new edge to the destination vector
  newE->weight = w; // setting the weight of the new edge to the int w
  newE->nextPtr = source->edgePtr; // setting the next pointer from new edge to the source of the edge pointer 
  source->edgePtr = newE; // setting the source of the edge pointer to the new edge 

}		
  // AddEdge()
  // Adds edge from source S  to destination D with specified weight W.
  // If there is not enough memory to add the edge, throw the GraphFull exception

bool Graph::IsPresent(string v)
{
  return (WhereIs(v) != NULL); // returning whether or not the vector exists
}	
  // IsPresent()
  // Returns true if vertex V in graph, false otherwise


VertexNode*  Graph::WhereIs(string v)
{
  VertexNode* currentV = vertices;
  while (currentV != NULL) // loop until reaching the end
  {
    if (currentV->vname == v) // if currentV's name is equal to v then return the vector
    {
        return (currentV);
    }

    currentV = currentV->nextVertex;
  }


}		/* Note: This function replaces IndexIs */
  // WhereIs()
  // Returns pointer to the vertex node that stores vertex v in the vertices linked list; 
  // Throws GraphVertexNotFound if V is not present in the vertices list

int  Graph::WeightIs(string s, string d)
{

  VertexNode* source = WhereIs(s); // finding the source vector

  VertexNode* desV = WhereIs(d); // finding the destination vector

  if (source == NULL || desV == NULL)
  {
      throw GraphVertexNotFound(); // throwing the vertex not found if source or desV are NULL

  }

  EdgeNode* edgePtr = source->edgePtr; 


  while (edgePtr != NULL) // looping through the edgeptr until the end 
  {
    if (edgePtr->destination == desV)
    {
      return (edgePtr->weight);

    }
    edgePtr = edgePtr->nextPtr;
  }

  throw (GraphEdgeNotFound()); // if there is no edge found, then throw GraphEdgeNotFound

}
  // WeightIs()
  // Returns weight of edge (s,d).  Throws GraphEdgeNotFound if edge not present.

void Graph::ClearMarks()
{

  VertexNode* currentV = vertices; // setting a current vector equal to vertices

  while (currentV != NULL) // looping through the entire graph until currentV is NULL
  {
    currentV->mark = false; // make all of the makrs FALSE
    currentV = currentV->nextVertex;

  }

}		
  // ClearMarks()
  // Clears all vertex marks

void Graph::MarkVertex(string v)
{
  VertexNode* vertex = WhereIs(v);
  if (vertex != NULL) 
  {
      vertex->mark = true;
  }
}	
  // MarkVertex()
  // Marks vertex V as visited

bool Graph::IsMarked(string v)
{
  
  VertexNode* vertex = WhereIs(v); // make a vertex varaible and locate v


  if (vertex != NULL) // make sure that vertex is not NULL
  {

    return vertex->mark; // if you find the vertex than check whether or not it is marked

  }
  else  // otherwise
  {
    return false; // there is no mark so return FALSE

  }

}		
  // IsMarked()
  // Returns true if vertex V is marked, false otherwise

void Graph::GetToVertices(string V, queue<string>& q)
{

  VertexNode* vertex = WhereIs(V); // finding vertex

  if (vertex != NULL) // making sure that vertex is not NULL
  {

    EdgeNode* edgePtr = vertex->edgePtr; // setting edgePtr equal to the edge of vertex

    while (edgePtr != NULL) // looping until at the end
    {
      q.push((edgePtr->destination)->vname); // pushing the destination and name of the edge onto the queue

      edgePtr = edgePtr->nextPtr; // moving edge to the next pointer

    }

  }

}	
  // GetToVertices()
  // Returns queue Q of vertex names of those vertices adjacent to vertex V
  // The queue here is from the Standard Template Library

void Graph::DepthFirstSearch(string startVertex, string endVertex, queue<string>& path)
{
  if ((!IsPresent(startVertex)) || (!IsPresent(endVertex)))
    {
      throw GraphVertexNotFound();
    }

    stack<string> myStack;
    queue<string> myQueue;

    bool bruh = false;

    string vertex;
    string item;

    ClearMarks();

    myStack.push(startVertex);
    do
    {
      vertex = myStack.top();
      myStack.pop();

      if (vertex == endVertex)
      {
        bruh = true;
        path.push(vertex);

      }
      else
      {
        if (!IsMarked(vertex))
        {

          MarkVertex(vertex);
          path.push(vertex);
          GetToVertices(vertex, myQueue);

          while (!myQueue.empty())
          {
            item = myQueue.front();
            myQueue.pop();

            if (!IsMarked(item))
            {
              myStack.push(item);

            }

          }
        }

        }

    } while (!myStack.empty() && !bruh);

    if (!bruh)
    {
      while (path.empty() != true)
      {
        path.pop();

      }
    }
}


  // DepthFirstSearch()
  // Uses the DFS algorithm from the CPE 212 textbook to determine a path from the
  // startVertex to the endVertex.  If a path is found, the path vertices should
  // be in the path queue.  If no path is found, the path queue should be emptied
  // as a signal to the client code that no path exists between the start and
  // end vertices.
  //
  // Notes:
  // (1) This algorithm is flawed in that as it searches for a path, it may
  // output some additional vertices that it visited but were not part
  // of the actual path.  Implement the algorithm just as it appears in the textbook.
  // 
  // (2) This algorithm requires use of the stack and queue containers from the
  // Standard Template Library.  The STL stack and queue interfaces may require
  // minor modifications to the DFS code from the textbook.


