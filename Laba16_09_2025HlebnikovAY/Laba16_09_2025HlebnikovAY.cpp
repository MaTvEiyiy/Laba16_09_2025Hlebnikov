#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

struct Pipe {
	string namePipe="";
	double lenght=0;
	double diametr=0;
	bool repair =  0;
};

struct KompresCtation {
	string nameKC="";
	int count_cex=0;
	int count_cex_work=0;
	int klass=0;
};

template <typename T>
void InputCor(T& var)
{
	cin >> var;
	while (cin.fail() || cin.peek() != '\n' || var < 0) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Ошибка, введите коректное значение!";
		cin >> var;
	}
}

void getPipe(Pipe& p) {
	if (p.namePipe!= "") {
		cout << "У вас уже есть труба" << endl;
	}
	else {
		cout << "Введите название трубы: ";
		cin.ignore(1000, '\n');
		getline(cin, p.namePipe);
		while (p.namePipe == "") {
			cout << "Название не может быть пустым!" << endl;
			getline(cin, p.namePipe);
		}
		cout << "Введите длину: ";
		InputCor(p.lenght);
		cout << "Введите диаметр: ";
		InputCor(p.diametr);
		cout << "Труба в ремонте? (1-да, 0-нет): ";
		InputCor(p.repair);
	}
 }

void getKC(KompresCtation& c) {
	if (c.nameKC != "") {
		cout << "У вас уже есть Компрессорная станция" << endl;
	}
	else {
		cout << "Введите название компрессорной станции: ";
		cin.ignore(1000, '\n');
		getline(cin, c.nameKC);
		while (c.nameKC == "") {
			cout << "Название не может быть пустым!" << endl;
			getline(cin, c.nameKC);
		}
		cout << "Введите количество цехов: ";
		InputCor(c.count_cex);
		cout << "Введите количество работающих цехов: ";
		InputCor(c.count_cex_work);
		while (c.count_cex_work > c.count_cex) {
			cout << "Количество работающих цехов превыщает количество цехов! '\n' Введите корректное значение";
			InputCor(c.count_cex_work);
		}
		cout << "Введите класс станции (от 1 до 5): ";
		InputCor(c.klass);
		while (1 > c.klass || 5 < c.klass) {
			cout << "Введите коректное значение: ";
			InputCor(c.klass);
		}
	}
}
void show_pipe(Pipe p) {
	if (p.namePipe == "") {
		cout << "У вас нет трубы" << endl;
	}
	else {
		cout << "------Ваша труба!-------" << endl;
		cout << "Название: " << p.namePipe << endl;
		cout << "Длина трубы: " << p.lenght << endl;
		cout << "Диаметр трубы: " << p.diametr << endl;
		cout << "Состояние трубы (1-в ремонте, 0-не в ремонте):" << p.repair << endl;
	}

}

void show_ks(KompresCtation& c) {
	if (c.nameKC == "") {
		cout << "У вас нет КС" << endl;
	}
	else {
		cout << "----Ваша компрессорная станция----" << endl;
		cout << "Название станции: " << c.nameKC << endl;
		cout << "Количество цехов: " << c.count_cex << endl;
		cout << "Количесвто работающих цехов: " << c.count_cex_work << endl;
		cout << "Класс КС: " << c.klass << endl;
	}

}
void changPipe(Pipe& p) {
	if (p.namePipe=="") {
		cout << "У вас еще нет трубы!" << endl;
	}
	else {
		p.repair = 0;
		cout << "Введите состояние трубы (1-в ремонте, 0-работает): " << endl;
		InputCor(p.repair);
	}
}
void changKS(KompresCtation& c) {
	if (c.nameKC=="") {
		cout << "У вас нет Компрессорной станции" << endl;
	}
	else {
		cout << "Введите количество работающих цехов" << endl;
		InputCor(c.count_cex_work);
		while (c.count_cex_work > c.count_cex) {
			cout << "Количество работающих цехов превыщает количество цехов! '\n' Введите корректное значение";
			InputCor(c.count_cex_work);
		}
	}
}
void savePipe(ofstream& fout, const Pipe& p) {// const чтобы значение трубы нельхя было изменить
	string Marker = "Труба";
	if (p.namePipe == "") {
		fout << Marker << endl;
	}
	else{
		fout << p.namePipe << endl;
		fout << p.lenght << endl;
		fout << p.diametr << endl;
		fout << p.repair << endl;
	}
}
void saveKS(ofstream& fout, const KompresCtation& c) {
	string Marker = "КС";
	if (c.nameKC == "") {
			fout << Marker << endl;
	}
	else{
		fout << c.nameKC << endl;
		fout << c.count_cex << endl;
		fout << c.count_cex_work<< endl;
		fout << c.klass << endl;
	}
}
Pipe loudPipe(ifstream& fin, Pipe& p) {
	string Marker;
	getline(fin >> ws, Marker);
	if (Marker == "Труба") {
		return p = { "",0,0,0 };
	}
	else {
		p.namePipe = Marker;
		fin >> p.lenght;
		fin >> p.diametr;
		fin >> p.repair;
		return p;
	}
}
KompresCtation loudKS(ifstream& fin, KompresCtation& c) {
	string Marker;
	getline(fin >> ws, Marker);
	if (Marker == "КС") {
		return c = { "",0,0,0 };
	}
	else {
		c.nameKC = Marker;
		fin >> c.count_cex;
		fin >> c.count_cex_work;
		fin >> c.klass;
		return c;
	}
}
void menu() {
	cout << "-------MENU-------" << endl;
	cout << "1. Добавить трубу" << endl;
	cout << "2. Добавить КС" << endl;
	cout << "3. Редактировать состояние трубы" << endl;
	cout << "4. Редактировать количество работающих цехов" << endl;
	cout << "5. Просмотр всех объектов" << endl;
	cout << "6. Загрузить в файл" << endl;
	cout << "7. Выгрузить из файла" << endl;
	cout << "0. Выход" << endl;


}
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	Pipe p;
	KompresCtation c;
	int vibor;
	string filename = "save.txt";
	while (true) 
	{
		menu();




		cout << "Введите номер команды: ";
		cin.clear(1000, '\n');
		InputCor(vibor);

		switch (vibor)
		{
		case 1:
			getPipe(p);
			break;

		case 2:
			getKC(c);
			break;

		case 3: {
			changPipe(p);
			break;
		}
		case 4: {
			changKS(c);
			break;
		}
		case 5: {
			show_pipe(p);
			show_ks(c);
			break;
		}
		case 6: {
			ofstream fout(filename);
			if (fout.is_open()) {
				savePipe(fout, p);
				saveKS(fout, c);
				cout << "Данные сохранены" << endl;
			}
			else {
				cout << "файл не открывается" << endl;
			}
			break;
		}
		case 7: {
			ifstream fin(filename);
			if (fin.is_open()) {
				loudPipe(fin, p);
				loudKS(fin, c);
				fin.close();
				cout << "Данные загружены из файла" << endl;
			}
			else {
				cout << "Файл не открылся" << endl;
			}
			break;
		}
		case 0: {
			cout << "До свидания!" << endl;
			return 0;
		}
		default: {
			cout << "Такого пункта нет" << endl;
			break;
		}
		}
	}
	return 0;

}
