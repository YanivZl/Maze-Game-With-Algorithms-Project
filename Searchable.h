#pragma once
#include <vector>
#include <memory>
#include "Node.h"


template<class T>
class Searchable
{
private:
	std::vector<Node<T>> _nodes;
	int _startNode;
	int _goalNode;
public:
	Searchable();
	std::vector<Node<T>>* getNodes();
	int getStartNode() const;
	int getGoalNode() const;
	void setNodes(std::vector<Node<T>> nodes);
	void setStartNode(int start);
	void setGoalNode(int goal);
};

template<class T>
Searchable<T>::Searchable() : _startNode(0), _goalNode(0)
{}

template<class T>
int Searchable<T>::getStartNode() const
{
	return _startNode;
}

template<class T>
int Searchable<T>::getGoalNode() const
{
	return _goalNode;
}

template<class T>
void Searchable<T>::setStartNode(int start)
{
	_startNode = start;
}

template<class T>
void Searchable<T>::setGoalNode(int goal)
{
	_goalNode = goal;
	
}

template<class T>
std::vector<Node<T>>* Searchable<T>::getNodes()
{
	return &_nodes;
}

template<class T>
void Searchable<T>::setNodes(std::vector<Node<T>> nodes)
{
	_nodes = nodes;
}