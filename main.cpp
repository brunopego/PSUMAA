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

    //Problema p("instancias/dados/INST0703.dat");
    //Problema p("instancias/dados/INST7501.dat");
    Problema p("instancias/dados/INST1001.dat");

    Populacao pop(300,0,1,&p);
    //pop.imprimePopulacao();

    return 0;
}