//If the start location is equal to the ending location, then we've
//solved the maze, so return true.
//Mark the start location as visted.
//For each of the four directions,
//If the location one step in that direction(from the start
//	location) is unvisited,
//	then call pathExists starting from that location(and
//		ending at the same ending location as in the
//		current call).
//	If that returned true,
//	then return true.
//	Return false.

#include <string>
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

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
	maze[sr][sc] = 'D';
	if (sr == er && sc == ec) //BASE CASE
		return true;
	if (maze[sr - 1][sc] == '.') //SIMPLIFYING CASES (reduces open spots)
		if (pathExists(maze, nRows, nCols, sr - 1, sc, er, ec))
			return true;
	if (maze[sr + 1][sc] == '.')
		if (pathExists(maze, nRows, nCols, sr + 1, sc, er, ec))
			return true;
	if (maze[sr][sc - 1] == '.')
		if (pathExists(maze, nRows, nCols, sr, sc - 1, er, ec))
			return true;
	if (maze[sr][sc + 1] == '.')
		if (pathExists(maze, nRows, nCols, sr, sc + 1, er, ec))
			return true;
	return false;
}