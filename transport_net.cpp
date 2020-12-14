#include "transport_net.h"

using namespace std;

transport_net::transport_net()
{

}

void transport_net::generate()
{
    for(auto &i:pipes){
        i.second.connected = 0;
    }

    strok_stolb.clear();
    m_smezhn.clear();
    order.clear();

    if(KS_es.size()>0){

        for(auto i : KS_es){
            strok_stolb.insert(i.first);
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

void transport_net::edit()
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

void transport_net::new_pipe()
{
    truba_type temp_truba;
    temp_truba.vvod();
    pipes.emplace(temp_truba.get_id(),temp_truba);
}

void transport_net::new_KS()
{
    KS_type temp_KS;
    temp_KS.vvod();
    KS_es.emplace(temp_KS.get_id(), temp_KS);

    if(m_smezhn.size()!=0){
        strok_stolb.insert(temp_KS.get_id());
        for(auto i:strok_stolb){
            m_smezhn.emplace(make_pair(temp_KS.get_id(),i),-1);
            if(i!=temp_KS.get_id()) m_smezhn.emplace(make_pair(i,temp_KS.get_id()),-1);
        }
    }
}

void transport_net::vivod_of_objects()
{
    if (pipes.size() > 0) {
        for (auto i : pipes) {
            cout<<i.second;
        }
    }
    else {
        cout << "��� �� ������ ������� ��������� ����� " << endl;
    }

    if (pipes.size() > 0) {
        for (auto i : KS_es) {
            cout<<i.second;
        }
    }
    else {
        cout << "��� �� ������ ������� ��������� �� " << endl;
    }
}

void transport_net::delete_pipe()
{
    double id_selection;
    id_presence(pipes,id_selection);

    if(pipes[id_selection].connected){
        for(auto& i:m_smezhn){
            if(i.second==id_selection){
                i.second = -1;
            }
        }
    }

    pipes.erase(int(id_selection));

    if(order.size()>0){
        order.clear();
    }

    cout<<"����� "<<id_selection<<" ������� ������� "<<endl;
}

void transport_net::delete_KS()
{
    double id_selection;
    id_presence(KS_es,id_selection);

    for(auto& i: strok_stolb){

        if(m_smezhn[make_pair(id_selection,i)] !=-1){
            pipes[m_smezhn[make_pair(id_selection,i)]].connected = false;
            m_smezhn.erase(make_pair(id_selection,i));
        }

        if(m_smezhn[make_pair(i,id_selection)] !=-1){
            pipes[m_smezhn[make_pair(i,id_selection)]].connected = false;
            m_smezhn.erase(make_pair(i,id_selection));
        }

    }

    strok_stolb.erase(id_selection);
    KS_es.erase(id_selection);

    if(order.size()>0){
        order.clear();
    }

    cout<<"�� "<<id_selection<<" ������� ������� "<<endl;



}

void transport_net::save_all()
{
    ofstream fout;
    string filename;

    input_and_check(filename, "�������� �����");

    //���������� � ����
    fout.open(filename + ".clbr");

    if (fout.is_open()) {

        for (auto i : pipes) {
            fout<<i.second;
        }

        for (auto i : KS_es) {
            fout<<i.second;
        }

        fout<<"m"<<endl;
        if(m_smezhn.size()>0){
            fout<<"y"<<endl;
            for(auto i: strok_stolb){
                for(auto j:strok_stolb){
                    fout<<m_smezhn[make_pair(i,j)]<<"|";
                }
                fout<<endl;
            }
        }
        else{
            fout<<"n"<<endl;
        }
    }
    else {
        cout << "�� ������� �������/������� ���� ��� ����������";
    }

    fout.close();
}

void transport_net::load_all()
{
    ifstream fin;//�������� ������ ������ �� �����
    string filename;

    input_and_check(filename, "�������� �����");

    //���������� ���� � ����
    fin.open(filename + ".clbr");

    if (fin.is_open() == false) {
        cout << "�� ������� ������� ���� ���� ��� ��������" << endl;
        return;
    }

    pipes.clear();
    KS_es.clear();
    m_smezhn.clear();
    order.clear();

    string load_string;
    int max_KS_id = 0;
    int max_pipe_id = 0;

    while (std::getline(fin, load_string)) {

        if (load_string[0] == 't') {
            truba_type temp_truba;
            temp_truba.load(load_string);
            if (temp_truba.get_id() > max_pipe_id) max_pipe_id = temp_truba.get_id();
            pipes.emplace(temp_truba.get_id(), temp_truba);
        }
        else if(load_string[0] == 'k'){
            KS_type temp_KS;
            temp_KS.load(load_string);
            if (temp_KS.get_id() > max_KS_id) max_KS_id = temp_KS.get_id();
            KS_es.emplace(temp_KS.get_id(), temp_KS);
        }
        else if(load_string[0] == 'm'){
            std::getline(fin, load_string);
            if(load_string[0] == 'y'){
                for(auto i : KS_es){
                    strok_stolb.insert(i.first);
                    std::getline(fin, load_string);
                    string temp_string = "";
                    int schet = 0;
                    for(auto j: KS_es){
                        while(load_string[schet]!='|'){
                            temp_string += load_string[schet];
                            schet++;
                        }
                        m_smezhn.emplace(make_pair(i.first,j.first),stoi(temp_string));
                        schet++;
                        temp_string = "";
                    }
                }
                cout<<"������������ ���� ������� ���������"<<endl;
            }
        }
    }

    fin.close();
}

void transport_net::find_way()
{
    if(m_smezhn.size() == 0){
        cout<<"������������ ���� �� ������, ���������� ����������� ���� ���������� "<<endl;
    }
    else{
        double begin_id, end_id;
        int min_way;

        cout<<"������� �� ������ "<<endl;
        id_presence(KS_es, begin_id,false);

        cout<<"������� �� ����� "<<endl;
        id_presence(KS_es, end_id,false);
        int stage = 0;
        stack<int> to_watch;
        set<int> next_to_watch;
        to_watch.push(-1);


        //��������
        while(true){
            if(to_watch.top() == -1){
                for(auto i:strok_stolb){
                    if(i!= begin_id){
                        deykstra_matrix.emplace(make_pair(stage, i),
                                                make_pair(numeric_limits<double>::infinity(), false));
                        deykstra_matrix.emplace(make_pair(stage+1, i),
                                                make_pair(numeric_limits<double>::infinity(), false));
                    }
                    else{
                        deykstra_matrix.emplace(make_pair(stage, i),
                                                make_pair(0, true));
                        deykstra_matrix.emplace(make_pair(stage+1, i),
                                                make_pair(0, true));
                    }
                }

                to_watch.pop();
                to_watch.push(begin_id);
                stage++;
            }
            else{
                while(!to_watch.empty()){
                    for(auto i:m_smezhn){
                        if(i.first.first == to_watch.top()){
                            if(i.second!=-1){
                                if(deykstra_matrix[make_pair(stage, i.first.second)].second == false){
                                    next_to_watch.insert(i.first.second);
                                }
                                if(deykstra_matrix[make_pair(stage, i.first.second)].first>
                                        (pipes[i.second].length + deykstra_matrix[make_pair(stage, to_watch.top())].first)
                                        && deykstra_matrix[make_pair(stage, i.first.second)].second == false){
                                    deykstra_matrix[make_pair(stage, i.first.second)].first = pipes[i.second].length+
                                            deykstra_matrix[make_pair(stage, to_watch.top())].first;
                                }
                                deykstra_matrix.emplace(make_pair(stage+1, i.first.second),
                                                        deykstra_matrix[make_pair(stage, i.first.second)]);
                            }
                            else{
                                deykstra_matrix.emplace(make_pair(stage+1, i.first.second),
                                                        deykstra_matrix[make_pair(stage, i.first.second)]);
                            }
                        }
                    }
                    to_watch.pop();
                }
                double min = numeric_limits<double>::infinity();
                int min_key;
                for(auto &i:deykstra_matrix){
                    if(i.first.first == stage && i.second.second == false && i.second.first<min){
                        min = i.second.first;
                        min_key = i.first.second;
                    }
                }
                deykstra_matrix[make_pair(stage,min_key)].second=true;
                deykstra_matrix[make_pair(stage+1,min_key)].second=true;
                for(auto i:next_to_watch){
                    to_watch.push(i);
                }
                next_to_watch.clear();

                for(auto &i:deykstra_matrix){

                    if(i.first.first == stage && i.first.second == end_id && i.second.second == true){
                        min_way = i.second.first;
                        cout<<"���������� ���� �� �� "<<begin_id<<" �� �� "<<end_id
                           <<" ���������� "<<min_way<<endl;

                        cout<<"������� ��������� :"<<endl;
                        for(auto i : strok_stolb)
                        {
                            cout<<"\t"<<i;
                        }
                        cout<<endl;

                        for(int i = 0; i<=stage; i++)
                        {
                            cout<<i;
                            for(auto j : strok_stolb)
                            {
                                cout<<"\t"<<deykstra_matrix[make_pair(i,j)].first;
                                if(deykstra_matrix[make_pair(i,j)].second==true) cout<<"p";
                            }
                            cout<<endl;
                        }
                        deykstra_matrix.clear();
                        return;
                    }
                }

                bool infinity_cycle = true;
                for(auto i:strok_stolb){
                    if(deykstra_matrix[make_pair(stage,i)].first != deykstra_matrix[make_pair(stage-1,i)].first
                            ||deykstra_matrix[make_pair(stage,i)].second != deykstra_matrix[make_pair(stage-1,i)].second ){
                        infinity_cycle = false;
                    }
                }

                if(infinity_cycle == true){
                    cout<<"��� ��������� ���� ������ ������ �� ��������� �� ������"<<endl;
                    deykstra_matrix.clear();
                    return;
                }
                stage++;
            }
        }
    }
}

void transport_net::max_potok()
{
    if(m_smezhn.size() == 0){
        cout<<"������������ ���� �� ������, ���������� ������������� ������ �� �������� "<<endl;
    }
    else{
        double begin_id, end_id;

        cout<<"������� �� ������ "<<endl;
        id_presence(KS_es, begin_id,false);

        cout<<"������� �� ����� "<<endl;
        id_presence(KS_es, end_id,false);

        while(true){
            floyd_matrix.clear();
            for(auto &i:pipes){
                i.second.current_potok = 0;
            }
            set<int> to_watch;

            //���������� ������ (��� 1)
            floyd_matrix.emplace(begin_id, node(true,begin_id,numeric_limits<double>::infinity(),grey));
            to_watch.insert(begin_id);

            //������ ��� (��� 2)
            while(true){
                auto current_iterator = to_watch.begin();
                for(auto i:strok_stolb){

                    //���������
                    if(m_smezhn[make_pair(*current_iterator,i)] != -1 && !(floyd_matrix.find(i) != floyd_matrix.end())){
                        if(pipes[m_smezhn[make_pair(*current_iterator,i)]].current_potok
                                != pipes[m_smezhn[make_pair(*current_iterator,i)]].prop_sbosobn){

                            floyd_matrix.emplace(i, node(true,*current_iterator,
                                                         min(floyd_matrix[*current_iterator].potok,
                                                         pipes[m_smezhn[make_pair(*current_iterator,i)]].prop_sbosobn -
                                    pipes[m_smezhn[make_pair(*current_iterator,i)]].current_potok),grey));
                            to_watch.insert(i);

                        }
                    }
                    //��������
                    if(m_smezhn[make_pair(i,*current_iterator)] != -1
                            && !(floyd_matrix.find(i) != floyd_matrix.end())
                            && pipes[m_smezhn[make_pair(i,*current_iterator)]].current_potok!=0){

                        floyd_matrix.emplace(i, node(false,*current_iterator,
                                                     min(floyd_matrix[*current_iterator].potok,
                                                     pipes[m_smezhn[make_pair(*current_iterator,i)]].current_potok),grey));
                        to_watch.insert(i);
                    }
                }

                floyd_matrix[*current_iterator].colour=black;
                to_watch.erase(*current_iterator);

                if(floyd_matrix.find(end_id) != floyd_matrix.end()){
                    break;
                }

                if(to_watch.empty()){
                    int mpt = 0;
                    for(auto i:pipes){
                        if(i.second.prop_sbosobn == i.second.current_potok){
                            mpt+=i.second.prop_sbosobn;
                        }
                    }
                    if(mpt==0){
                        cout<<"������������ ����� ����� ����(������ ����� �� �� �������)"<<endl;
                    }
                    else{
                        cout<<"������������ ����� ����� ������� �� ����� "<< mpt <<endl;
                    }

                    return;
                }
            }

            //�������� ��� (���� 4 � 5)
            int potok_change=floyd_matrix[end_id].potok;
            int current_ks = end_id;
            while(true){
                if(floyd_matrix[current_ks].znak==true){
                    pipes[m_smezhn[make_pair(floyd_matrix[current_ks].prev,current_ks)]].current_potok+=potok_change;
                }
                else{
                    pipes[m_smezhn[make_pair(current_ks,floyd_matrix[current_ks].prev)]].current_potok-=potok_change;
                }
                current_ks = floyd_matrix[current_ks].prev;
                if(current_ks == begin_id){
                    break;
                }
            }
        }
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







