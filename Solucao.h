#ifndef PSUMAA_SOLUCAO_H
#define PSUMAA_SOLUCAO_H


#include "Job.h"
#include "Problema.h"
#include <vector>
#include <list>

using namespace std;

class Solucao {

private:
    vector<Job> jobs; // vetor com os dados de cada tarefa do problema
    list<Job> lista_jobs; // lista com os dados do problema apos ordenacao
    Problema *prob; // referencia para o problema
    int custo = 0; // custo da solucao, calculado apos a linha do tempo ser gerada
    //int qtd_tarefas; // quantidade de jobs/tarefas

public:
    Solucao(Problema* prob);

    vector<Job> &getJobs();

    list<Job> &getListaJobs();

    int calculaCusto();

    int getAntecipacao(const Job& job) const;

    int getAtraso(const Job& job) const;

    void ordena(float alfa, int tipo);

    void imprimeSolucao();

    bool operator==(const Solucao&  sol) const;

    void gerarLinhaDoTempo();

    void atualizaVetor();

    int getCusto() const;

    void fazerMutacao(int tipo);

};


#endif //PSUMAA_SOLUCAO_H
