#include "transport_net.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
    //создание графа транспортной сети:
    transport_net net;
    //массивы классов
    map <int, truba_type> pipes;
    map <int, KS_type> KS_es;
	string temp_string;//врмененная строковая переменная (объявлена сверху т. к. используется повсеместно)
	while (true) {
		menu();
		//переменные выбора действия
		double selection; 
		string str_selection;
		input_and_check(selection, 1);
			switch (int(selection)) {

			case 1:{
				//создание новой пустой трубы и помещение ее в вектор труб
				truba_type temp_truba;
				temp_truba.vvod();
				pipes.emplace(temp_truba.get_id(),temp_truba);
			}
				  break;
			case 2: {
				//создание новой пустой КС и помещение ее в вектор КС
				KS_type temp_KS;
				temp_KS.vvod();
				KS_es.emplace(temp_KS.get_id(), temp_KS);
			}
				break;
			case 3: {
                vivod_vsego(pipes, "трубы");
				vivod_vsego(KS_es, "КС");
			}
				break;
			case 4: {
				edit_by_id(pipes);
			}
				break;
			case 5: {
				edit_by_id(KS_es);
			}
				break;
			case 6: {
				save_all(pipes, KS_es);
			}
				break;
			case 7: {
				load_all(pipes, KS_es);
			}
				break;
			case 8: {
				switch_search(pipes);
			}
				  break;
			case 9: {
				switch_search(KS_es);
			}
				  break;
			case 10:{
                delete_object(pipes);
			}
				 break;
			case 11: {
                delete_object(KS_es);
			}
                break;
            case 12: {
               net.generate(KS_es,pipes);
            }
				  break;
            case 13: {
               net.edit(pipes,KS_es);
            }
                  break;
            case 14: {
                net.sort();
            }
                  break;
            case 15: {
               net.vivod();
            }
                  break;
			case 0: {
				return 0;
			}
				  break;
			default: {
                cout << "введите цифру от 0 до 15 для выбора действия" << endl;
			}
				   break;
			}

        std::system("pause");
        std::system("cls");
	}
	return 0;
}
