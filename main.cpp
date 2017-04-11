#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "Tarefa.h"
#include "Problema.h"

using namespace std;

int main() {

    string nome_arq = "instancias/dados/INST0703.dat";
    Problema p(nome_arq);

    //cout << p.getTempoSetup(p.getTarefas().at(0).getId(), p.getTarefas().at(1).getId()) << endl;


    p.getTarefas().at(0).setInicio(108);
    p.getTarefas().at(1).setInicio(284);
    p.getTarefas().at(2).setInicio(97);
    p.getTarefas().at(3).setInicio(188);
    p.getTarefas().at(4).setInicio(267);
    p.getTarefas().at(5).setInicio(13);
    p.getTarefas().at(6).setInicio(198);

    cout << "Custo Total: " << p.getCusto() << endl;

    /*
    for(auto &tarefa : p.getTarefas()){
        cout << "-------------------------------------" << endl;
        cout << "ID: " << tarefa.getId() << endl;
        cout << "ALFA: " << tarefa.getAlfa() << endl;
        cout << "BETA: " << tarefa.getBeta() << endl;
    }
     */


    // ----------------------------------------------------------

    return 0;
}