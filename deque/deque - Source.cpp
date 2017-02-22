#include <iostream>
#include <deque>
#include <iterator>
#include <algorithm>
#include <fstream>

using namespace std;

void main()
{
	ifstream deque_data("deque_data.txt");
	istream_iterator<int> in_it(deque_data), end;
	ostream_iterator<int> out(cout, " ");
	deque<int> deq(in_it, end);
	int elem;
	cin >> elem;
	deq.insert(lower_bound(deq.begin(), deq.end(), elem), elem);
	copy(deq.begin(), deq.end(), out);
	system("pause");
}