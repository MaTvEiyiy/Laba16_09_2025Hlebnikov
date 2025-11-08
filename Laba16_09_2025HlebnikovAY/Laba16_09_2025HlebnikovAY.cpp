#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <format>
#include "Pipe.h"
#include "cs.h"
#include "dop.h"
#include "option.h"
#include <ctime>
#include <sstream>
#include <windows.h>

using namespace std;
using namespace chrono;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");
	unordered_set<int> keys;
	unordered_map<int, Pipe> pipe_group;
	unordered_map<int, ks>css;

	redirect_output_wrapper cerr_out(cerr);

	auto now = std::chrono::system_clock::now();
	time_t now_time_t = std::chrono::system_clock::to_time_t(now);
	tm local_tm;
	localtime_s(&local_tm, &now_time_t);

	char buf[100];
	strftime(buf, sizeof(buf), "%d_%m_%Y_%H_%M_%S", &local_tm);
	string time(buf);
	ofstream logfile("log_" + time);
	if (logfile) cerr_out.redirect(logfile);

	while (true) {
		menu();
		switch (InputCor(0, 10))
		{
		case 1:
			option1(pipe_group);
			break;

		case 2:
			option2(css);
			break;

		case 3: {
			option3(pipe_group, css);
			break;
		}
		case 4: {
			option4(pipe_group);
			break;
		}
		case 5: {
			option5(css);
			break;
		}
		case 6: {
			option6(pipe_group, css);
			break;
		}
		case 7: {
			option7(pipe_group, css);
			break;
		}
		case 8:option8(pipe_group, css);
			break;
		case 9:option9(pipe_group, css, keys);
			break;
		case 0: {
			cout << "До свидания!" << endl;
			return 0;
		case 10:
			view_logs();
			break;
		}
		default: {
			cout << "Такого пункта нет" << endl;
			break;
		}
		}
	}
	return 0;
}

