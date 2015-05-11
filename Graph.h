#ifndef GRAPH_H
#define GRAPH_H

#include <QHash>
#include <QList>
#include <algorithm>
#include <limits>

class Graph
{
public:
	Graph() = default;

	bool AddNode(int ID);
	bool RemoveNode(int ID);
	bool SetConnection(int a, int b, int weight);
	bool RemoveConnection(int a, int b);

	QList<int> CalculatePath(int start, int finish) const;

private:
	QList<int> nodes;
	QHash<int, QHash<int, int>> vertices;

	typedef QHash<int, QHash<int, int>>::const_iterator GraphIterator;
	typedef QHash<int, int>::const_iterator VertexIterator;
};

#endif