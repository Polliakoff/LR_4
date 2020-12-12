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

        cout<<"Транспортная сеть успешно создана (-1 = нету свзяи, любое другое число = id соединяющей трубы)"<<endl;
        vivod(false);
    }

    else{
        cout<<"Нету КС "<<endl;
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
                cout<<"Хотите ли вы редактировать транспортную сеть (y/n)?"<<endl;
                cin>>selection;
                if(selection == "y"){
                    cout<<"Введите два id КС: "<<endl;

                    cout<<"Id КС - начала: "<<endl;
                    id_presence(KS_es,id_begin, false);

                    cout<<"Id КС - конца: "<<endl;
                    id_presence(KS_es,id_end, false);

                    cout<<"Вы хотите соединить КС трубой или разорвать связь между ними ?"<<
                          endl<<"1 - соединить 2- разорвать"<<endl;
                    while(true){
                        cin>>selection_1;
                        if(selection_1 == "1")
                        {
                            cout<<"Введите id трубы, соединяющей КС : "<<endl;
                            while(true){
                                cout<<"Доступные трубы: "<<endl;
                                for(auto i:pipes){
                                    if(i.second.connected == 0){
                                        cout<<i.second;
                                        are_there_any = true;
                                    }
                                }
                                if(are_there_any == false){
                                    cout<<"Нет доступных труб, добавление связи невозможно "<<endl;
                                    return;
                                }
                                cout<<endl;
                                id_presence(pipes, pipe_id, false);
                                if(pipes[int(pipe_id)].connected == 0){
                                    pipes[int(pipe_id)].connected=1;
                                    break;
                                }
                                else{
                                    cout<<"Вы ввели Id уже присоединенной трубы";
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
                                cout<<"Данные КС уже не связаны"<<endl;
                            }
                            else {
                                pipes[m_smezhn[make_pair(id_begin, id_end)]].connected = 0;
                                m_smezhn[make_pair(id_begin, id_end)] = -1;
                            }
                            break;
                        }
                        else{
                            cout<<"Введите 1 или 2";
                        }
                    }
                    break;
                }
                else if(selection == "n"){
                    return;
                }
                else{
                    cout<<"Введите y или n строчными буквами"<<endl;
                }
            }
        }
    }
    else{
        cout<<"Транспортная сеть не создана"<<endl;
    }
}

void transport_net::vivod(bool output)
{   
    if(m_smezhn.size()>0){
        if (output) cout<<"Транспортная сеть на данный момент (-1 = нету свзяи, любое другое число = id соединяющей трубы)"
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
        cout<<"Транспортная сеть не создана"<<endl;
    }

    if(order.size()>0){
        cout<<"Номера вершин по топологической сортировке (номер - вершина): "<<endl;
        for(auto i:order){
            cout<<i.first<<"\t"<<i.second<<endl;
        }
    }
    else{
        cout<<"Сеть не отсортирована "<<endl;
    }
}

void transport_net::sort()
{
    if(m_smezhn.size()>0){

        // 0 - белый 1 - серый 2 - черный
        //покрасим все вершины в белый
        colour.clear();
        for(auto i : strok_stolb)
        {
            colour.emplace(i,0);
        }

        //Найдем корень, отсутствие корня приводит к циклу
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
            cout<<"В сети есть цикл, топологическая сортировка не возможна"<<endl;
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
                cout<<"Отсортированные КС: "<<endl;
                for(auto i:order){
                    cout<<i.first<<"\t"<<i.second<<endl;
                }
            }
        }
    }
    else{
        cout<<"Транспортная сеть не создана"<<endl;
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
        cout << "Нет ни одного объекта категории трубы " << endl;
    }

    if (pipes.size() > 0) {
        for (auto i : KS_es) {
            cout<<i.second;
        }
    }
    else {
        cout << "Нет ни одного объекта категории КС " << endl;
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

    cout<<"Труба "<<id_selection<<" успешно удалена "<<endl;
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

    cout<<"КС "<<id_selection<<" успешно удалена "<<endl;



}

void transport_net::save_all()
{
    ofstream fout;
    string filename;

    input_and_check(filename, "название Файла");

    //сохранение в файл
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
        cout << "Не удалось открыть/создать файл для сохранения";
    }

    fout.close();
}

void transport_net::load_all()
{
    ifstream fin;//создание потока вывода из файла
    string filename;

    input_and_check(filename, "название Файла");

    //сохранение труб в файл
    fin.open(filename + ".clbr");

    if (fin.is_open() == false) {
        cout << "Не удалось открыть этот файл для загрузки" << endl;
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
                cout<<"Транспортная сеть успешно загружена"<<endl;
            }
        }
    }

    fin.close();
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
                cout<<"В сети есть цикл, топологическая сортировка не возможна"<<endl;
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







