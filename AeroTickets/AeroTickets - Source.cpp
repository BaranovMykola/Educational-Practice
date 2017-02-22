#include <iostream>
#include <iterator>
#include <map>
#include <fstream>
#include <ctime>
#include "Ticket.h"
#include <algorithm>

using namespace std;

enum Action{ADD, SHW, SCH, DEL, EDT, CNT, LST, EXT};
const char* Ask{ "Chose action:\n" };
const char* Choose[]{ {"Add"}, {"Show"}, {"Search"}, {"Delete"}, {"Edit"}, {"Count"}, {"List"}, { "Exit" } };

template<ostream& stream = cout>
void message()
{
	stream << Ask;
	unsigned int _number = 0;
	for (auto i : Choose)
	{
		stream << _number++ << ": " << i << endl;
	}
}

void main()
{
	/*
	time_t now = time(0);
	cout << asctime(gmtime(&now)) << endl;
	*/
	ifstream file("dataTickets.txt");
	multimap<Destination, Ticket> base;
	do
	{
		Destination f;
		Ticket s;
		file >> f >> s;
		base.insert(make_pair(f, s));
	}
	while(!file.eof());

	auto current = base.begin();
	do
	{
		auto end_range = base.upper_bound(current->first);
		cout << "To " << current->first << ':' << endl;
		for (;current != end_range;++current)
		{
			cout << '\t' << current->second;
		}
		current = end_range;

	} while (current != base.end());

	int action;
	do
	{
		try
		{
			message();
			cin >> action;
			if (action == Action::ADD)
			{
				cout << "Type {Destination {Flight, Name, Time}}" << endl;
				Destination _to;
				Ticket _add;
				cin >> _to >> _add;
				base.insert(make_pair(_to, _add));
			}
			else if (action == Action::SHW)
			{
				cout << "Type destination: " << endl;
				Destination _key;
				cin >> _key;
				auto range = base.equal_range(_key);
				for (;range.first != range.second;++range.first)
				{
					cout << range.first->second;
				}
			}
			else if (action == Action::SCH)
			{
				cout << "Type 'Fligt' & 'Name':" << endl;
				unsigned short _flight;
				string _name;
				cin >> _flight >> _name;
				auto start = find_if(base.begin(), base.end(), [=](map<Destination, Ticket>::value_type val) { return (val.second.name() == _name) && (val.second.flight() == _flight); });
				if (start == base.end())
				{
					throw exception("Not found");
				}
				do
				{
					cout << "From: " << start->first << '\t' << start->second;
					++start;
				} while (start->second.name() == _name && start->second.flight() == _flight);

			}
			else if (action == Action::DEL)
			{
				cout << "Type 'Fligt' & 'Name':" << endl;
				unsigned short _flight;
				string _name;
				cin >> _flight >> _name;
				auto start_del = find_if(base.begin(), base.end(), [=](map<Destination, Ticket>::value_type val) { return (val.second.name() == _name) && (val.second.flight() == _flight); });
				auto end_del = start_del;
				do
				{
					++end_del;
				} while (end_del->second.name() == _name && end_del->second.flight() == _flight);
				base.erase(start_del, end_del);

				/*current = base.begin();
				do
				{
					auto end_range = base.upper_bound(current->first);
					cout << "To " << current->first << ':' << endl;
					for (;current != end_range;++current)
					{
						cout << '\t' << current->second;
					}
					current = end_range;

				} while (current != base.end());*/
			}
			else if (action == Action::EDT)
			{
				cout << "Type destination: ";
				Destination _to;
				cin >> _to;
				auto range = base.equal_range(_to);
				if (range.first == range.second)
				{
					throw exception("Not found");
				}
				auto current = range.first;
				int i = 0;
				for (;current != range.second;++current)
				{
					cout << i++ << ": " << current->second;
				}
				cout << "Chose item: ";
				cin >> i;
				current = next(range.first, i);
				cout << current->second << endl << "Type new ticket: ";
				Ticket _edit;
				cin >> _edit;
				current->second = _edit;
				current = base.begin();
				do
				{
					auto end_range = base.upper_bound(current->first);
					cout << "To " << current->first << ':' << endl;
					for (;current != end_range;++current)
					{
						cout << '\t' << current->second;
					}
					current = end_range;

				} while (current != base.end());
			}
			else if (action == Action::CNT)
			{
				cout << "Type destination: ";
				Destination _to;
				cin >> _to;
				auto range = base.equal_range(_to);
				cout << distance(range.first, range.second) << " passangers" << endl;
			}
			else if (action == Action::LST)
			{
				current = base.begin();
				do
				{
					auto end_range = base.upper_bound(current->first);
					cout << "To " << current->first << ':' << endl;
					for (;current != end_range;++current)
					{
						cout << '\t' << current->second;
					}
					current = end_range;

				} while (current != base.end());
			}
			else
			{
				throw exception("Unknown action");
			}
		}
		catch (exception error)
		{
			cout << "Error: " << error.what() << endl;
		}
	}
	while(action != Action::EXT);
}