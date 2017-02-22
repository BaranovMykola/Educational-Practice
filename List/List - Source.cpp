#include <list>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>

using namespace std;

template<typename T>
ostream& operator<<(ostream& stream, const list<T>& Val)
{
	for (auto &i : Val)
	{
		stream << i << ' ';
	}
	return stream;
}

template<typename T>
bool compare(const T& right, const T& left)
{
	return !(right <= left);
}

template<typename T>
bool notEqual(const T& left, const T& right)
{
	return left != right;
}

void main()
{
	ifstream in("data.txt");
	list<char> elementaryList;
	char ch;
	in >> ch;
	while (!in.eof())
	{
		elementaryList.push_back(ch);
		in >> ch;
	}
	in.close();

	in.open("data2.txt");
	list<char> L2;
	in >> ch;
	while (!in.eof())
	{
		L2.push_back(ch);
		in >> ch;
	}

	cout << "Elementary list:\t" << elementaryList << endl;

	elementaryList.sort(compare<char>);

	cout << "Sorted list:\t" << elementaryList << endl << "Type E: ";
	cin >> ch;
	list<char>::iterator i = elementaryList.begin();
	//bool insert = false;
	while(true)
	{
		if (i == elementaryList.end() || ch > *i)
		{
			elementaryList.insert(i, ch);
			break;
		}
		++i;
	}
	cout << "After input:\t" << elementaryList << endl;

	elementaryList.unique();

	cout << "Only first duplicates:\t" << elementaryList << endl << endl;

	cout << "L1:\t" << elementaryList << endl << "L2:\t" << L2 << endl;

	list<char> L;
	list<char> arr[2] = { elementaryList, L2 };
	for (int j = 0;j < 2;++j)
	{
		for (auto &i : arr[j])
		{
			if (find(L.begin(), L.end(), i) == L.end())
			{
				L.push_back(i);
			}
		}
	}
	cout << "Merged list:\t" << L << endl;
	system("pause");
}