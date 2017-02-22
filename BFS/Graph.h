#pragma once
#include <stack>
#include <queue>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;
typedef unsigned int index;

class Graph
{
private:
	unsigned int** matrix;
	size_t vertexCount;
	void reallocateMatrix(unsigned int** const = nullptr);
	void deleteMatrix();
	queue<unsigned int> getAdjacent(unsigned int);
public:
	Graph();
	Graph(const Graph&);
	~Graph();
	unsigned int getDistance(unsigned int, unsigned int);
	friend ostream& operator<<(ostream&, const Graph&);
	friend istream& operator>>(istream&, Graph&);
};

