#include "Astar.h"
#include <string>

template<class T>
class AStar2D : public AStar<T>
{
private:
	double fromHere(Node<T>* start, Node<T>* goal) { return NULL; };
public:
	double fromHere(Node<T>* start, Node<T>* goal, const char* name_of_evaluation);
};

template<class T>
double AStar2D<T>::fromHere(Node<T>* start, Node<T>* goal , const char* name_of_evaluation)
{
	std::vector<int> first = start->getArguments();
	std::vector<int> second = goal->getArguments();
	int x1 = first[0];
	int y1 = first[1];
	int x2 = second[0];
	int y2 = second[1];
	if(name_of_evaluation == "manhattan")
		return ((double)abs(x2 - x1) + (double)abs(y2 - y1));
	if (name_of_evaluation == "air")
		return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	return 0;
}
