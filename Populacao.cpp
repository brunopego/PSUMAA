#include "Populacao.h"
#include <utility>
#include <random>

float gerarAlfa(){
    // gera numero aleatorio entre 0 e 1
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0,1);
    return (float) dis(gen);
}

void Populacao::insere(Solucao &solucao) {

    pair<unordered_set<Solucao, HashSolucao>::iterator,bool> p;
    p = populacao.insert(solucao);
    if(p.second == false) cout << "Nao inseriu";

}

Populacao::Populacao(int mi, int lambda, int tipo, Problema* prob) {

    this->mi = mi; // numero de pais selecionados
    this->lambda = lambda; // numero de filhos gerados
    /*
     * tipo 1 = edd
     * tipo 2 = tdd
     * tipo 3 = spt
     * tipo >3 = aleatorio
     */
    this->tipo = tipo;
    this->prob = prob;

    pair<unordered_set<Solucao, HashSolucao>::iterator,bool> par;

    int i = 0;
    while(i < lambda){
        Solucao sol(prob);
        sol.ordena(gerarAlfa(), tipo);
        par = populacao.insert(sol);
        if(par.second == true) i++;
    }

}

/*
unordered_set &Populacao::getPopulacao() {
    return populacao;
}
 */

void Populacao::imprimePopulacao() {

    for(auto sol : populacao){
        sol.imprimeSolucao();
    }

}
