#include <iostream>
#include <random>
#include <ctime>

#include "Problema.h"
#include "Solucao.h"
#include "Populacao.h"


using namespace std;
/*
float gerarAlfa(){
    // gera numero aleatorio entre 0 e 1
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0,1);
    return (float) dis(gen);
}
 */

int main() {

    // semente para a funcao rand() para gerar um valor aleatorio
    srand(time(NULL));

    //string nome_arq = "instancias/dados/INST0703.dat";
    //string nome_arq = "instancias/dados/INST1001.dat";

    //Problema p("instancias/dados/INST0703.dat");
    //Problema p("instancias/dados/INST7501.dat");
    Problema p("instancias/dados/INST1001.dat");
    //Solucao sol_p(&p);

    /*
    //INST0703.dat custo .sol = 2117
    sol_p.getJobs().at(0).setInicio(108);
    sol_p.getJobs().at(1).setInicio(284);
    sol_p.getJobs().at(2).setInicio(97);
    sol_p.getJobs().at(3).setInicio(188);
    sol_p.getJobs().at(4).setInicio(267);
    sol_p.getJobs().at(5).setInicio(13);
    sol_p.getJobs().at(6).setInicio(198);
    */

    //sol_p.edd_ordena();
    //cout << "Custo Total (edd) : " << sol_p.getCusto() << endl;

    //sol_p.tdd_ordena();
    //cout << "Custo Total (tdd) : " << sol_p.getCusto() << endl;
    //sol_p.spt_ordena();
    //cout << "Custo Total (spt) : " << sol_p.getCusto() << endl;
/*
    Problema q("instancias/dados/INST1001.dat");
    Solucao sol_q(&q);

    //sol_q.edd_ordena();
    sol_p.tdd_ordena();
    //sol_p.spt_ordena();
    //cout << "Custo Total (edd) : " << sol_q.getCusto() << endl;

    for(auto job : sol_p.getJobs()){
        cout << job.getId() << endl;
    }
*/
    //sol_q.tdd_ordena();
    //cout << "Custo Total (tdd) : " << sol_q.getCusto() << endl;
    //sol_p.spt_ordena();
    //cout << "Custo Total (spt) : " << sol_p.getCusto() << endl;

/*
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
*/

    //cout << "Custo Total (p) : " << sol_p.getCusto() << endl;
    //cout << "Custo Total (q) : " << sol_q.getCusto() << endl;

    /*
    for(auto &tarefa : p.getTarefas()){
        cout << "-------------------------------------" << endl;
        cout << "ID: " << tarefa.getId() << endl;
        cout << "ALFA: " << tarefa.getAlfa() << endl;
        cout << "BETA: " << tarefa.getBeta() << endl;
    }
     */


    // ----------------------------------------------------------

/*
    Problema q("instancias/dados/INST1001.dat");
    Solucao sol(&q);

    float n;

    int tam_lista;
    int tam_lrc;

    tam_lista = q.getQtd_tarefas();



    n = gerarAlfa();

    tam_lrc = max(1, (int) (n * tam_lista));



    cout << "Numero: " << n << endl;
    cout << "Tam Lista: " << tam_lista << endl;
    cout << "Tam LRC: " << tam_lrc << endl;

*/

    //Solucao sol_q(&p);

    //sol_p.ordena(gerarAlfa(), 1);
    //sol_q.ordena(gerarAlfa(), 1);

    //sol_p.ordena(0,1);
    //sol_q.ordena(0,1);

    //Populacao pop;
    //pop.insere(sol_p);
    //pop.insere(sol_q);

    //sol_p.eddGuloso();

    /*
    for(auto job : sol_p.getJobs()){
        cout << job.getId() << endl;
    }
     */

    //sol_p.imprimeSolucao();

    Populacao pop(0,30,1,&p);
    pop.imprimePopulacao();

    return 0;
}