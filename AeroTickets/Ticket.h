#pragma once
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

typedef string Destination;

class Ticket
{
public:
	Ticket() = default;
	Ticket(unsigned short, string, time_t);
	~Ticket() = default;
	friend ostream& operator<<(ostream&, const Ticket&);
	friend istream& operator>>(istream&, Ticket&);
	unsigned short flight()const;
	string name()const;
	time_t time()const;
private:
	unsigned short mId;
	string mName;
	time_t mTime;
};

