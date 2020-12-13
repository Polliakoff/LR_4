#include "KS_type.h"
#include "truba_type.h"
//#include "func.h"

using namespace std;

vector<int> find_by_parameter(map<int,truba_type>& pipes, const bool& output) {

    cout << "В ремонте ли труба? (y/n)" << endl;
    vector<int> found;
    while (true) {
        string str_selection;
        cin >> str_selection;
        if (str_selection == "y") {

            found = pipes_in_service(pipes, true);
            if (found.size() != 0) {
                for (auto i : found) {
                    if (output) cout<<pipes[i];
                }
            }
            break;
        }
        else if (str_selection == "n") {
            found = pipes_in_service(pipes, false);
            if (found.size() != 0) {

                for (auto i : found) {
                    if (output) cout<<pipes[i];
                }
            }
            break;
        }
        else {
            cout << "Введите y или n" << endl;
            continue;
        }
    }

    if (found.size() == 0) {
        if (output) cout << "Не найден ни один объект по заданным параметрам" << endl;
    }

    return found;
}

vector<int> find_by_parameter(map<int, KS_type>& KS_es, const bool& output) {

    cout << "Введите эффективность КС" << endl;
    double effectiveness;

    vector<int> found;

    while (true) {
        input_and_check(effectiveness);
        if (effectiveness > 0 && effectiveness < 1) {
            found = ks_by_eff(KS_es, effectiveness);
            if (found.size() > 0) {
                for (auto i : found) {
                    if (output) cout<<KS_es[i];
                }
            }
            break;
        }
        else {
            cout << "Введите вещественное число больше нуля и меньше единицы" << endl;
            continue;
        }
    }

    if (found.size() == 0) {
        if (output) cout << "Не найден ни один объект по заданным параметрам" << endl;
    }

    return found;
}

//void save_all(const map<int,truba_type>& pipes, const map<int,KS_type>& KS_es) {

//    ofstream fout;
//    string filename;

//    input_and_check(filename, "название Файла");

//    //сохранение в файл
//    fout.open(filename + ".clbr");

//    if (fout.is_open()) {

//        for (auto i : pipes) {
//            fout<<i.second;
//        }

//        for (auto i : KS_es) {
//            fout<<i.second;
//        }
//    }
//    else {
//        cout << "Не удалось открыть/создать файл для сохранения";
//    }

//    fout.close();
//}

//void load_all(map<int,truba_type>& pipes, map<int, KS_type>& KS_es) {
//    ifstream fin;//создание потока вывода из файла
//    string filename;

//    input_and_check(filename, "название Файла");

//    //сохранение труб в файл
//    fin.open(filename + ".clbr");

//    if (fin.is_open() == false) {
//        cout << "Не удалось открыть этот файл для загрузки" << endl;
//        return;
//    }

//    pipes.clear();
//    KS_es.clear();

//    string temp_string;
//    int max_KS_id = 0;
//    int max_pipe_id = 0;

//    while (std::getline(fin, temp_string)) {

//        if (temp_string[0] == 't') {
//            truba_type temp_truba;
//            temp_truba.load(temp_string);
//            if (temp_truba.get_id() > max_pipe_id) max_pipe_id = temp_truba.get_id();
//            pipes.emplace(temp_truba.get_id(), temp_truba);
//        }
//        else {
//            KS_type temp_KS;
//            temp_KS.load(temp_string);
//            if (temp_KS.get_id() > max_KS_id) max_KS_id = temp_KS.get_id();
//            KS_es.emplace(temp_KS.get_id(), temp_KS);
//        }
//    }

//    fin.close();
//}

void input_and_check(double& subject, const bool& int_check) {
    while (true) {
        subject = 0;
        cin >> subject;
        if (cin.good() && (!(subject - int(subject)) || int_check == 0)) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        else {
            if (int_check == 1) cout << "Введите целое число" << endl;
            else                cout << "Введите вещественное число" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void input_and_check(std::string& subject, const std::string& name) {

    cout << "Введите " << name << endl;
    getline(std::cin, subject);

}

void input_and_check(std::string& subject) {

    getline(std::cin, subject);

}

void menu() {

    cout << "Выберите действие которое необходимо осуществить: " <<
            endl << "1 - Добавить трубу " << endl << "2 - Добавить КС " << endl
         << "3 - Просмотр объектов " << endl << "4 - Редактировать трубу " << endl
         << "5 - Редактировать КС " << endl << "6 - Сохранить (Файлы перезаписываются) " << endl
         << "7 - Загрузить (введенные структуры удаляются и заменяются загруженнми из файла)"
         << endl << "8 - Вывести/редактировать трубы по фильтрам" << endl << "9 - Вывести/редактировать КС по фильтрам "
         << endl << "10 - Удаление Трубы" << endl << "11 - Удаление КС"
         << endl <<"12 - Создать пустую/очистить имеющуюся транспортную сеть" <<endl <<"13 - Редактировать транспортную сеть" <<endl
         <<"14 - Топологически отсортировать транспортную сеть" <<endl
         <<"15 - Вывести транспортную сеть" <<endl <<"16 - Найти кратчайший путь между двумя КС" <<endl
         << "0 - Выйти" << endl <<"Ввод : ";


}

vector<int> pipes_in_service(map <int,truba_type> pipes, bool in_service) {

    vector<int> return_vector;

    for (auto i:pipes) {
        if (i.second.in_servise == in_service) {
            return_vector.push_back(i.first);
        }
    }

    return return_vector;

}

vector<int> ks_by_eff(map<int, KS_type> KS_es, double effectiveness) {

    vector<int> return_vector;

    for (auto i:KS_es) {
        if (i.second.effectiveness == effectiveness) {
            return_vector.push_back(i.first);
        }
    }

    return return_vector;
}


