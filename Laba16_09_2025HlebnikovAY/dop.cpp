#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>
#include "dop.h"

using namespace std;

void menu() {
	cout <<
		"0. Выход\n" <<
		"1. Добавить новую трубу\n" <<
		"2. Добавить новую КС\n" <<
		"3. Показать все объекты\n" <<
		"4. Редактировать трубу\n" <<
		"5. Редактировать КС\n" <<
		"6. Сохранить файл\n" <<
		"7. Загрузить из файла\n" <<
		"8.Удалить объект\n" <<
		"9. Фильтр\n" << 
        "10. просмотр log-файлов "<<endl;
}

void sort_menu() {
	cout <<
		"0. Выход\n" <<
		"1. Просмотреть трубу по названию\n" <<
		"2. Просмотреть трубу по состоянию\n" <<
		"3. Просмотреть КС по названию\n" <<
		"4. Просмотреть КС по количеству цехов" << endl;
}

void delete_menu() {
	cout <<
		"Удалить:\n" <<
		"1. Трубу\n" <<
		"2. КС" << endl;
}

void action() {
	cout <<
		"1. Удалить\n" <<
		"2. Редактировать\n";//тут подумать
}

void view_logs() {
    cout << "=== ПРОСМОТР LOG-ФАЙЛОВ ===" << endl;
    cout << "Введите имя log-файла (например: log_16_09_2025_14_30_25): ";

    string filename;
    INPUT_LINE(cin, filename);

    ifstream logfile(filename);
    if (logfile.is_open()) {
        cout << "=== СОДЕРЖИМОЕ " << filename << " ===" << endl;
        string line;
        int line_count = 0;
        while (getline(logfile, line)) {
            cout << line << endl;
            line_count++;

            // Пауза каждые 20 строк
            if (line_count % 20 == 0) {
                cout << "--- Нажмите Enter для продолжения ---";
                cin.ignore();
                cin.get();
            }
        }
        logfile.close();
        cout << "=== КОНЕЦ ФАЙЛА ===" << endl;
    }
    else {
        cout << "Ошибка открытия файла " << filename << "!" << endl;
        cout << "Убедитесь что файл существует в папке с программой" << endl;
    }
}