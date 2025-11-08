#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "dop.h"

using namespace std;

class ks {
public:
	void getks();
	void showks(const unordered_map<int, ks>& css);
	void edit();
	void saveks(ofstream& fout, unordered_map<int, ks>& css);
	void loudks(ifstream& fin, unordered_map<int, ks>& css);
	int get_id();
	static int get_MaxID();
	void search_ksname(const unordered_map<int, ks>& css, unordered_set<int>& keys, const string& name);
	void delete_searched(unordered_map<int, ks>& css, const unordered_set<int>& keys);
	void edit_searched(unordered_map<int, ks>& css, const unordered_set<int>& keys);
	void show_searched(unordered_map<int, ks>& css, const unordered_set<int>& keys);
	void search_ks_working_cex(const unordered_map<int, ks>& css, unordered_set<int>& keys, int percent);//тут такая
private:
	static int MaxID;
	int id = 0;
	string ksname = "None";
	int count_cex = 0;
	int count_cex_work = 0;
	int klass = 0;
};