#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <windows.h>
#include "dop.h"
#include "Pipe.h"
#include "cs.h"
#include <fstream>
#include <sstream>

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

vector<string> get_log_files() {
    vector<string> log_files;

    WIN32_FIND_DATAA findFileData;
    HANDLE hFind = FindFirstFileA("log_*", &findFileData);

    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                string filename = findFileData.cFileName;
                if (filename.find("log_") == 0 && filename.find(".txt") == string::npos) {
                    log_files.push_back(filename);
                }
            }
        } while (FindNextFileA(hFind, &findFileData) != 0);

        FindClose(hFind);
    }

    sort(log_files.rbegin(), log_files.rend());

    return log_files;
}

void view_logs() {
    cout << "=== ПРОСМОТР LOG-ФАЙЛОВ ===" << endl;

    vector<string> log_files = get_log_files();

    if (log_files.empty()) {
        cout << "Log-файлы не найдены!" << endl;
        return;
    }

    cout << "Доступные log-файлы:" << endl;
    for (size_t i = 0; i < log_files.size(); ++i) {
        cout << i + 1 << ". " << log_files[i] << endl;
    }

    cout << "Выберите файл (1-" << log_files.size() << ") или 0 для отмены: ";
    int choice = InputCor(0, static_cast<int>(log_files.size()));

    if (choice == 0) {
        return;
    }

    string selected_file = log_files[choice - 1];

    ifstream logfile(selected_file);
    if (logfile.is_open()) {
        cout << "=== СОДЕРЖИМОЕ " << selected_file << " ===" << endl;
        string line;
        int line_count = 0;
        while (getline(logfile, line)) {
            cout << line << endl;
            line_count++;

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
        cout << "Ошибка открытия файла " << selected_file << "!" << endl;
    }
}

// Функция для парсинга данных трубы из строки
bool parse_pipe_data(const string& line, Pipe& pipe) {
    // Ищем паттерны в логе для извлечения данных трубы
    if (line.find("Название: ") != string::npos) {
        pipe.set_name(line.substr(10)); // Берем все после "Название: "
        return true;
    }
    else if (line.find("Длина трубы: ") != string::npos) {
        string length_str = line.substr(13);
        pipe.set_lenght(stod(length_str));
        return true;
    }
    else if (line.find("Диаметр трубы: ") != string::npos) {
        string diameter_str = line.substr(15);
        pipe.set_diametr(stod(diameter_str));
        return true;
    }
    else if (line.find("Состояние трубы") != string::npos) {
        size_t pos = line.find(":") + 1;
        string repair_str = line.substr(pos);
        pipe.set_repair(stoi(repair_str) == 1);
        return true;
    }
    return false;
}

// Функция для парсинга данных КС из строки
bool parse_ks_data(const string& line, ks& ks_obj) {
    if (line.find("Название станции: ") != string::npos) {
        ks_obj.set_name(line.substr(18));
        return true;
    }
    else if (line.find("Количество цехов: ") != string::npos) {
        string count_str = line.substr(18);
        ks_obj.set_count_cex(stoi(count_str));
        return true;
    }
    else if (line.find("Количесвто работающих цехов: ") != string::npos) {
        string count_str = line.substr(29);
        ks_obj.set_count_cex_work(stoi(count_str));
        return true;
    }
    else if (line.find("Класс КС: ") != string::npos) {
        string class_str = line.substr(10);
        ks_obj.set_klass(stoi(class_str));
        return true;
    }
    return false;
}

// Основная функция восстановления данных из log-файла
void restore_from_log(const string& filename, unordered_map<int, Pipe>& pipe_group, unordered_map<int, ks>& css) {
    cout << "=== ВОССТАНОВЛЕНИЕ ДАННЫХ ИЗ LOG-ФАЙЛА ===" << endl;

    ifstream logfile(filename);
    if (!logfile.is_open()) {
        cout << "Ошибка открытия файла " << filename << "!" << endl;
        return;
    }

    unordered_map<int, Pipe> restored_pipes;
    unordered_map<int, ks> restored_css;

    string line;
    Pipe current_pipe;
    ks current_ks;
    bool is_reading_pipe = false;
    bool is_reading_ks = false;
    int max_pipe_id = 0;
    int max_ks_id = 0;

    while (getline(logfile, line)) {
        if (line.empty()) continue;

        if (line.find("PIPE_NAME:") != string::npos) {
            current_pipe.set_name(line.substr(10));
            is_reading_pipe = true;
            is_reading_ks = false;
        }
        else if (line.find("PIPE_LENGTH:") != string::npos) {
            current_pipe.set_lenght(stod(line.substr(12)));
        }
        else if (line.find("PIPE_DIAMETER:") != string::npos) {
            current_pipe.set_diametr(stod(line.substr(14)));
        }
        else if (line.find("PIPE_REPAIR:") != string::npos) {
            current_pipe.set_repair(stoi(line.substr(12)) == 1);
        }
        else if (line.find("PIPE_ID:") != string::npos) {
            int id = stoi(line.substr(8));
            current_pipe.set_id(id);
            restored_pipes[id] = current_pipe;
            max_pipe_id = max(max_pipe_id, id);
            current_pipe = Pipe(); // Сбрасываем для следующей трубы
        }
        else if (line.find("KS_NAME:") != string::npos) {
            current_ks.set_name(line.substr(8));
            is_reading_ks = true;
            is_reading_pipe = false;
        }
        else if (line.find("KS_CEX_COUNT:") != string::npos) {
            current_ks.set_count_cex(stoi(line.substr(13)));
        }
        else if (line.find("KS_CEX_WORKING:") != string::npos) {
            current_ks.set_count_cex_work(stoi(line.substr(15)));
        }
        else if (line.find("KS_CLASS:") != string::npos) {
            current_ks.set_klass(stoi(line.substr(9)));
        }
        else if (line.find("KS_ID:") != string::npos) {
            int id = stoi(line.substr(6));
            current_ks.set_id(id);
            restored_css[id] = current_ks;
            max_ks_id = max(max_ks_id, id);
            current_ks = ks(); // Сбрасываем для следующей КС
        }
    }

    logfile.close();

    // Заменяем текущие данные
    if (!restored_pipes.empty()) {
        pipe_group = restored_pipes;
        Pipe::set_MaxID(max_pipe_id + 1);
        cout << "✓ Восстановлено труб: " << pipe_group.size() << endl;
    }

    if (!restored_css.empty()) {
        css = restored_css;
        ks::set_MaxID(max_ks_id + 1);
        cout << "✓ Восстановлено КС: " << css.size() << endl;
    }

    cout << "=== ВОССТАНОВЛЕНИЕ ЗАВЕРШЕНО ===" << endl;
}