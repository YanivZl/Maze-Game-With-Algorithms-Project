#pragma once
#include <map>
#include "SearchAlgorithm.h"

template <class T>
class AStar : public SearchAlgorithm<T>
{
public:
    std::vector<Node<T>*> search(Searchable<T>* searchable) { return std::vector<Node<T>*>(); };
    virtual double fromHere(Node<T>* start, Node<T>* goal , const char* name_of_evaluation) = 0;
    std::vector<Node<T>*> search(Searchable<T>* searchable, const char* name_of_evaluation);
};

template<class T>
std::vector<Node<T>*> AStar<T>::search(Searchable<T>* searchable , const char* name_of_evaluation)
{
    this ->_evaluatedNodes = 0;
    // list of nodes that need to be checked
    std::vector<std::pair<Node<T>* , double>> openList;
    //list of nodes that have been checked
    std::vector<std::pair<Node<T>*, double>> closedList;
    std::map<Node<T>*, double> toNode;

    Node<T>* start = &searchable->getNodes() ->at(searchable ->getStartNode());
    Node<T>* goal = &searchable->getNodes()->at(searchable->getGoalNode());

    openList.push_back(std::make_pair(start , 1));
    toNode[start] = 0;

    while (!openList.empty()) 
    {
        // greedy choice
        std::pair<Node<T>*, double> best = openList.front();
        for (std::pair<Node<T>*, double> o : openList)
        {
            if (this->fromHere(o.first, goal , name_of_evaluation) + toNode.at(o.first) < this->fromHere(best.first, goal , name_of_evaluation) + toNode.at(best.first) && o.second != INT_MAX) 
                best = o;
        }
        // Erase the next node to check from the open list.
        for (unsigned int n = 0; n < openList.size(); n++)
            if (openList[n].first == best.first)
                openList.erase(openList.begin() + n);

        this->_evaluatedNodes++;

        // Push the neighbours of the best node to the open list.
        std::vector<std::pair<Node<T>*, double>>* adj = new std::vector<std::pair<Node<T>*, double>>;
        for (unsigned int i = 0; i < best.first->getChildren().size(); i++)
        {
            best.first->getChildren()[i].second->setCostUntil(toNode[best.first] + best.first->getChildren()[i].first);
            adj->push_back(std::make_pair(best.first->getChildren()[i].second, best.first->getChildren()[i].first));
        }
        for (std::pair<Node<T>*, double> a : *adj)
        {
            if (a.first == goal) 
            {
                a.first->setCameFrom(best.first);
                return this->backTrace(a.first, searchable);
            }

            // if in the closed list ignore
            bool isInClosed = false;
            for (std::pair<Node<T>*, double> c : closedList)
            {
                if (c.first == a.first) 
                {
                    isInClosed = true;
                    break;
                }
            }
            if (isInClosed)
                continue;

            // if already in open list, check if the total score
            // when we use the current generated path to get there
            // if it is, update its score and parent
            bool isInOpen = false;
            for (std::pair<Node<T>*, double> o : openList)
                if (o == a) 
                {
                    isInOpen = true;
                    break;
                }
            if (isInOpen) 
            {
                if (this->fromHere(best.first, goal , name_of_evaluation) + toNode[best.first] + a.first->getCostUntil() < this->fromHere(a.first, goal , name_of_evaluation) + toNode[a.first])
                {
                    a.first->setCameFrom(best.first);
                    toNode[a.first] = toNode[best.first] + a.first->getCostUntil();
                    best.first = a.first;
                }
                // if not in the open list add it and compute its score
            }
            else 
            {
                a.first->setCameFrom(best.first);
                toNode[a.first] = toNode[best.first] + toNode[a.first];
                openList.push_back(a);
            }
        }
        closedList.push_back(best);
    }
}
