#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "Tarefa.h"
#include "Problema.h"
#include "Solucao.h"

using namespace std;


int main() {

    //string nome_arq = "instancias/dados/INST0703.dat";
    //string nome_arq = "instancias/dados/INST1001.dat";

    Problema p("instancias/dados/INST0703.dat");
    Solucao sol_p(&p);

    //INST0703.dat custo .sol = 2117
    sol_p.getJobs().at(0).setInicio(108);
    sol_p.getJobs().at(1).setInicio(284);
    sol_p.getJobs().at(2).setInicio(97);
    sol_p.getJobs().at(3).setInicio(188);
    sol_p.getJobs().at(4).setInicio(267);
    sol_p.getJobs().at(5).setInicio(13);
    sol_p.getJobs().at(6).setInicio(198);


    Problema q("instancias/dados/INST1001.dat");
    Solucao sol_q(&q);

    //INST1001.dat custo .sol = 14411
    sol_q.getJobs().at(0).setInicio(10);
    sol_q.getJobs().at(1).setInicio(510);
    sol_q.getJobs().at(2).setInicio(600);
    sol_q.getJobs().at(3).setInicio(101);
    sol_q.getJobs().at(4).setInicio(327);
    sol_q.getJobs().at(5).setInicio(233);
    sol_q.getJobs().at(6).setInicio(691);
    sol_q.getJobs().at(7).setInicio(762);
    sol_q.getJobs().at(8).setInicio(472);
    sol_q.getJobs().at(9).setInicio(366);


    cout << "Custo Total (p) : " << sol_p.getCusto() << endl;
    cout << "Custo Total (q) : " << sol_q.getCusto() << endl;

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