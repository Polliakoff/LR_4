#include "transport_net.h"

using namespace std;

transport_net::transport_net()
{

}

void transport_net::generate(map<int,KS_type> &KS_es, map<int,truba_type> &pipes)
{
    for(auto &i:pipes){
        i.second.connected = 0;
    }

    strok_stolb.clear();
    m_smezhn.clear();
    order.clear();

    if(KS_es.size()>0){

        for(auto i : KS_es){
            strok_stolb.push_back(i.first);
            for(auto j : KS_es){
                m_smezhn.emplace(make_pair(i.first, j.first), -1);
            }
        }

        cout<<"������������ ���� ������� ������� (-1 = ���� �����, ����� ������ ����� = id ����������� �����)"<<endl;
        vivod(false);
    }

    else{
        cout<<"���� �� "<<endl;
    }

}

void transport_net::edit(map<int,truba_type> &pipes, map<int,KS_type> &KS_es)
{
    string selection, selection_1;
    bool are_there_any = false;
    double id_begin = -1, id_end = -1, pipe_id = -1;
    if(m_smezhn.size()>0){
        while(true){

            vivod();

            while(true){
                cout<<"������ �� �� ������������� ������������ ���� (y/n)?"<<endl;
                cin>>selection;
                if(selection == "y"){
                    cout<<"������� ��� id ��: "<<endl;

                    cout<<"Id �� - ������: "<<endl;
                    id_presence(KS_es,id_begin, false);

                    cout<<"Id �� - �����: "<<endl;
                    id_presence(KS_es,id_end, false);

                    cout<<"�� ������ ��������� �� ������ ��� ��������� ����� ����� ���� ?"<<
                          endl<<"1 - ��������� 2- ���������"<<endl;
                    while(true){
                        cin>>selection_1;
                        if(selection_1 == "1")
                        {
                            cout<<"������� id �����, ����������� �� : "<<endl;
                            while(true){
                                cout<<"��������� �����: "<<endl;
                                for(auto i:pipes){
                                    if(i.second.connected == 0){
                                        cout<<i.second;
                                        are_there_any = true;
                                    }
                                }
                                if(are_there_any == false){
                                    cout<<"��� ��������� ����, ���������� ����� ���������� "<<endl;
                                    return;
                                }
                                cout<<endl;
                                id_presence(pipes, pipe_id, false);
                                if(pipes[int(pipe_id)].connected == 0){
                                    pipes[int(pipe_id)].connected=1;
                                    break;
                                }
                                else{
                                    cout<<"�� ����� Id ��� �������������� �����";
                                }
                                are_there_any = false;
                            }

                            if( m_smezhn[make_pair(id_begin, id_end)] == -1){
                                m_smezhn[make_pair(id_begin, id_end)] = pipe_id;
                            }
                            else {
                                pipes[m_smezhn[make_pair(id_begin, id_end)]].connected = 0;
                                m_smezhn[make_pair(id_begin, id_end)] = pipe_id;
                            }
                            break;
                        }
                        else if(selection_1 == "2"){
                            if( m_smezhn[make_pair(id_begin, id_end)] == -1){
                                cout<<"������ �� ��� �� �������"<<endl;
                            }
                            else {
                                pipes[m_smezhn[make_pair(id_begin, id_end)]].connected = 0;
                                m_smezhn[make_pair(id_begin, id_end)] = -1;
                            }
                            break;
                        }
                        else{
                            cout<<"������� 1 ��� 2";
                        }
                    }
                    break;
                }
                else if(selection == "n"){
                    return;
                }
                else{
                    cout<<"������� y ��� n ��������� �������"<<endl;
                }
            }
        }
    }
    else{
        cout<<"������������ ���� �� �������"<<endl;
    }
}

void transport_net::vivod(bool output)
{   
    if(m_smezhn.size()>0){
        if (output) cout<<"������������ ���� �� ������ ������ (-1 = ���� �����, ����� ������ ����� = id ����������� �����)"
                       <<endl;
        for(auto i : strok_stolb)
        {
            cout<<"\t"<<i;
        }
        cout<<endl;

        for(auto i : strok_stolb)
        {
            cout<<i;
            for(auto j : strok_stolb)
            {
                cout<<"\t"<<m_smezhn[make_pair(i,j)];
            }
            cout<<endl;
        }
    }
    else{
        cout<<"������������ ���� �� �������"<<endl;
    }

    if(order.size()>0){
        cout<<"������ ������ �� �������������� ���������� (����� - �������): "<<endl;
        for(auto i:order){
            cout<<i.first<<"\t"<<i.second<<endl;
        }
    }
    else{
        cout<<"���� �� ������������� "<<endl;
    }
}

void transport_net::sort()
{
    if(m_smezhn.size()>0){

        // 0 - ����� 1 - ����� 2 - ������
        //�������� ��� ������� � �����
        colour.clear();
        for(auto i : strok_stolb)
        {
            colour.emplace(i,0);
        }

        //������ ������, ���������� ����� �������� � �����
        vector<int> zahod;
        stack<int> null_zahod;
        stack<int> sort_stack;
        for(auto i : strok_stolb)
        {
            for(auto j : strok_stolb)
            {
                zahod.push_back(m_smezhn[make_pair(j,i)]);
            }

            if(accumulate(zahod.begin(), zahod.end(), 0) == int(zahod.size())*(-1)){
                null_zahod.push(i);
            }
            zahod.clear();
        }

        if(null_zahod.size() == 0){
            cout<<"� ���� ���� ����, �������������� ���������� �� ��������"<<endl;
            return;
        }
        else{
            while(!predki.empty())
                predki.pop();

            predki.push(-1);

            while(!sort_stack.empty())
                sort_stack.pop();

            order.clear();

            while(!null_zahod.empty()){
                dfs(null_zahod.top(), sort_stack);
                null_zahod.pop();
            }
            int i = 1;
            while(!sort_stack.empty()){
                order.emplace(i, sort_stack.top());
                sort_stack.pop();
                i++;
            }
            if(order.size()>0){
                cout<<"��������������� ��: "<<endl;
                for(auto i:order){
                    cout<<i.first<<"\t"<<i.second<<endl;
                }
            }
        }
    }
    else{
        cout<<"������������ ���� �� �������"<<endl;
    }
}

void transport_net::dfs(int vershina,stack<int> &sort_stack)
{
    bool there_is_way = false;
    if(colour[vershina] == 0) colour[vershina] = 1;
    if(predki.top()!=vershina)predki.push(vershina);

    for(auto sled_vershina: strok_stolb){
        if(m_smezhn[make_pair(vershina,sled_vershina)]!=-1){
            if(colour[sled_vershina]==0){
                there_is_way = true;
                dfs(sled_vershina,sort_stack);
                return;
            }
            else if(colour[sled_vershina]==1){
                cout<<"� ���� ���� ����, �������������� ���������� �� ��������"<<endl;
                while(!sort_stack.empty())
                    sort_stack.pop();
                return;
            }
        }
    }
    if(there_is_way == false){
        predki.pop();
        if(predki.top()!=-1){
            colour[vershina] = 2;
            sort_stack.push(vershina);
            dfs(predki.top(),sort_stack);
        }
        else{
            colour[vershina] = 2;
            sort_stack.push(vershina);
            return;
        }
    }
}




