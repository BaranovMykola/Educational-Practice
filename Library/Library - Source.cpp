#include <iostream>
#include "LibraryBaseData.h"
#include <algorithm>
#include <iterator>
#include <forward_list>
#include <iomanip>
#include <vector>

using namespace std;

enum Aaction{ADD, DEL, VIEW, EXIT};
enum SortBy{YEAR, AUTHOR};

void main()
{
	ifstream file("BaseData.txt");
/*	while (!file.eof())
	{
		LibraryBaseData in;
		file >> in;
		cout << in << endl;
	}*/
	istream_iterator<LibraryBaseData> data(file), end;
	ostream_iterator<LibraryBaseData> out(cout, "\n");
	forward_list<LibraryBaseData> lst(data, end);
	int action;
	do
	{
		try
		{
			cout << "Chose action: " << endl << "0: Add new book" << endl << "1: Delete book" << endl << "2: View book" << endl << "3: Exit" << endl;
			cin >> action;
			if (action == ADD)
			{
				cout << "Create book: {UDC, author, name, year, quantity" << endl;
				LibraryBaseData new_book;
				cin >> new_book;
				if (new_book.quantity == 0)
				{
					throw exception("Do you realy want me to add 0 books? I am rather astonished");
				}
				lst.push_front(new_book);
			}
			else if (action == DEL)
			{
				int index;
				unsigned int quantity;
				cout << "Type UDC: ";
				cin >> index;
				cout << "Type quantity: ";
				cin >> quantity;
				
				lst.remove_if([=](LibraryBaseData& val) { 
					bool del = false;
					if (val.udc == index)
					{
						if (val.quantity < quantity)
						{
							throw exception("There are less books than you are going to delete. It might have been stolen");
						}
						if (val.quantity <= quantity)
						{
							del = true;
						}
						{
							val.quantity -= quantity;
						}
					}
					return del; });
			}
			else if (action == VIEW)
			{
				unsigned int sort_type;
				cout << "Sorted by:" << endl << YEAR << ": Year" << endl << AUTHOR << ": Author" << endl;
				cin >> sort_type;
				if (sort_type == YEAR)
				{
					lst.sort([](LibraryBaseData& left, LibraryBaseData& right) { return left.date < right.date; });
				}
				else if (sort_type == AUTHOR)
				{
					lst.sort([](LibraryBaseData& left, LibraryBaseData& right) { return left.author < right.author; });
				}
				else
				{
					throw exception("Choose type of sorting. Be a perfectionist");
				}
				copy(lst.begin(), lst.end(), out);
			}
			else if (action == EXIT)
			{
				break;
			}
			else
			{
				throw exception("Unknown action");
			}
		}
		catch (exception error)
		{
			cout << error.what() << endl;
		}
		
	}
	while(action != EXIT);
	system("pause");
}