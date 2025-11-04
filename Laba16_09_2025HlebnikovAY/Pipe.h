#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "dop.h"


using namespace std;

class Pipe {
private:
	static int MaxID;
	int id = 0;
	string namePipe = "None";
	double lenght = 0;
	double diametr = 0;
	bool repair = false;
public:
	void getPipe();
	void show_pipe(const unordered_map<int, Pipe>&pipe_group);
	void edit();
	void savePipe(ofstream& fout, unordered_map<int, Pipe>& pipe_group);
	void loudPipe(ifstream& fin, unordered_map<int, Pipe>& pipe_group);
	int get_id();
	static int get_MaxID();
	void search_pipename(unordered_set<int>& keys, const unordered_map<int, Pipe>& pipe_group, const string& name);
	void search_piperepair(unordered_set<int>& keys, const unordered_map<int, Pipe>& pipe_group, const bool& inrep);
	void delete_searched(unordered_map<int, Pipe>& pipe_group, const unordered_set<int>& keys);
	void show_searched(unordered_map<int, Pipe>& pipe_group, const unordered_set<int>& keys);
	void edit_searched(unordered_map<int, Pipe>& pipe_group, const unordered_set<int>& keys);
};