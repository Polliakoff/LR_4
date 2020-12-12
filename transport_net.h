#ifndef TRANSPORT_NET_H
#define TRANSPORT_NET_H

#include "truba_type.h"
#include "KS_type.h"

class transport_net
{

private:
    vector<int> strok_stolb;
    map<int,int> order;
    map<int,int> colour;
    void dfs(int vershina,stack<int> &sort_stack);
    stack<int> predki;

public:
    transport_net();
    map< pair<int,int>, int> m_smezhn;

    void generate(map<int,KS_type> &KS_es, map<int,truba_type> &pipes);
    void vivod(bool output = true);
    void edit(map<int,truba_type> &pipes, map<int,KS_type> &KS_es);
    void sort();

};

#endif // TRANSPORT_NET_H
