#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <deque>
#include <string>
#include "Graph.h"
#include <iterator>

using namespace std;

void main()
{

	_CrtMemState state1, state2, state3;
	_CrtMemCheckpoint(&state1);
	{
		ifstream in("graph.txt");
		Graph test;
		in >> test;
		cout << test << endl;
		for (int i = 0;i <= 7;++i)
		{
			for (int j = 0;j <= 7;++j)
			{
				cout << "From " << i << " to " << j << '\t' << test.getDistance(i, j) << endl;
			}
		}
	}
	_CrtMemCheckpoint(&state2);
	if (_CrtMemDifference(&state3, &state1, &state2))
	{
		cout << "Memory error" << endl;
	}
	system("pause");
}