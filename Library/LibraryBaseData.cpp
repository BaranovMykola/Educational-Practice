#include "LibraryBaseData.h"



LibraryBaseData::LibraryBaseData():
	udc(0),
	author(),
	date(0),
	quantity(0)
{
}

LibraryBaseData::LibraryBaseData(unsigned int _udc, string _author, string _name, unsigned int _date, unsigned int _quantity):
	udc(_udc),
	author(_author),
	name(_name),
	date(_date),
	quantity(_quantity)
{
}

LibraryBaseData::LibraryBaseData(const LibraryBaseData& _Right) :
	udc(_Right.udc),
	author(_Right.author),
	name(_Right.name),
	date(_Right.date),
	quantity(_Right.quantity)
{
}


LibraryBaseData::~LibraryBaseData()
{
}

LibraryBaseData & LibraryBaseData::operator=(const LibraryBaseData& _right)
{
	udc = _right.udc;
	author = _right.author;
	name = _right.name;
	date = _right.date;
	quantity = _right.quantity;
	return *this;

}

ostream & operator<<(ostream& stream, const LibraryBaseData& output)
{
	return stream << "UDC: " << output.udc << "\tAuthor: " << output.author << "\tName: " << output.name << "\t" << output.date << "\tQuantity: " << output.quantity;
}

istream & operator>>(istream& stream, LibraryBaseData& input)
{
	return stream >> input.udc >> input.author >> input.name >> input.date >> input.quantity;
}
