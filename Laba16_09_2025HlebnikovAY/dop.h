#pragma once
#include <iostream>
#include <unordered_map>
#include "Pipe.h"

using namespace std;

#define INPUT_LINE(in,str) getline(in>>ws, str);cerr<<str<<endl;
#define PRINT_PARAM(out, x) out <<#x<< "="<<x<<endl;

template <typename T>
T InputCor(T min, T max)
{
	T x;
	while ((cin >> x).fail() || cin.peek() != '\n' || x<min || x>max) {
		cin.clear();
		cin.ignore();
		cout << "Диапозон(" << min << "-" << max << "):";
	}
	cerr << x << endl;
	return x;
}

class redirect_output_wrapper {
	ostream& stream;
	streambuf* const old_buf;
public:
	redirect_output_wrapper(ostream& src) :old_buf(src.rdbuf()), stream(src) {

	}
	~redirect_output_wrapper() {
		stream.rdbuf(old_buf);
	}
	void redirect(std::ostream& dest) {
		stream.rdbuf(dest.rdbuf());
	}
};

void menu();
void delete_menu();
void sort_menu();
void action();

template <typename T>
void ID_ver(unordered_map<int, T>& objects, int todo) {
	cout << "Введите ID: " << endl;
	int choice = InputCor(1, T::get_MaxID());
	if ((objects.find(choice) != objects.end())) {
		switch (todo) {
		case 0:
			objects[choice].edit();
			break;
		case 1:
			objects.erase(choice);
			break;
		}
	}
	else {
		cout << "ID не найден" << endl;
	}
}