#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>

using namespace std;

bool _secondElementCompare(pair<int, char> &left, pair<int, char> &right)
{
	return left.second < right.second;
}

void main()
{
	ifstream in("data.txt");
	size_t size;
	in >> size;
	vector<char> arr(size);
	cout << "Primordial vector: ";
	for (int j = 0;j < size;++j)
	{
		in >> arr[j];
	}
	for (char i : arr)
	{
		cout << i << ' ';
	}
	cout << endl << endl;
	vector<pair<int, char>> relation;
	for (int i = 0;i < arr.size();++i)
	{
		relation.emplace_back(i, arr[i]);
	}
	cout << "Realtion:" << endl;
	for (auto i : relation)
	{
		cout << i.first << '\t' << i.second << endl;
	}
	cout << endl << endl;
	sort(relation.begin(), relation.end(), _secondElementCompare);
	cout << "Sorted relation:" << endl;
	for (auto i : relation)
	{
		cout << i.first << '\t' << i.second << endl;
	}
	vector<pair<int, char>>::iterator i = relation.begin();
	while ((i != relation.end()) && i != relation.end())
	{
		bool popFirst = false;
		if (i == relation.begin() && i == prev(relation.end()))
		{	//remove last element
			relation.erase(i);
			break;
		}
		bool popEnd = i != relation.begin() && i == prev(relation.end()) && (*(i - 1)).second != (*i).second;
		bool popMiddle = (i != relation.end()) && i+1 != relation.end() && i != relation.begin() && ((*i).second != (*(i + 1)).second) && ((*i).second != (*(i - 1)).second);
		popFirst = ((i == relation.begin()) && ((*i).second != (*(i + 1)).second));
		if (popFirst ||
			popEnd ||
			popMiddle )
		{
			i = relation.erase(i);
			if (i != relation.begin())
			{
				--i;
			}
		}
		if (!popFirst)
		{
			++i;
		}
	}
	cout << endl << endl;
	cout << "Erased relation:" << endl;
	for (auto i : relation)
	{
		cout << i.first << '\t' << i.second << endl;
	}
	cout << endl << endl;
	sort(relation.begin(), relation.end());
	cout << "Erased sorted relation:" << endl;
	for (auto i : relation)
	{
		cout << i.first << '\t' << i.second << endl;
	}
	arr.erase(arr.begin(), arr.end());
	for (auto i : relation)
	{
		arr.push_back(i.second);
	}
	cout << endl << endl;
	cout << "Result: ";
	for (char i : arr)
	{
		cout << i << ' ';
	}
	cout << endl;
	system("pause");
}