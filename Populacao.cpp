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

bool ordernaPorCusto(const Solucao& a, const Solucao& b){
    return (a.getCusto() < b.getCusto());
}

int geraTipoMutacao(int num){
    return (rand() % num) + 1;
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
    // adiciona um individuo construido de forma gulosa
    Solucao s(prob);
    s.ordena(0, tipo);
    s.gerarLinhaDoTempo();
    populacao_set.insert(s);

    while(i < (lambda-1)){
        Solucao sol(prob);
        sol.ordena(gerarAlfa(), tipo);
        par = populacao_set.insert(sol);
        if(par.second) i++;
    }

    for(auto sol : populacao_set){
        sol.gerarLinhaDoTempo();
        populacao.push_back(sol);
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

void Populacao::insereIndividuo(Solucao &solucao) {

    // TODO: Corrigir essa funcao para inserir na lista populacao
    pair<unordered_set<Solucao, HashSolucao>::iterator,bool> p;
    p = populacao_set.insert(solucao);
    if(!p.second) cout << "O individuo ja esta nesta populacao";

}

list <Solucao> &Populacao::getPopulacao() {
    return populacao;
}

void Populacao::ordernarPopulacao() {
    populacao.sort(ordernaPorCusto);
}

void Populacao::estrategiaEvolutiva() {

    int qtd_filhos = lambda/mi;
    int tipo_mutacao;
    list<Solucao> aux; // vetor auxiliar de populacao


    for(int i = 0; i < 3; i++){

        for(auto individuo: populacao){
            for(int i = 0; i < qtd_filhos; i++){
                tipo_mutacao = geraTipoMutacao(6);
                //cout << "Tipo de mutação: " << tipo_mutacao << endl;
                Solucao s(prob);
                s = individuo;
                s.fazerMutacao(tipo_mutacao);
                s.gerarLinhaDoTempo();
                aux.push_back(s);
            }
        }

        populacao.splice(populacao.end(), aux);
        ordernarPopulacao();
        //populacao.resize(10);
    }



}
