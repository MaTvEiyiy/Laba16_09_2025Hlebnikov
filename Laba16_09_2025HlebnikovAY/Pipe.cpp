#include <iostream>
#include <string>
#include <fstream>
#include "Pipe.h"
#include "dop.h"

using namespace std;

int Pipe::MaxID = 1;

int Pipe::get_id() {
	return id;
}
int Pipe::get_MaxID() {
	return MaxID;
}

void Pipe::getPipe() {
	cout << "Введите название трубы: ";
	cin.ignore(1000, '\n');
	getline(cin,namePipe);
	cerr << "PIPE_NAME:" << namePipe << endl;
	cout << "Введите длину: ";
	lenght = InputCor(0, 10000);
	cerr << "PIPE_LENGTH:" << lenght << endl;
	cout << "Введите диаметр: ";
	diametr = InputCor(0, 1000);
	cerr << "PIPE_DIAMETER:" << diametr << endl;
	cout << "Труба в ремонте? (1-да, 0-нет): ";
	repair = InputCor(0, 1);
	cerr << "PIPE_REPAIR:" << repair << endl;
	id = MaxID;
	MaxID++;
	cerr << "PIPE_ID:" << id << endl;
}

void Pipe::edit() {
	if (namePipe == "") {
		cout << "У вас еще нет трубы!" << endl;
	}
	else {
		cout << "Введите состояние трубы (1-в ремонте, 0-работает): " << endl;
		repair = InputCor(0, 1);
	}
}

void Pipe::show_pipe(const unordered_map<int, Pipe>& pipe_group) {
	for(const auto& pair : pipe_group)
	{
		cout << "------Ваша труба!-------" << endl;
		cout << "ID: " << pair.first << endl;
		cout << "Название: " << pair.second.namePipe << endl;
		cout << "Длина трубы: " << pair.second.lenght << endl;
		cout << "Диаметр трубы: " << pair.second.diametr << endl;
		cout << "Состояние трубы (1-в ремонте, 0-не в ремонте):" << pair.second.repair << endl;
		cout << "---------------" << endl;
	}

}

void Pipe::savePipe(ofstream& fout, unordered_map<int, Pipe>& pipe_group) {
	string Marker = "PIPELINE";
	for (const auto& pair : pipe_group) {
		if (namePipe == "") {
			fout << Marker << endl;
		}
		else {
			fout << Marker << endl;
			fout << pair.first + 1 << endl;
			fout << pipe_group[pair.first].namePipe << endl;
			fout << pipe_group[pair.first].lenght << endl;
			fout << pipe_group[pair.first].diametr << endl;
			fout << pipe_group[pair.first].repair << endl;
		}
	}
}
void Pipe::loudPipe(ifstream& fin, unordered_map<int, Pipe>& pipe_group) {
	pipe_group.clear();
	string Marker;
	int max_id = -1;
	while (true) {
		getline(fin, Marker);
		if (fin.eof()) break;
		if (Marker != "PIPELINE")continue;
		int saved_id;
		if (!(fin >> saved_id))break;
		Pipe p;
		if (!(fin >> p.namePipe >> p.lenght >> p.diametr >> p.repair))break;
		p.id = saved_id - 1;
		pipe_group[p.id] = p;
		if (p.id > max_id) {
			max_id = p.id;
		}
		if (max_id != -1) {
			Pipe::MaxID = max_id + 1;
		}
	}
}

void Pipe::search_pipename(unordered_set<int>& keys, const unordered_map<int, Pipe>& pipe_group, const string& name) {
	for (const auto& pair : pipe_group) {
		if (pair.second.namePipe.find(name) != string::npos) {
			keys.insert(pair.first);
		}
	}
}

void Pipe::search_piperepair(unordered_set<int>& keys, const unordered_map<int, Pipe>& pipe_group, const bool& inrep) {
	for (const auto& pair : pipe_group) {
		if (inrep == pair.second.repair) {
			keys.insert(pair.first);
		}
	}
}
void Pipe::delete_searched(unordered_map<int, Pipe>& pipe_group, const unordered_set<int>& keys) {
	for (const int& key : keys) {
		pipe_group.erase(key);
	}
}
void Pipe::show_searched(unordered_map<int, Pipe>& pipe_group, const unordered_set<int>& keys) {
	for (const int& key : keys) {
		cout << "ID: " <<key<< endl;
		cout << "Название: " <<pipe_group[key].namePipe<< endl;
		cout << "Длина: " << pipe_group[key].lenght<<endl;
		cout << "Диаметр: " << pipe_group[key].diametr<<endl;
		cout << "Находиться в ремонте (0-нет, 1-да): " << pipe_group[key].repair<<endl;
	}
}
void Pipe::edit_searched(unordered_map<int, Pipe>& pipe_group, const unordered_set<int>& keys) {
	for (const int& key : keys) {
		if (pipe_group.count(key) != 0) {
			cout << "Редактирование трубы ID" << key << " (" << pipe_group[key].namePipe << " )" << endl;
			cout << "Труба в ремонте? (1-да, 0-нет): ";
			pipe_group[key].repair = InputCor(0, 1);
		}
	}
}