#include <stack>
#include <iostream>
using namespace std;

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);

int main()
{
	string maze[10] = {
				"XXXXXXXXXX",
				"X....X...X",
				"X.XX.XX..X",
				"XXX....X.X",
				"X.XXX.XXXX",
				"X.X...X..X",
				"X...X.X..X",
				"XXXXX.X.XX",
				"X........X",
				"XXXXXXXXXX"
	};

	if (pathExists(maze, 10, 10, 3, 5, 8, 8))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;
}

class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
	Coord start(sr, sc);
	stack<Coord> coordStack;
	coordStack.push(start);
	maze[sr][sc] = 'D';

	while (!coordStack.empty())
	{
		Coord cur = coordStack.top();
		coordStack.pop();
		if (cur.r() == er && cur.c() == ec)
			return true;
		if (cur.r() != nRows - 1 && maze[cur.r() + 1][cur.c()] != 'D' && maze[cur.r() + 1][cur.c()] != 'X')
		{
			coordStack.push(Coord(cur.r() + 1, cur.c()));
			maze[cur.r() + 1][cur.c()] = 'D';
		}
		if (cur.c() != 0 && maze[cur.r()][cur.c() - 1] != 'D' && maze[cur.r()][cur.c() - 1] != 'X')
		{
			coordStack.push(Coord(cur.r(), cur.c() - 1));
			maze[cur.r()][cur.c() - 1] = 'D';
		}
		if (cur.r() != 0 && maze[cur.r() - 1][cur.c()] != 'D' && maze[cur.r() - 1][cur.c()] != 'X')
		{
			coordStack.push(Coord(cur.r() - 1, cur.c()));
			maze[cur.r() - 1][cur.c()] = 'D';
		}
		if (cur.c() != nCols - 1 && maze[cur.r()][cur.c() + 1] != 'D' && maze[cur.r()][cur.c() + 1] != 'X')
		{
			coordStack.push(Coord(cur.r(), cur.c() + 1));
			maze[cur.r()][cur.c() + 1] = 'D';
		}
	}
	return false;
}
