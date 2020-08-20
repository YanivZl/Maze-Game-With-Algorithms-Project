#pragma once
#include<vector>

template <class T>
class Node {
    T _node;
    double _costUntil;
    Node<T>* _cameFrom;
    std::vector<std::pair<double , Node<T>*>> _children; 

public:
    Node(T node);

    bool operator==(const Node<T>& s);

    bool operator<(const Node<T>& left);

    double getCostUntil() const;

    std::vector<std::pair<double, Node<T>*>> getChildren() const;

    void setCostUntil(double cost);

    void appendChild(Node<T>* node , double cost);

    T getNode() const;

    Node<T>* getCameFrom() const;

    void setCameFrom(Node<T>* cameFrom);

    std::vector<int> getArguments() const;
};

template<class T>
Node<T>::Node(T node) : _node(node) , _costUntil(0) , _cameFrom(nullptr) {};

template<class T>
bool Node<T>::operator==(const Node<T>& s)
{
    return _node == s._node ? true : false;
}

template<class T>
bool Node<T>::operator<(const Node<T>& n)
{
    return _costUntil < n._costUntil ? true : false;
}


template<class T>
double Node<T>::getCostUntil() const
{
    return _costUntil;
}

template<class T>
std::vector<std::pair<double, Node<T>*>> Node<T>::getChildren() const
{
    return _children;
}

template<class T>
void Node<T>::setCostUntil(const double cost)
{
    _costUntil = cost;
}

template<class T>
void Node<T>::appendChild(Node<T>* node , double cost)
{
    _children.push_back(std::make_pair(cost , node));
}

template<class T>
T Node<T>::getNode() const
{
    return _node;
}

template<class T>
Node<T>* Node<T>::getCameFrom() const
{
    return _cameFrom;
}

template<class T>
void Node<T>::setCameFrom(Node<T>* cameFrom)
{
    _cameFrom = cameFrom;
}

template<class T>
std::vector<int> Node<T>::getArguments() const
{
    return _node.getArguments();
}
