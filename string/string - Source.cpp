#include <iostream>
#include <iterator>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

void main()
{
	
	ifstream file("stringData.txt");
	istream_iterator<char> in(file), end;
	ostream_iterator<char> out(cout, "");
	string data(in, end);
	cout << "Premodial string: " << data << endl;
	auto end_line = find(data.begin(), data.end(), '.');
	auto current = data.begin();
	auto next_pos = current;
	cout << "Some magic..." << endl;
	cout << "Result: ";
	while (current != data.end())
	{
		next_pos = find(current, end_line, ',');
		if (any_of(next(current), next_pos, [=](char _ch) { return _ch == *current; }))
		{
			copy(current, next_pos, out);
			cout << " ";
		}
		current = next(next_pos);
	}
	cout << endl;
	system("pause");
}