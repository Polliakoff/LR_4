#include "transport_net.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
    //создание графа транспортной сети:
    transport_net net;
    //массивы классов
    net.pipes.clear();
    net.KS_es.clear();
	string temp_string;//врмененна€ строкова€ переменна€ (объ€влена сверху т. к. используетс€ повсеместно)
	while (true) {
		menu();
		//переменные выбора действи€
		double selection; 
		string str_selection;
		input_and_check(selection, 1);
			switch (int(selection)) {

			case 1:{
                net.new_pipe();
			}
				  break;
			case 2: {
                net.new_KS();
			}
				break;
			case 3: {
                net.vivod_of_objects();
			}
				break;
			case 4: {
                edit_by_id(net.pipes);
			}
				break;
			case 5: {
                edit_by_id(net.KS_es);
			}
				break;
			case 6: {
                net.save_all();
			}
				break;
			case 7: {
                net.load_all();
			}
				break;
			case 8: {
                switch_search(net.pipes);
			}
				  break;
			case 9: {
                switch_search(net.KS_es);
			}
				  break;
			case 10:{
                net.delete_pipe();
			}
				 break;
			case 11: {
                net.delete_KS();
			}
                break;
            case 12: {
               net.generate();
            }
				  break;
            case 13: {
               net.edit();
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
            case 16: {
               net.find_way();
            }
                  break;
            case 17: {
               net.max_potok();
            }
                  break;
			case 0: {
				return 0;
			}
				  break;
			default: {
                cout << "введите цифру от 0 до 16 дл€ выбора действи€" << endl;
			}
				   break;
			}

        std::system("pause");
        std::system("cls");
	}
	return 0;
}
