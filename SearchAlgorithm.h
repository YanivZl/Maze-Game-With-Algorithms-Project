#pragma once

#include <iostream>
#include <queue>
#include "Searchable.h"
#include "Node.h"


template <class T>
class SearchAlgorithm
{
protected:
    int _evaluatedNodes;
    std::vector<Node<T>> _laststeps;
public:
    SearchAlgorithm();
    virtual std::vector<Node<T>*> search(Searchable<T>* searchable) = 0;
    int getNumberOfNodesEvaluated();

protected:
    std::vector<Node<T>*> backTrace(Node<T>* node, Searchable<T>* searchable);
};

template <class T>
SearchAlgorithm<T>::SearchAlgorithm()
{
    _evaluatedNodes = 0;
}

template <class T>
int SearchAlgorithm<T>::getNumberOfNodesEvaluated() 
{
    return _evaluatedNodes;
}

template<class T>
std::vector<Node<T>*> SearchAlgorithm<T>::backTrace(Node<T>* node, Searchable<T>* searchable)
{
    std::vector<Node<T>*> trace;
    while (node != &searchable->getNodes() ->at(searchable->getStartNode())) 
    {
        if (node == nullptr) 
        {
            std::cout << "no path" << std::endl;
            return trace;
        }
        trace.push_back(node);
        node = node->getCameFrom();
    }
    trace.push_back(&searchable->getNodes()->at(searchable->getStartNode()));
    return trace;
}