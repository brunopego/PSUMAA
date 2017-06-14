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
    Problema p("instancias/dados/INST1001.dat");

    //Populacao pop(100,0,1,&p);
    //pop.imprimePopulacao();

    Solucao s(&p);
    s.ordena(0.16,1);
    s.gerarLinhaDoTempo();
    s.imprimeSolucao();

    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duracao = duration_cast<milliseconds>( t2 - t1 ).count();
    cout << duracao << " milisegundos" << endl;
    return 0;
}