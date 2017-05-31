#include "Solucao.h"
#include "Tarefa.h"
#include "Problema.h"

#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

/*
 * Funcoes gerais
 */

bool edd_funcao(const Job &j, const Job& q) {
    int jEarliness = j.t->getE();
    int qEarliness = q.t->getE();
    return (jEarliness < qEarliness);
}

bool tdd_funcao(const Job &j, const Job& q) {
    int jTardiness = j.t->getT();
    int qTardiness = q.t->getT();
    return (jTardiness > qTardiness);
}

bool spt_funcao(const Job &j, const Job& q) {
    int jTempoProcessamento = j.t->getTp();
    int qTempoProcessamento = q.t->getTp();
    return (jTempoProcessamento < qTempoProcessamento);
}

// gera posicao aleatoria para lista restrita de candidatos (LRC)
int geraPosicaoAleatoria(int tamLrc){
    return rand() % tamLrc;
}

/*
 * Funcoes da Classe
 */

Solucao::Solucao(Problema* prob) {
    this->prob = prob;

    for (int i = 1; i <= prob->getQtd_tarefas() ; ++i) {
        this->jobs.push_back(Job(&(prob->getTarefas()[i-1]), i));
    }
}

deque<Job> &Solucao::getJobs() {
    return jobs;
}

int Solucao::getAntecipacao(const Job& job) const {
    int fim = job.getInicio() + job.t->getTp();
    int e = job.t->getE();
    if(fim < e) {
        return (e - fim);
    }

    return 0;
}

int Solucao::getAtraso(const Job& job) const {
    int fim = job.getInicio() + job.t->getTp();

    int t = job.t->getT();
    if(fim > t) {
        return (fim - t);
    }

    return 0;
}

int Solucao::getCusto() const {
    int total = 0;
    for(auto job : jobs){
        int job_alfa = job.t->getAlfa();
        int job_beta = job.t->getBeta();
        int job_antecipacao = getAntecipacao(job);
        int job_atraso = getAtraso(job);
        total += (job_alfa * job_antecipacao) + (job_beta * job_atraso);
        //std::cout << "job_alfa " << job_alfa << std::endl;
        //std::cout << "job_beta " << job_beta << std::endl;
        //std::cout << "job_antecipacao " << job_antecipacao << std::endl;
        //std::cout << "job_atraso " << job_atraso << std::endl << std::endl;
    }
    return total;
}

void Solucao::eddGuloso() {
    sort(jobs.begin(), jobs.end(), edd_funcao);
    //list.sort(edd_funcao)
}

void Solucao::tddGuloso() {
    sort(jobs.begin(), jobs.end(), tdd_funcao);
}

void Solucao::sptGuloso() {
    sort(jobs.begin(), jobs.end(), spt_funcao);
}

void Solucao::ordena(float alfa, int tipo) {
    /*
     * tipo de ordenacao 1 = EDD
     * tipo de ordenacao 2 = TDD
     * tipo de ordenacao 3 = SPT
     * tipo de ordenacao 4 e > = Aleatoria
     */

    cout << "Alfa: " << alfa << endl;
    int tamLista;
    int tamLrc;
    int posicaoAleatoria;
    vector<Job> jobsOrdena; // Vetor auxiliar

    if (tipo == 1) {
        sort(jobs.begin(), jobs.end(), edd_funcao);
    }
    else if (tipo == 2) {
        sort(jobs.begin(), jobs.end(), tdd_funcao);
    }
    else if (tipo == 3) {
        sort(jobs.begin(), jobs.end(), spt_funcao);
    }
    else {
        alfa = 1;
    }


    while(!jobs.empty()){
        tamLista  = jobs.size();
        tamLrc =  max(1, (int) (alfa * tamLista));
        cout << "Tam LRC: " << tamLrc << endl;
        posicaoAleatoria = geraPosicaoAleatoria(tamLrc);
        jobsOrdena.push_back(jobs[posicaoAleatoria]);
        jobs.erase(jobs.begin() + posicaoAleatoria);
    }

    for(auto job : jobsOrdena){
        jobs.push_back(job);
    }

}

