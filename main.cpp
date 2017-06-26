#include <iostream>
#include <random>
#include <ctime>
#include <chrono>

#include "Problema.h"
#include "Solucao.h"
#include "Populacao.h"


using namespace std;
using namespace std::chrono;

int main() {

    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    // Alfa =  0 -> Guloso, 1 -> totalmente aleatorio

    // semente para a funcao rand() para gerar um valor aleatorio
    srand(time(NULL));

    //Problema p("instancias/dados/INST0703.dat");
    //Problema p("instancias/dados/INST7501.dat");
    Problema p("instancias/dados/INST5001.dat");
    //Problema p("instancias/dados/INST2002.dat");
    //Problema p("instancias/dados/INST2004.dat");
    //Problema p("instancias/dados/INST1001.dat");

    Populacao pop(4,100,1,&p);
    pop.estrategiaEvolutiva();
    //cout << "Tamanho da populacao: " << pop.getPopulacao().size() << endl;

    //pop.ordernarPopulacao();

    cout << endl;
    /*
    for(auto sol : pop.getPopulacao()){
        cout << "Custo: " << sol.getCusto() << endl;
    }
    */
    //cout << "Custo: " << pop.getPopulacao().front().getCusto() << endl;
    //cout << "Tamanho da populacao: " << pop.getPopulacao().size() << endl;
    pop.getPopulacao().front().imprimeSolucao();
    //pop.imprimePopulacao();


    /*
    Solucao s(&p);
    s.ordena(0,1);
    s.gerarLinhaDoTempo();

    // muta um individuo 100x
    for(int i = 1; i < 101; i++){
        cout << "i -> " << i << endl;
        s.fazerMutacao(6);
    }

    s.gerarLinhaDoTempo();
    s.imprimeSolucao();
    */


    /*
    for(auto job : s.getListaJobs()){
        cout << "id: " << job.getId() << " tempo de inicio: " << job.getInicio() << endl;
    }
    */




    cout << endl;
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duracao = duration_cast<milliseconds>( t2 - t1 ).count();
    cout << duracao << " milisegundos" << endl;
    return 0;
}