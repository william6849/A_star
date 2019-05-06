#ifndef ASTAR_H
#define ASTAR_H

#include "lib.h"

template <class Q>
void clearQueue(Q & q);

int ManhattanDistance(const int x  , const int y);

typedef struct _pare {
	int cost;
	int parentx;
	int parenty;
}pare;

class node {
public:
	node();
	node(const int x, const int y);
	node(node const & n);
	~node();
	node & operator =(const node &a);

	void finder(int (*openmatrix)[WIDTH]);
	void set_G(const int g, const int x, const int y, const int px, const int py);
	int getX() const;
	int getY() const;
	int getG() const;
	int getT() const;


private:
	struct impl;
	impl *pimpl;
};


void astar(int (*grid)[WIDTH] , int(*open)[WIDTH], const int start_x, const int start_y , const int end_x, const int end_y);

#endif 
