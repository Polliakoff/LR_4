#ifndef TRANSPORT_NET_H
#define TRANSPORT_NET_H

#include "truba_type.h"
#include "KS_type.h"

class transport_net
{

private:
    set<int> strok_stolb;
    map<int,int> order;
    map<int,int> colour;
    void dfs(int vershina,stack<int> &sort_stack);
    stack<int> predki;

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



};

#endif // TRANSPORT_NET_H
