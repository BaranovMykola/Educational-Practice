#include "Ticket.h"

Ticket::Ticket(unsigned short id, string name, time_t time):
	mId(id),
	mName(name),
	mTime(time)
{
}

unsigned short Ticket::flight() const
{
	return mId;
}

string Ticket::name() const
{
	return mName;
}

time_t Ticket::time() const
{
	return mTime;
}

ostream & operator<<(ostream& stream, const Ticket& out)
{
	return stream << "Flight: " << out.mId << "\tName: " << out.mName << "\t\t" << asctime(gmtime(&out.mTime));
}

istream & operator>>(istream& stream, Ticket& in)
{
	return stream >> in.mId >> in.mName >> in.mTime;
}
