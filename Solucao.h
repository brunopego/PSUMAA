#ifndef PSUMAA_SOLUCAO_H
#define PSUMAA_SOLUCAO_H


#include "Job.h"
#include "Problema.h"
#include <vector>
#include <deque>

using namespace std;

class Solucao {

private:
    vector<Job> jobs; // vetor com os dados de cada tarefa do problema
    Problema *prob; // referencia para o problema
    //int qtd_tarefas; // quantidade de jobs/tarefas

public:
    Solucao(Problema* prob);

    vector<Job> &getJobs();

    int getCusto() const;

    int getAntecipacao(const Job& job) const;

    int getAtraso(const Job& job) const;

    // Metodo guloso Data de Entrega mais Próxima - EDD (Earliest Due Date)
    void eddGuloso();

    // Metodo parcialmente guloso Data de Entrega mais Próxima - EDD (Earliest Due Date)
    void ordena(float alfa, int tipo);

    // Metodo guloso Data de Entrega mais Distante - TDD (Tardiest Due Date)
    void tddGuloso();

    // Metodo guloso Menor Tempo de Processamento - SPT (Shortest Processing Time)
    void sptGuloso();

    void imprimeSolucao();

    bool operator==(const Solucao&  sol) const;


};


#endif //PSUMAA_SOLUCAO_H
