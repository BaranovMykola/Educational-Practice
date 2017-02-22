#include <iostream>
#include <set>
#include <algorithm>
#include <string>
#include <fstream>
#include <iterator>

enum Students{PROG, MATH, ENGL};
const int Quantity = 3;
const char* FileName[Quantity] = { "Programming.txt", "Math.txt", "English.txt" };

void main()
{
	std::set<std::string> data[3];
	std::ostream_iterator<std::string> out(std::cout, " ");
	std::ifstream input;
	std::istream_iterator<std::string> end;
	for (int i = 0;i < Quantity;++i)
	{
		input.open(FileName[i]);
					if (!input.is_open()) throw;
		std::istream_iterator<std::string> beg(input);
		std::copy(beg, end, std::inserter(data[i], data[i].begin()));
		std::cout << FileName[i] << '\t';
		std::cout.width(40);
		std::copy(data[i].begin(), data[i].end(), out);
		std::cout << std::endl;
		input.close();
	}

	std::set<std::string> ProgAndEng;
	std::set_intersection(data[Students::PROG].begin(), data[Students::PROG].end(), data[Students::ENGL].begin(), data[Students::ENGL].end(), std::inserter(ProgAndEng, ProgAndEng.begin()));
	std::cout << "Programs and English:\t";
	std::copy(ProgAndEng.begin(), ProgAndEng.end(), out);
	std::cout << std::endl;

	std::set<std::string> ProgAndMath;
	std::set<std::string> ProgAndMathButEng;
	std::set_intersection(data[Students::PROG].begin(), data[Students::PROG].end(), data[Students::MATH].begin(), data[Students::MATH].end(), std::inserter(ProgAndMath, ProgAndMath.begin()));
	std::set_difference(ProgAndMath.begin(), ProgAndMath.end(), data[Students::ENGL].begin(), data[Students::ENGL].end(), std::inserter(ProgAndMathButEng, ProgAndMathButEng.end()));
	std::cout << "Programs and Math but English:\t";
	std::copy(ProgAndMathButEng.begin(), ProgAndMathButEng.end(), out);
	std::cout << std::endl;

	std::set<std::string> MathOrProg;
	std::set<std::string> Math;
	std::set_difference(data[Students::MATH].begin(), data[Students::MATH].end(), data[Students::ENGL].begin(), data[Students::ENGL].end(), std::inserter(MathOrProg, MathOrProg.begin()));
	std::set_difference(MathOrProg.begin(), MathOrProg.end(), data[Students::PROG].begin(), data[Students::PROG].end(), std::inserter(Math, Math.begin()));
	std::cout << "Only Math:\t";
	std::copy(Math.begin(), Math.end(), out);
	std::cout << std::endl;
	system("pause");
}