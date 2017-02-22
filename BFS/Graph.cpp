#include "Graph.h"



void Graph::reallocateMatrix(unsigned int** _Right)
{	//creates new matrix
	deleteMatrix();
	matrix = new unsigned int*[vertexCount];
	for (unsigned int i = 0;i < vertexCount;++i)
	{
		matrix[i] = new unsigned int[vertexCount];
		if (_Right != nullptr)
		{
			for (unsigned int j = 0;j < vertexCount;++j)
			{
				matrix[i][j] = _Right[i][j];
			}
		}
	}

}

void Graph::deleteMatrix()
{	//destroys matrix and frees memory in heap
	if (matrix != nullptr)
	{
		for (unsigned int i = 0;i < vertexCount; ++i)
		{
			delete[] matrix[i];
		}
		delete[] matrix;
	}
}

queue<unsigned int> Graph::getAdjacent(unsigned int vertex)
{	//gets all adjascent vertex
	queue<unsigned int> ret;
	for (unsigned int i = 0;i < vertexCount;++i)
	{
		if (matrix[vertex][i] != 0)
		{
			ret.push(i);
		}
	}
	return ret;
}

Graph::Graph() :
	matrix(nullptr),
	vertexCount(0)
{	//empty constructor
}

Graph::Graph(const Graph& _Right):
	matrix(nullptr),
	vertexCount(_Right.vertexCount)
{	//copy constructor
	reallocateMatrix(_Right.matrix);
}


Graph::~Graph()
{
	deleteMatrix();
}

unsigned int Graph::getDistance(unsigned int from, unsigned int to)
{	//BFS method for get distance
	unsigned int* const distanceTo = new unsigned int[vertexCount];
	for (int i = 0;i < vertexCount;++i)
	{	// initializing infinity distance to each vertex
		distanceTo[i] = UINT_MAX;
	}

	unsigned int currentVertex = from;
	queue<index> waitingVertex;
	queue<index> adjacent;
	
	distanceTo[currentVertex] = 0;

	waitingVertex.push(from);

	while (!waitingVertex.empty())
	{
		currentVertex = waitingVertex.front();
		adjacent = getAdjacent(currentVertex);
		while (!adjacent.empty())
		{
			if (distanceTo[adjacent.front()] > distanceTo[currentVertex] + matrix[currentVertex][adjacent.front()])
			{
				distanceTo[adjacent.front()] = distanceTo[currentVertex] + matrix[currentVertex][adjacent.front()];
				waitingVertex.push(adjacent.front());
			}
			adjacent.pop();
		}
		waitingVertex.pop();
	}
	unsigned int ret = distanceTo[to];
	delete[] distanceTo;
	return ret;
}

ostream & operator<<(ostream& stream, const Graph& output)
{
	stream << "\tVertex count: " << output.vertexCount << endl;
	for (unsigned int i = 0;i < output.vertexCount;++i)
	{
		for (unsigned int j = 0;j < output.vertexCount;++j)
		{
			stream << output.matrix[i][j] << ' ';
		}
		stream << endl;
	}
	return stream;
}

istream & operator>>(istream& stream, Graph& input)
{
	string firstLine;
	getline(stream, firstLine);
	input.vertexCount = count(firstLine.begin(), firstLine.end(), ' ')+1;
	input.reallocateMatrix();
	stream.seekg(ios::beg);
	for (unsigned int i = 0;i < input.vertexCount;++i)
	{
		for (unsigned int j = 0;j < input.vertexCount;++j)
		{
			stream >> input.matrix[i][j];
		}
	}
	return stream;
}
