#include "cs.h"
#include "dop.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int ks::MaxID = 1;

int ks::get_id() {
	return id;
}
int ks::get_MaxID() {
	return MaxID;
}

void ks::getks() {
	cin.ignore(1000, '\n');
	cout << "Введите название компрессорной станции: ";
	getline(cin, ksname);
	cerr << ksname << endl;
	cout << "Введите количество цехов: ";
	count_cex= InputCor(0,1000);
	cout << "Введите количество работающих цехов: ";
	count_cex_work=InputCor(0,count_cex);
	cout << "Введите класс станции (от 1 до 5): ";
	klass = InputCor(1, 5);
}

void ks::edit() {
	if (ksname == "") {
		cout << "У вас нет Компрессорной станции" << endl;
	}
	else {
		cout << "Введите количество работающих цехов" << endl;
		count_cex_work = InputCor(0, count_cex);
	}
}

void ks::showks(const unordered_map<int, ks>& css) {
	for (const auto& pair : css) {
		
		cout << "----Ваша компрессорная станция----" << endl;
		cout << "ID" << pair.first << endl;
		cout << "Название станции: " << ksname<< endl;
		cout << "Количество цехов: " << count_cex << endl;
		cout << "Количесвто работающих цехов: " << count_cex_work << endl;
		cout << "Класс КС: " << klass << endl;
	}
}void ks::saveks(ofstream& fout, unordered_map<int, ks>& css) {
	string Marker = "КС";
	for (const auto& pair:css){
		if (ksname == "") {
		fout << Marker << endl;
		}
		else {
			fout << Marker << endl;
			fout << pair.first + 1 << endl;
			fout << css[pair.first].ksname << endl;
			fout << css[pair.first].count_cex << endl;
			fout << css[pair.first].count_cex_work << endl;
			fout << css[pair.first].klass << endl;
	}
	}
}

void ks::loudks(ifstream& fin, unordered_map<int, ks>& css) {
	css.clear();
	string Marker;
	int max_id = -1;
	while (true) {
		getline(fin, Marker);
		if (fin.eof())break;
		if (Marker != "KS")continue;
		int save_id;
		if (!(fin >> save_id))break;
		ks c;
		if (!(fin >> c.ksname >> c.count_cex >> c.count_cex_work >> c.klass))break;
		c.id = save_id - 1;
		css[c.id] = c;
		if (c.id > max_id) {
			max_id = c.id;
		}
		if (max_id != -1) {
			ks::MaxID = max_id + 1;
		}
	}
}

void ks::search_ksname(const unordered_map<int, ks>& css, unordered_set<int>& keys, const string& name) {
	for (const auto& pair : css) {
		if (pair.second.ksname.find(name) != string::npos) {
			keys.insert(id);
		}
	}
}
void ks::delete_searched(unordered_map<int, ks>& css, const unordered_set<int>& keys) {
	for (const auto& key : keys) {
		css.erase(key);
	}
}
void ks::edit_searched(unordered_map<int, ks>& css, const unordered_set<int>& keys) {
	for (auto& pair : css) {
		if (keys.find(id) != keys.end()) {
			cin.clear();
			cin.ignore(1000, '\n');
			cin >> css[pair.first].count_cex;
		}
	}
}
void ks::show_searched(unordered_map<int, ks>& css, const unordered_set<int>& keys) {
	for (const int& key : keys) {
		cout << "--------KS-------" << endl;
		cout << "ID: " << key << endl;
		cout << "Название: " << css[key].ksname << endl;
		cout << "Количество цехов: " << css[key].count_cex << endl;
		cout << "Количество работающих цехов: " << css[key].count_cex_work << endl;
		cout << "Класс: " << css[key].klass << endl;
	}
}