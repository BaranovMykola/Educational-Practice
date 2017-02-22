#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>
#include <iterator>
#include <vector>
#include <string>
#include <numeric>

using namespace std;

template<typename T>
void print(list<T> seq, ostream& stream, const char* message = "", const char* delim = " ")
{
	ostream_iterator<char> charIt(stream, "");
	copy(message, message + strlen(message), charIt);
	ostream_iterator<T> typeIt(stream, delim);
	copy(seq.begin(), seq.end(), typeIt);
	*charIt = '\n';
}

template<typename T, typename U>
class EditIf
{
private:
	T condition;
	U edit;
public:
	EditIf(T _condition, U _edit) :
		condition(_condition),
		edit(_edit)
	{
	}
	void operator()(int& value)
	{
		if (condition())
		{
			edit(value);
		}
	}
};

class EveryN
{
private:
	unsigned int interval;
	unsigned int current;
public:
	EveryN(unsigned int _interval, unsigned int _current) :
		interval(_interval),
		current(_current)
	{
	}
	bool operator()()
	{
		return !(current++ % interval);
	}
};

class MultiplyBy
{
private:
	int factor;
public:
	MultiplyBy(int _factor) :
		factor(_factor)
	{
	}
	void operator()(int& value)
	{
		value *= factor;
	}
};

class Replace
{
private:
	int new_value;
public:
	Replace(int _new_value, bool _replace = true) :
		new_value(_new_value)
	{
	}
	void operator()(int& value)
	{
		value = new_value;
	}
};

struct Sum
{
	long int sum;
	Sum(long int _sum = 0):
		sum(_sum)
	{
	}
	void operator()(int value)
	{
		sum += value;
	}
};

bool squareOf(const double value)
{
	double number = sqrt(value);
	return (number == floor(number));
}

unsigned int sumNumeral(int value)
{
	value = abs(value);
	unsigned int sum = 0;
	while (value != 0)
	{
		sum += value % 10;
		value /= 10;
	}
	return sum;
}

bool compareBySumNumeric(int left, int right)
{
	return (sumNumeral(left) < sumNumeral(right));
}

class PowerSum
{
private:
	unsigned int n;
public:
	PowerSum(): n(1) {};
	int operator()(int left, int right)
	{
		int result = n*pow(left + right, 2);
		n *= -1;
		return result;
	}
};

void main()
{
	list<int> seq;
	ifstream file("Algorithm_data.txt");
	istream_iterator<int> inIt(file), end;
	ostream_iterator<int> outIt(cout, " ");
	seq.assign(inIt, end);
	print(seq, cout, "Primodial list:\t");
	int factor;
	cout << "Multiply every 2 element by: ";
	cin >> factor;
	for_each(seq.begin(), seq.end(), EditIf<EveryN, MultiplyBy>(EveryN(2,1), MultiplyBy(factor)));
	print(seq, cout, "Multiplied even elements:\t");

	int divider;
	cout << "Type divider of position:\t";
	cin >> divider;
	for_each(seq.begin(), seq.end(), EditIf<EveryN, Replace>(EveryN(divider, 1), Replace(*prev(seq.end()))));
	print(seq, cout, "Modifided sequenced:\t");
	int square_of;
	cout << "Enter number to square it: ";
	cin >> square_of;
	square_of = pow(square_of, 2);
	stable_partition(seq.begin(), seq.end(), [=](int val) { return val == square_of; });
	print(seq, cout, "Moved perfect square to the begin of sequence:\t");

	seq.sort();
	seq.unique();
	seq.sort(compareBySumNumeric);
	print(seq, cout, "Sorted by sum of numeric:\t");

	const int quantity = 2;
	vector<int> v1;
	vector<int> v2;
	vector<int>* vector_set[quantity] = { &v1, &v2 };
	string name_file[quantity] = { "Algorithm_vector1_data.txt", "Algorithm_vector2_data.txt" };
	for (int i = 0;i < quantity;++i)
	{
		ifstream file(name_file[i]);
		istream_iterator<int> vectorInIt(file);
		vector_set[i]->assign(vectorInIt, end);
		cout << "vector " << i+1 << ":\t";
		copy(vector_set[i]->begin(), vector_set[i]->end(), outIt);
		cout << endl;
	}
	vector<int> v_result(v1.size());
	transform(v1.begin(), v1.end(), v2.begin(), v_result.begin(), PowerSum());
	cout << "Sum of square sum each pair from v1 & v2:\t" << accumulate(v_result.begin(), v_result.end(), 0) << endl;

	system("pause");
}