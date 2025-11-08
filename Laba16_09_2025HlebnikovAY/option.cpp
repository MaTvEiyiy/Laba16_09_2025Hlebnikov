#include "option.h"

using namespace std;
using namespace chrono;

void option1(unordered_map<int, Pipe>& pipe_group) {
	Pipe p;
	p.getPipe();
	pipe_group.emplace(p.get_id(), p);
	return;
}

void option2(unordered_map<int, ks>& css) {
	ks k;
	k.getks();
	css.emplace(k.get_id(), k);
	return;
}

void option3(unordered_map<int, Pipe>& pipe_group, unordered_map<int, ks>& css) {
	Pipe p;
	ks k;
	p.show_pipe(pipe_group);
	k.showks(css);
	return;
}
void option4(unordered_map<int, Pipe>& pipe_group) {
	if (!pipe_group.empty())ID_ver(pipe_group, 0);
	else cout << "У вас нет трубы!" << endl;
	return;
}

void option5(unordered_map<int, ks>& css) {
	if (!css.empty())ID_ver(css, 0);
	else cout << "У вас нет компрессорной станции!" << endl;
	return;
}

void option6(unordered_map<int, Pipe>& pipe_group, unordered_map<int, ks>& css) {
	string txt;
	Pipe p;
	ks k;
	cout << "Введите название файла" << endl;
	INPUT_LINE(cin, txt);
	ofstream fout(txt + ".txt");
	if (fout.is_open()) {
		p.savePipe(fout, pipe_group);
		k.saveks(fout, css);
		fout.close();
		cout << "Сохранено!" << endl;
	}
	else {
		cout << "Не получилось сохранить" << endl;
	}
	return;
}

void option7(unordered_map<int, Pipe>& pipe_group, unordered_map<int, ks>& css) {
	string filename;
	Pipe p;
	ks k;

	cout << "Введите название файла: " << endl;
	INPUT_LINE(cin, filename);
	ifstream fin(filename + ".txt");
	if (fin.is_open()) {
		k.loudks(fin, css);
		fin.clear();
		fin.seekg(0, ios::beg);
		p.loudPipe(fin, pipe_group);
		fin.close();
		cout << "Загружено! " << endl;
		cerr << filename << endl;
	}
	else cout << "Не получилось загрузить" << endl;
	return;
}

void option8(unordered_map<int, Pipe>& pipe_group, unordered_map<int, ks>& css) {
	delete_menu();
	switch (InputCor(1, 2)) {
	case 1: {
		if (!pipe_group.empty()) {
			ID_ver(pipe_group, 1);
			break;
		}
		else {
			cout << "У вас нет трубы!" << endl;
			break;
		}
	}
	case 2: {
		if (!css.empty()) {
			ID_ver(css, 1);
			break;
		}
		else {
			cout << "У вас нет КС!" << endl;
			break;
		}
	}
	default: {
			  break;
		  }
	}
	return;
}

void option9(unordered_map<int, Pipe>& pipe_group, unordered_map<int, ks>& css, unordered_set<int>& keys) {
	Pipe p;
	ks c;
	cin.clear();
	cin.ignore(1000, '\n');

	if ((pipe_group.size() == 0) && (css.size() == 00)) {
		cout << "Нет объектов" << endl;
		return;
	}
	sort_menu();
	string txt;
	bool flag;
	switch (InputCor(1, 4)) {
	case 1: {
		cin.clear();
		cin.ignore(1000, '\n');
		flag = true;
		cout << "Введите название трубы: " << endl;
		INPUT_LINE(cin, txt);
		p.search_pipename(keys, pipe_group, txt);
		if (keys.size() == 0) {
			cout << "Труба не найдена!" << endl;
			break;
		}
		p.show_searched(pipe_group, keys);
		break;
	}
	case 2: {
		cin.clear();
		cin.ignore(1000, '\n');
		bool rep;
		flag = true;
		cout << "Труба в ремонте? (0-нет, 1-да): "<<endl;
		rep = InputCor(0, 1);
		p.search_piperepair(keys, pipe_group, rep);
		if (keys.size() == 0) {
			cout << "Труба не найдена" << endl;
			break;
		}
		p.show_searched(pipe_group, keys);
		break;
	}
	case 3: {
		cin.clear();
		cin.ignore(1000, '\n');
		flag = false;
		cout << "Введите название КС: " << endl;
		INPUT_LINE(cin, txt);
		c.search_ksname(css, keys, txt);
		if (keys.size() == 0) {
			cout << "КС не найдена!" << endl;
			break;
		}
		c.show_searched(css, keys);
		break;
	}
	case 4: {
		cin.clear();
		cin.ignore(1000, '\n');
		flag = false;
		cout << "Введите количество работающих цехов: " << endl;
		int working_cex = InputCor(0, 1000);
		c.search_ks_working_cex(css, keys, working_cex);
		if (keys.size() == 0) {
			cout << "КС не найдена!" << endl;
			break;
		}
		c.show_searched(css, keys);
		break;
	}
	}
	if (keys.empty()) {
		return;
	}
	unordered_set<int>selected_keys;

	cout << "Хотите выбрать конкретные ID из найденных" << endl << "0-нет" << endl << "1-да" << endl;
	if (InputCor(0, 1) == 1) {
		cout << "Введите ID через пробел: ";
		cin.clear();
		cin.ignore(1000, '\n');
		INPUT_LINE(cin, txt);

		int number;
		istringstream stream(txt);
		while (stream >> number) {
			if (keys.find(number) == keys.end()) {
				cout << "ID не найдено: " << number << endl;
			}
			else {
				selected_keys.insert(number);
			}
		}

	}
	else {
		selected_keys = keys;
	}
	if (!selected_keys.empty()) {
		action();
		switch (InputCor(1, 2)) {
		case 1:
			if (flag) {
				p.delete_searched(pipe_group, selected_keys);
				cout << "Труба удалены! " << endl;
			}
			else {
				c.delete_searched(css, selected_keys);
				cout << "КС удалены!" << endl;
			}
			break;
		case 2:
			if (flag) {
				p.edit_searched(pipe_group, selected_keys);
				cout << "Труба отредактированы!" << endl;
			}
			else {
				c.edit_searched(css, selected_keys);
				cout << "KC отредактированы!" << endl;
			}
			break;
		}
	}
	else {
		cout << "Нет выбранных ID для обработки!" << endl;
	}
	keys.clear();
}