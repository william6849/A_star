#include "astar.h"

int startx;
int starty;
int endx;
int endy;
pare cost[HEIGHT][WIDTH] = { 0 };

struct comp
{
	bool operator() (const node &a, const node &b)
	{
		return a.getT() > b.getT();
	}
};

std::priority_queue <node, std::vector<node>, comp> Pqueue;

template<class Q>
void clearQueue(Q & q)
{
	q = Q();
}


int ManhattanDistance(const int x, const int y)
{
	return abs(x - endx) + abs(y - endy);
}


struct node::impl {
	impl()
		:g(0), h(0), t(0), posX(-1), posY(-1)
	{}
	impl(const int x, const int y)
		:g(0), h(0), t(0), posX(x), posY(y)
	{}

	int g;
	int h;
	int t;
	int posX;
	int posY;
};

node::node()
	:pimpl(new impl())
{
}

node::node(const int x, const int y)
	: pimpl(new impl(x, y))
{
}

node::node(node const & n)
	:pimpl(new impl(*n.pimpl))
{
}

node::~node()
{
	delete pimpl;
}


node & node::operator=(const node & a)
{
	if (&a == this)return *this;
	delete this->pimpl;
	pimpl = new impl(*a.pimpl);
	return *this;
}



void astar(int(*grid)[WIDTH], int(*open)[WIDTH], const int start_x, const int start_y, const int end_x, const int end_y)
{
	endx = end_x; endy = end_y; startx = start_x; starty = start_y;

	while (!Pqueue.empty())Pqueue.pop();
	memset(cost, 0 , sizeof(int)*3 * HEIGHT * WIDTH);
	cost[start_y][start_x].parentx = start_x;
	cost[start_y][start_x].parenty = start_y;

	node start(start_x, start_y);
	start.finder(open);
	node temp;

	while (Pqueue.top().getX() != end_x || Pqueue.top().getY() != end_y) {
		if (!Pqueue.empty()) {
			temp = Pqueue.top();
			Pqueue.pop();
			grid[temp.getY()][temp.getX()] = 4;
			cost[temp.getY()][temp.getX()].cost = temp.getT();

			temp.finder(open);
		}
		else break;
	}


	int i = endy; int j = endx;

	//for (int k = 0; i!=starty || j!=startx;){
	for (int k = 0; k<200;k++){
			std::cout << "x:" << j << " y:" << i << std::endl;
			int px = cost[i][j].parentx; int py = cost[i][j].parenty;
			grid[py][px] = 5;
			j = px;
			i = py;
			
	}

	system("CLS");
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j)
			std::cout << cost[i][j].cost << " ";
		std::cout << "\n";
	}std::cout << "\n-----------------------------------";std::cout << "\n";

}


void node::finder(int(*openmatrix)[WIDTH]){
		openmatrix[pimpl->posY][pimpl->posX] = 1;
		cost[this->getY()][this->getX()].cost = this->getT();

		bool up = false, down = false, left = false, right = false;
		int posX = this->getX();
		int posY = this->getY();

		if (posX > 0) left = true;
		if (posX < WIDTH - 1) right = true;
		if (posY > 0) up = true;
		if (posY < HEIGHT - 1) down = true;

		node temp;

		if (up && !openmatrix[(pimpl->posY)-1][pimpl->posX]){
			temp.set_G((pimpl->g) + 1, posX, posY-1  ,posX,posY);
			Pqueue.push(temp);
		}
		if (down && !openmatrix[(pimpl->posY)+1][pimpl->posX]) {
			temp.set_G((pimpl->g) + 1, posX, posY+1, posX, posY);
			Pqueue.push(temp);
		}
		if (left && !openmatrix[pimpl->posY][(pimpl->posX)-1]) {
			temp.set_G((pimpl->g) + 1, posX-1, posY, posX, posY);
			Pqueue.push(temp);
		}
		if (right && !openmatrix[pimpl->posY][(pimpl->posX)+1]) {
			temp.set_G((pimpl->g) + 1, posX+1, posY, posX, posY);
			Pqueue.push(temp);
		}
		if (up&&left && !openmatrix[(pimpl->posY) - 1][pimpl->posX-1]) {
			temp.set_G((pimpl->g) + 1, posX-1, posY - 1, posX, posY);
			Pqueue.push(temp);
		}
		if (up&&right && !openmatrix[(pimpl->posY)-1][pimpl->posX+1]) {
			temp.set_G((pimpl->g) + 1, posX+1, posY - 1, posX, posY);
			Pqueue.push(temp);
		}
		if (down&&right && !openmatrix[pimpl->posY+1][(pimpl->posX) + 1]) {
			temp.set_G((pimpl->g) + 1, posX + 1, posY+1, posX, posY);
			Pqueue.push(temp);
		}
		if (left&&down && !openmatrix[pimpl->posY+1][(pimpl->posX) - 1]) {
			temp.set_G((pimpl->g) + 1, posX - 1, posY+1, posX, posY);
			Pqueue.push(temp);
		}
}



void node::set_G(const int g , const int x, const int y, const int px, const int py){
	cost[y][x].parentx = px;
	cost[y][x].parenty = py;

	pimpl->g = g;
	pimpl->h = ManhattanDistance(x,y);
	pimpl->t = pimpl->g + pimpl->h;
	pimpl->posX = x;
	pimpl->posY = y;
}

int node::getX() const
{
	return pimpl->posX;
}

int node::getY() const
{
	return pimpl->posY;
}

int node::getG() const
{
	return pimpl->g;
}

int node::getT() const
{
	return pimpl->t;
}


