#pragma once
#include "SearchAlgorithm.h"

template <class T>
class BFS : public SearchAlgorithm<T> {
public:
    virtual std::vector<Node<T>*> search(Searchable<T>* searchable);
};

template<class T>
struct customComparation
{
    bool operator()(const std::pair<Node<T>*, double>& left,const std::pair<Node<T>*, double>& right)
    {

        return left.second > right.second ? true : false;
    }
};

template<typename T>
std::vector<Node<T>*> BFS<T>::search(Searchable<T>* searchable)
{
    // if initial case is goal node
    if (searchable->getStartNode() == searchable->getGoalNode()) 
        return this->backTrace(&searchable ->getNodes() ->at(searchable->getStartNode()), searchable);

    std::vector<Node<T>*> blacks;
    std::vector<Node<T>*> grays;
    std::priority_queue<std::pair<Node<T>* , double> , std::vector<std::pair<Node<T>* , double >> , customComparation<T> > p_queue;
    
    p_queue.push(std::make_pair(&(searchable ->getNodes() ->at(searchable->getStartNode())) , 1));

    while (!p_queue.empty()) 
    {
        std::pair<Node<T>* , double> node = p_queue.top();
        p_queue.pop();
        this->_evaluatedNodes++;
        
        // if node is goal node
        if (&(searchable->getNodes() ->at(searchable->getGoalNode())) == node.first)
            return this ->backTrace(node.first, searchable);

        std::vector<std::pair< Node<T>* ,  double>> adj;
        for(unsigned int i = 0 ; i < node.first -> getChildren().size(); i++)
            adj.push_back(std::make_pair(node.first->getChildren()[i].second, node.first->getChildren()[i].first));
        for (std::pair<Node<T>* , double> a: adj)
        {
            bool isWhite = true;
            for (Node<T>* g : grays) 
                if (a.first == g)
                    isWhite = false;
            if (isWhite) 
            {
                grays.push_back(a.first);
                a.first ->setCameFrom(node.first);
                p_queue.push(a);
            }
        }
        blacks.push_back(node.first);
    }
    return std::vector<Node<T>*>();
}
