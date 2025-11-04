#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <unordered_set>
#include <chrono>
#include "Pipe.h"
#include "cs.h"
#include "dop.h"

using namespace std;

void option1(unordered_map<int, Pipe>& pipe_group);
void option2(unordered_map<int, ks>& css);
void option3(unordered_map<int, Pipe>& pipe_group, unordered_map<int, ks>& css);
void option4(unordered_map<int, Pipe>& pipe_group);
void option5(unordered_map<int, ks>& css);
void option6(unordered_map<int, Pipe>& pipe_group, unordered_map<int, ks>& css);
void option7(unordered_map<int, Pipe>& pipe_group, unordered_map<int, ks>& css);
void option8(unordered_map<int, Pipe>& pipe_group, unordered_map<int, ks>& css);
void option9(unordered_map<int, Pipe>& pipe_group, unordered_map<int, ks>& css,unordered_set<int>&keys);
