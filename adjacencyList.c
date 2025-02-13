﻿/* AdjacencyList.c */

#include <stdio.h>
#include <stdlib.h>
#include "adjacencyList.h"


/*  InitGraph
	---------
	General: Allocates memory for base vertices of an
	Adjacency List for Graph G, sets bases to Vertices
	of G and edges to NULL.
	
	input: List of a Graph, base n - end v.
	
	output: none.
*/
void initGraph(PGraph G, Vertex V[], int VSize)
{
	int i;
	G->vertices = (PAdjNode) malloc(sizeof(AdjNode) * VSize);
	for (i = 0; i < VSize; i++)
	{
		G->vertices[i].v = V[i];
		G->vertices[i].adjv = NULL;
	}
}

/*  AddEdge
	------
	General: Adds edge from n to v
	
	input: List of a Graph, base n - end v.
	
	output: none.
*/
void addEdge(PAdjNode n, PVertex v)
{
	PAdjNode new = malloc(sizeof(AdjNode));
	new->v = *v;
	new->adjv = n->adjv;
	n->adjv = new;
}

/*  AddEdge
	------
	General: Removes edge from 'in' to 'out', if (in, out) ∈ E

	input: Graph Pointer G, number of vertices 'VSize', vertex 'in' and 'out'.

	output: none.
*/
void deleteEdge(PGraph G, int VSize, PVertex in, PVertex out)
{
	PAdjNode prev,n;
	
	if (isEdge(G, VSize, in, out))
	{
		prev = _findPreviousEdge(G, VSize, in, out);
		n = prev->adjv;
		prev->adjv = prev->adjv->adjv;
		free(n);
	}
	else
	{
		printf("Edge (%c, %c) not found. no action performed.\n", out->value, in->value);
	}
}

/*  IsEdge 
	------
	General: Finds if there is an edge (out, in) in Graph G i.e. (out, in) ∈ E
	
	input: Graph 'G', base of edge 'out', end of edge 'in'.
	
	output: returns 1 if edge exists, 0 if not.

*/
int isEdge(PGraph G, int VSize, PVertex out, PVertex in)
{
	if (_findEdge(G, VSize, out, in) == NULL)
		return 0;
	return 1;
}



/*  FindEdge (PRIVATE METHOD)
	--------
	General: Finds Address of Edge (out, in) if such exists in Graph G

	input: Graph 'G', base of edge 'out', end of edge 'in'.

	output: returns Address if edge exists, NULL if not.

*/
PAdjNode _findEdge(PGraph G, int VSize, PVertex out, PVertex in) // O(V+E)
{
	PAdjNode n = _findPreviousEdge(G, VSize, out, in);
	if (n == NULL)
		return NULL;
	return n->adjv;
}


/*  FindEdge (PRIVATE METHOD)
	--------
	General: Finds Address of Edge preceding (out, in) if such exists in Graph G

	input: Graph 'G', base of edge 'out', end of edge 'in'.

	output: returns Address of preceding Edge if (out, in) exists, NULL if not.

*/
PAdjNode _findPreviousEdge(PGraph G, int VSize, PVertex out, PVertex in) // O(V+E)
{
	int i;
	PAdjNode n;

	for (i = 0; i < VSize; i++)
	{
		if (G->vertices[i].v.value == out->value)
		{
			n = &G->vertices[i];
			while (n->adjv != NULL)
			{
				if (n->adjv->v.value == in->value)
					return n;
				n = n->adjv;
			}
			return NULL;
		}
	}
	return NULL;
}

void printGraph(PGraph G, int VSize)
{
	int i;
	PAdjNode adj;

	for (i = 0; i < VSize; i++)
	{
		printf("%c - ", G->vertices[i].v.value);
		adj = G->vertices[i].adjv;
		while (adj != NULL)
		{
			printf("%c -> ", adj->v.value);
			adj = adj->adjv;
		}
		printf("NULL\n");
	}
}


/*  OutDegree
	---------
	General: Finds amount of Edges coming OUT OF vertex V i.e. V's Out-Degree.

	input: Graph 'G', Length of G, and Vertex to find it's Out-Degree.

	output: returns amount of edges coming OUT OF vertex V, if V is not member of G, returns -1.
*/
int outDegree(PGraph G, int VSize, PVertex v)
{
	int counter=0;
	PAdjNode n;
	n = _isVertexOf(G, VSize, v);
	if (n == NULL)
		return -1;
	n = n->adjv;
	while (n != NULL)
	{
		counter++;
		n = n->adjv;
	}
	return counter;
}

/*  InDegree
	--------
	General: Finds amount of Edges coming INTO vertex v i.e. v's In-Degree.

	input: Graph 'G', Length of G, and Vertex v to find it's Out-Degree.

	output: returns amount of edges coming INTO vertex v, if v is not member of G, returns -1.
*/
int inDegree(PGraph G, int VSize, PVertex v)
{
	int i, counter=0;
	PAdjNode n;
	if (_isVertexOf(G, VSize, v) == NULL)
		return -1;
	
	for (i = 0; i < VSize; i++)
	{
		n = G->vertices[i].adjv;
		while (n != NULL)
		{
			if (n->v.value == v->value)
				counter++;
			n = n->adjv;
		}
	}

	return counter;
}


/*  isVertexOf (PRIVATE FUNCTION)
	--------
	General: Finds if Vertex v is in Graph G, and retrieves it's address.

	input: Graph 'G', Length of G, and Vertex to fi

	output: returns address of Vertex v in Graph G is such exists, returns NULL if not.
*/
PAdjNode _isVertexOf(PGraph G, int VSize, PVertex v)
{
	int i, counter = 0;
	PAdjNode n;
	for (i = 0; i < VSize; i++)
	{
		if (G->vertices[i].v.value == v->value)
		{
			return &G->vertices[i];
		}
	}
	return NULL;
}
