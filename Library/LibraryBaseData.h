#pragma once
#include <string>
#include <fstream>

using namespace std;

class LibraryBaseData
{
public:
	unsigned int udc;
	string author;
	string name;
	unsigned int date;
	unsigned int quantity;
public:
	LibraryBaseData();
	LibraryBaseData(unsigned int, string, string, unsigned int, unsigned int);
	LibraryBaseData(const LibraryBaseData&);
	~LibraryBaseData();
	LibraryBaseData& operator=(const LibraryBaseData&);
	friend ostream& operator<<(ostream&, const LibraryBaseData&);
	friend istream& operator>>(istream&, LibraryBaseData&);
};

