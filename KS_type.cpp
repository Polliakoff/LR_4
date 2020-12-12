#include "KS_type.h"
using namespace std;

int KS_type::sId = 0;

KS_type::KS_type() :id(sId++) {

}

int KS_type::get_id()const {
	return id;
}

void KS_type::vvod() {
	
	double input;
	string name_input;

    cout << endl << "Введите параметры для КС:" << endl;

	input_and_check(name_input, "название КС");
	name = name_input;
    
	cout << "Введите число цехов КС" << endl;

	input_and_check(input, 1);
	workshop_number = input;
	
	cout << "Введите число работающих цехов КС (<= числа цехов)" << endl;

	while (true) {
		input_and_check(input, 1);

		if (input <= workshop_number) {
			working_workshops = input;
			break;
		}
		else {
			cout << "Введите число <= числа цехов" << endl;
			continue;
		}
	}
	
	effectiveness = int((double(working_workshops) / double(workshop_number)) * 100 + 0.5) / 100.0;
	
	cout << "Ввод парамтеров завершен" << endl;

}

//изменение кол-ва рабочих цехов
void KS_type::edit() {    
	double ammount = 0;
	cout << "Введите число цехов (меньше нуля - выключить, больше нуля - включить)" << endl;
	
	while (true) {
		input_and_check(ammount, 1);
		
			if((working_workshops+ammount)<=workshop_number 
				&& (working_workshops + ammount) >= 0) working_workshops = working_workshops+ammount;
			else {
				cout << "Введите возможное число изменяемых цехов" << endl;
				continue;
			}
			break;
		
	}

	cout << "Число работающих цехов на данный момент :" << working_workshops << endl;

}

//загрузка из файла
void KS_type::load(std::string load_string) {

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
				workshop_number = stoi(temp_string);
				break;

			case 3:
				working_workshops = stoi(temp_string);
				break;

			case 4:
                for (size_t k = 0; k < temp_string.length(); k++) {
					if (temp_string[k] == '.') temp_string[k] = ',';
				}
				effectiveness = stod(temp_string);
				cout << "КС " << id << " Успешно Загружена!" << endl;
				break;
			}

			temp_string = "";
			j++;
		}
		if (i + 1 <= load_string.length())i++;
		else return;
	}
		else {
			if (i + 1 < load_string.length())i++;
			else return;
		}

	}

	

}

std::ostream& operator<<(std::ostream& os, const KS_type& k_t) {

	os << endl << "Параметры КС " << k_t.get_id() << endl;

	os << "Id КС : " << k_t.get_id() << endl;

	os << "Название КС: " << k_t.name << endl;

	os << "Число цехов КС: " << k_t.workshop_number << endl;

	os << "Число работающих цехов КС: " << k_t.working_workshops << endl;

	os << "Эффективность КС : " << k_t.effectiveness << endl;

	return os;

}

std::ofstream& operator<<(std::ofstream& ofs, const KS_type& k_t) {

	ofs << "k" << "|" << k_t.get_id()<< "|" << k_t.name << "|" <<
		k_t.workshop_number << "|" << k_t.working_workshops << "|" << k_t.effectiveness << "|" << endl;
	cout << "КС " << k_t.get_id() << " Успешно Сохранена!" << endl;

	return ofs;
}
