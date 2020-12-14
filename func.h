#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <map>
#include <algorithm>
#include <stack>
#include <numeric>
#include <set>
#include <cmath>

using namespace std;

class truba_type;
class KS_type;

void menu();
//void save_all(const map<int, truba_type>& pipes, const map<int, KS_type>& KS_es);
//void load_all(map<int, truba_type>& pipes, map<int, KS_type>& KS_es);
void input_and_check(double& subject, const bool& int_check = 0);
void input_and_check(std::string& subject, const std::string& name);
void input_and_check(std::string& subject);
vector<int> find_by_parameter(map<int, truba_type>& pipes, const bool& output = 1);
vector<int> find_by_parameter(map<int,KS_type>& KS_es, const bool& output = 1);
vector<int> pipes_in_service(map <int, truba_type> pipes, bool in_service);
vector<int> ks_by_eff(map<int, KS_type> KS_es, double effectiveness);

template <typename T> void id_presence(map<int, T>& objects,double &id_selection,  bool vivod = true) {

    if(objects.size()>0){
        if(vivod) cout << "������� id ������� " << endl;

        while(true){
            input_and_check(id_selection, 1);

            if (!(objects.find(int(id_selection)) != objects.end())) {
                cout << "������� id ������ �� ������������ ��������" << endl;
            }
            else {
                return;
            }
        }
    }
    else{
        cout << "��� �� ������ �������" << endl;
    }
}

template <typename T> void edit_by_id(map<int, T>& objects) {
    double id_selection;
    id_presence(objects,id_selection);
    objects[int(id_selection)].edit();
}

template <typename T> void package_edit(vector<int>& found, map<int, T>& objects) {

    if (found.size() != 0) {
        cout << "������ ������������� ��������� �������? (y/n)" << endl;
        while (true) {
            string str_selection;
            cin >> str_selection;
            if (str_selection == "y") {
                for (auto i : found) {
                    objects[i].edit();
                }
                break;
            }
            else if (str_selection == "n") {
                found.clear();
                return;
            }
            else {
                cout << "������� y ��� n" << endl;
            }
        }
    }
}

template <typename T> vector<int> name_to_id(map<int,T> objects, std::string name)
{
    vector<int> return_vector;

    for (auto i: objects) {
        if (i.second.name == name) {
            return_vector.push_back(i.first);
        }
    }

    return return_vector;

}

template <typename T> vector<int> find_by_name(map<int,T>& objects, const bool& output = 1) {
    string name_selection;
    input_and_check(name_selection, "��������, �� �������� ����� ���������� �����");

    vector <int> found = name_to_id(objects, name_selection);
    if (found.size() > 0) {
        for (auto i : found) {
            if (output) cout<<objects[i];
        }
    }
    else {
        if(output) cout << "������� ���� �� �������� c����������� ���� (����� ���������� �������� 3)" << endl;
    }
    if (found.size() == 0) {
        if (output) cout << "�� ������ �� ���� ������ �� �������� ����������" << endl;
    }

    return found;
}

template <typename T> vector<int> find_by_filter(map<int,T>& objects) {

    vector<int> found_1 = find_by_name(objects,0);
    vector<int> found_2 = find_by_parameter(objects,0);
    vector<int> found;

    for (auto i : found_1) {
        for (auto j : found_2) {
            if (i == j) {
                found.push_back(i);
                cout<<objects[i];
            }
        }
    }

    if (found.size() == 0) {
        cout << "�� ������ �� ���� ������ �� �������� ����������" << endl;
    }

    return found;
}

template <typename T> void switch_search(map<int,T>& objects) {

    vector<int> found;
    double selection;

    cout << "�������� ������� ����������: " << endl <<
            "1 - ����� �� �������� (������/����� ���. �����)" << endl << "2 - ����� �� �������� " << endl
         << "3 - ����� �� �������� � �������� � �������" << endl;

    while (true) {

        input_and_check(selection, 1);

        switch (int(selection)) {

        case 1: {
            found = find_by_parameter(objects);
        }
            break;
        case 2: {
            found = find_by_name(objects);
        }
            break;
        case 3: {
            found = find_by_filter(objects);
        }
            break;
        default: {
            cout << "������� 1 - 3" << endl;
        }
            break;
        }
        package_edit(found, objects);
        break;
    }
}








