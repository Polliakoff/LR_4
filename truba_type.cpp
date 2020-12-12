#include "truba_type.h"

using namespace std;

int truba_type::sId = 0;

truba_type::truba_type():id(sId++) {

}

int truba_type::get_id()const {
	return id;
}

void truba_type::vvod() {
	string name_input;
	double input;


    cout << endl << "Введите параметры для Трубы:" << endl;

	input_and_check(name_input, "название трубы");
	name = name_input;

	cout << "Введите длину трубы" << endl;
	input_and_check(input);
	length = input;

	cout << "Введите диаметр трубы" << endl;
	input_and_check(input);
	diameter = input;

	cout << "Ввод парамтеров завершен"<<endl;

}

//Изменения статуса в ремонте
void truba_type::edit() {

	   string input;

		cout << endl << "В ремонте ли труба (y/n)" << endl;
		cin >> input;

		while (true) {

			if (input == "y") {
				in_servise = 1;
				break;
			}
			else if (input == "n") {
				in_servise = 0;
				break;
			}
			else {
				cout << "Введите 'y' или 'n' (строчными буквами)";
			}
			cout << endl;
			cin >> input;
		}

		if (in_servise == 1) input = "y";
		else input = "n";
	
}

void truba_type::load(std::string load_string) {
	
	string temp_string; //временная строка

	//счетчики для цикла
    size_t i = 0;
    size_t j = 0;
	temp_string = "";//инициализируем временную строку
	while (true) {

		if (i > 1) {
			if (load_string[i] != '|') {
				temp_string += load_string[i];
			}
			else {
				switch (j) {
				case 0:
					id = stoi(temp_string);
					sId = id+1;
					break;
				
				case 1:
					name = temp_string;
					break;
				
				case 2:
                    for (size_t k = 0; k < temp_string.length(); k++) {
						if (temp_string[k] == '.') temp_string[k] = ',';
					}
					length = stod(temp_string);
					break;
				case 3:
                    for (size_t k = 0; k < temp_string.length(); k++) {
						if (temp_string[k] == '.') temp_string[k] = ',';
					}
					diameter = stod(temp_string);
					break;

				case 4:
					in_servise = stoi(temp_string);
					cout << "Труба " << id << " Успешно Загружена!" << endl;
					break;
				}

				temp_string = "";
				j++;
			}
			
			if (i + 1 < load_string.length())i++;
			else return;
		}
		else {
			if (i + 1 < load_string.length())i++;
			else return;
		}
		
	}
	
}

std::ostream& operator<<(std::ostream& os, const truba_type& t_t) {


	os << endl << "Параметры Трубы " << t_t.get_id()<< endl;

	os << "Id трубы : " << t_t.get_id() << endl;

	os << "Название трубы: " << t_t.name << endl;

	os << "Длина трубы: " << t_t.length << endl;

	os << "Диаметр трубы: " << t_t.diameter << endl;

	string service_status; //временная строка

	if (t_t.in_servise == 1) service_status = "yes";
	else service_status = "no";

	os << "В ремонте ли труба (yes/no) : \t " << service_status << endl;

	return os;
}

std::ofstream& operator<<(std::ofstream& ofs, const truba_type& t_t) {

	ofs << "t" << "|" << t_t.get_id() << "|" << t_t.name << "|" << t_t.length << "|" <<
		t_t.diameter << "|" << t_t.in_servise << "|" << endl;
	cout << "Труба " << t_t.get_id() << " Успешно Сохранена!" << endl;

	return ofs;
}


