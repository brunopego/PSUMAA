#include "Solucao.h"
#include "Tarefa.h"
#include "Problema.h"

#include <algorithm>
#include <random>
#include <ctime>
#include <iomanip>

using namespace std;

/*
 * Funcoes gerais
 */

bool edd_funcao(const Job &j, const Job& q) {
    return (j.t->getE() < q.t->getE());
}

bool tdd_funcao(const Job &j, const Job& q) {
    return (j.t->getT() > q.t->getT());
}

bool spt_funcao(const Job &j, const Job& q) {
    return (j.t->getTp() < q.t->getTp());
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

vector<Job> &Solucao::getJobs() {
    return jobs;
}

list <Job> &Solucao::getListaJobs() {
    return lista_jobs;
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

    //cout << "Alfa: " << alfa << endl;
    int tamLista;
    int tamLrc;
    int posicaoAleatoria;
    vector<Job> jobsOrdena; // Vetor auxiliar

    if (tipo == 1) {
        //ordenacao edd
        sort(jobs.begin(), jobs.end(), edd_funcao);
    }
    else if (tipo == 2) {
        //ordenacao tdd
        sort(jobs.begin(), jobs.end(), tdd_funcao);
    }
    else if (tipo == 3) {
        //ordenacao spt
        sort(jobs.begin(), jobs.end(), spt_funcao);
    }
    else {
        //ordenacao aleatoria
        alfa = 1;
    }


    while(!jobs.empty()){
        tamLista  = jobs.size();
        tamLrc =  max(1, (int) (alfa * tamLista));
        //cout << "Tam LRC: " << tamLrc << endl;
        posicaoAleatoria = geraPosicaoAleatoria(tamLrc);
        jobsOrdena.push_back(jobs[posicaoAleatoria]);
        jobs.erase(jobs.begin() + posicaoAleatoria);
    }

    for(auto job : jobsOrdena){
        jobs.push_back(job);
    }

}

void Solucao::imprimeSolucao() {

    cout << left;
    cout << endl;
    cout << "=======================SOLUCAO=======================" << endl << endl;
    cout << "Problema: " << (*prob).getNome_arq() << endl;
    cout << "Numero de Jobs: " << (*prob).getQtd_tarefas() << endl;
    cout << "Custo: " << getCusto() << endl;
    cout << endl;

    cout << setw(6) << "Job"; // id do job
    cout << setw(8) << "TP[i]"; // tempo de processamento
    cout << setw(8) << "S[i][j]"; // tempo de setup
    cout << setw(8) << "H1[i]"; // tempo adiantado
    cout << setw(8) << "C1[i]"; // valor da penalidade por antecipacao
    cout << setw(8) << "H2[i]"; // tempo atrasado
    cout << setw(8) << "C2[i]"; // valor da penalidade por atraso
    cout << endl;

    for (int i = 0; i < jobs.size(); i++){
        cout << setw(6) << jobs[i].getId();
        cout << setw(8) << jobs[i].t->getTp();
        if (i != jobs.size()-1){
            cout << setw(8) << (*prob).getTempoSetup(jobs[i].getId(), jobs[i+1].getId());
        } else{
            cout << setw(8) << 0;
        }
        cout << setw(8) << getAntecipacao(jobs[i]);
        cout << setw(8) << jobs[i].t->getAlfa() * getAntecipacao(jobs[i]);
        cout << setw(8) << getAtraso(jobs[i]);
        cout << setw(8) << jobs[i].t->getBeta() * getAtraso(jobs[i]);
        cout << endl;
    }

    cout << endl;
    cout << "=====================================================" << endl;

}

bool Solucao::operator==(const Solucao &sol) const {
    if (sol.jobs.size() != this->jobs.size()) return false;
    for(unsigned int i = 0; i < sol.jobs.size(); i++)
        if(sol.jobs[i] != this->jobs[i])
            return false;
    return true;
}



