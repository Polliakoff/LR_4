#ifndef TRANSPORT_NET_H
#define TRANSPORT_NET_H

#include "truba_type.h"
#include "KS_type.h"

class transport_net
{

private:

    struct node{
        bool znak;
        int prev;
        double potok;
        int colour = white;


        node(){
        }


        node(bool znak_, int prev_, double potok_){
            znak = znak_;
            prev = prev_;
            potok = potok_;
        }

        node(bool znak_, int prev_, double potok_, int colour_){
            znak = znak_;
            prev = prev_;
            potok = potok_;
            colour = colour_;
        }
    };
    set<int> strok_stolb;
    map<int,int> order;
    map<int,int> colour;
    void dfs(int vershina,stack<int> &sort_stack);
    stack<int> predki;
    map<pair<int,int>, pair<double,bool>> deykstra_matrix;
    map<int, node>floyd_matrix;

    enum colours{
        white = 0,
        grey = 1,
        black = 2
    };



public:
    transport_net();
    map< pair<int,int>, int> m_smezhn;
    map <int, truba_type> pipes;
    map <int, KS_type> KS_es;

    void generate();
    void vivod(bool output = true);
    void edit();
    void sort();
    void new_pipe();
    void new_KS();
    void vivod_of_objects();
    void delete_pipe();
    void delete_KS();
    void save_all();
    void load_all();
    void find_way();
    void max_potok();



};

#endif // TRANSPORT_NET_H
