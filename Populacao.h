#ifndef PSUMAA_POPULACAO_H
#define PSUMAA_POPULACAO_H

#include <vector>
#include <list>
#include <unordered_set>
#include <string>
#include <iostream>
#include <ctime>
#include <chrono>
#include <cstdlib>

#include "Job.h"
#include "Solucao.h"
#include "Problema.h"

using namespace std;

struct HashSolucao {
    std::size_t operator()(Solucao solucao) const {
        std::size_t ret = 0;
        for (auto i : solucao.getJobs())
            ret ^= std::hash<int>()(i.getId());
        return ret;
    }
};


class Populacao {

private:
    unordered_set<Solucao, HashSolucao> populacao_set;
    vector<Solucao> populacao;
    Problema *prob; // referencia para o problema
    int mi; // numero de pais selecionados
    int lambda; // numero de filhos gerados
    /*
     * tipo 1 = edd
     * tipo 2 = tdd
     * tipo 3 = spt
     * tipo >3 = aleatorio
     */
    int tipo; // tipo usado na construcao da solucao

    /*
     * tipo 1 = merms e merm e vnd
     * tipo 2 = merm e vnd
     * tipo 3 = vnd
     */
    int tipoEstrategia;
    int pctgVnd;
    int pctgMut;
    int qtdEvolucao;
    double start; // tempo em que comecou a execucao


public:

    Populacao(int mi, int lambda, int tipo, Problema* prob, int qtdEvolucao, int tipoEstrategia, int pctgVnd, int pctgMut, double start);

    vector<Solucao> &getPopulacao();

    void ordernarPopulacao();

    void imprimePopulacao();

    void estrategiaEvolutivaParalela();

    void estrategiaEvolutiva();

    Solucao merm(Solucao sol);

    Solucao vndPM(Solucao s_atual);

    Solucao ils(Solucao s);


};


#endif //PSUMAA_POPULACAO_H
