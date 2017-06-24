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

int geraPosicaoAleatoria(int min, int max){
    return rand() % (max - min + 1) + min;
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

int Solucao::calculaCusto() {
    int total = 0;
    for(auto job : lista_jobs){
        int job_alfa = job.t->getAlfa();
        int job_beta = job.t->getBeta();
        int job_antecipacao = getAntecipacao(job);
        int job_atraso = getAtraso(job);
        total += (job_alfa * job_antecipacao) + (job_beta * job_atraso);
    }
    this->custo = total;
    return total;
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
    //vector<Job> jobsOrdena; // Vetor auxiliar

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
        tamLista  = (int) jobs.size();
        tamLrc =  max(1, (int) (alfa * tamLista));
        //cout << "Tam LRC: " << tamLrc << endl;
        posicaoAleatoria = geraPosicaoAleatoria(tamLrc);
        lista_jobs.push_back(jobs[posicaoAleatoria]);
        jobs.erase(jobs.begin() + posicaoAleatoria);
    }

    for(auto job : lista_jobs){
        jobs.push_back(job);
    }

}
/*
void Solucao::imprimeSolucao() {

    cout << left;
    cout << endl;
    cout << "=======================SOLUCAO=======================" << endl << endl;
    cout << "Problema: " << (*prob).getNome_arq() << endl;
    cout << "Numero de Jobs: " << (*prob).getQtd_tarefas() << endl;
    cout << "Custo: " << calculaCusto() << endl;
    cout << endl;

    cout << setw(6) << "Job"; // id do job
    cout << setw(8) << "TP[i]"; // tempo de processamento
    cout << setw(8) << "S[i][j]"; // tempo de setup
    cout << setw(8) << "H1[i]"; // tempo adiantado
    cout << setw(8) << "C1[i]"; // valor da penalidade por antecipacao
    cout << setw(8) << "H2[i]"; // tempo atrasado
    cout << setw(8) << "C2[i]"; // valor da penalidade por atraso
    cout << endl;

    atualizaVetor();

    for (int i = 0; i < jobs.size(); i++){
        cout << setw(6) << jobs[i].getId();
        cout << setw(8) << jobs[i].t->getTp();
        if (i != jobs.size() - 1) {
            cout << setw(8) << (*prob).getTempoSetup(jobs[i].getId(), jobs[i+1].getId());
        } else {
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
*/

void Solucao::imprimeSolucao() {

    list<Job>::iterator it;

    cout << left;
    cout << endl;
    cout << "=======================SOLUCAO=======================" << endl << endl;
    cout << "Problema: " << (*prob).getNome_arq() << endl;
    cout << "Numero de Jobs: " << (*prob).getQtd_tarefas() << endl;
    cout << "Custo: " << calculaCusto() << endl;
    cout << endl;

    cout << setw(6) << "Job"; // id do job
    cout << setw(8) << "TP[i]"; // tempo de processamento
    cout << setw(8) << "S[i][j]"; // tempo de setup
    cout << setw(8) << "H1[i]"; // tempo adiantado
    cout << setw(8) << "C1[i]"; // valor da penalidade por antecipacao
    cout << setw(8) << "H2[i]"; // tempo atrasado
    cout << setw(8) << "C2[i]"; // valor da penalidade por atraso
    cout << endl;

    for (it = lista_jobs.begin(); it != lista_jobs.end(); it++){
        cout << setw(6) << (*it).getId();
        cout << setw(8) << (*it).t->getTp();
        if ((*it).getId() != lista_jobs.back().getId()) {
            cout << setw(8) << (*prob).getTempoSetup((*it).getId(), (*(it++)).getId());
            it--;
        } else {
            cout << setw(8) << 0;
        }
        cout << setw(8) << getAntecipacao((*it));
        cout << setw(8) << (*it).t->getAlfa() * getAntecipacao((*it));
        cout << setw(8) << getAtraso((*it));
        cout << setw(8) << (*it).t->getBeta() * getAtraso((*it));
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

void Solucao::gerarLinhaDoTempo() {

    atualizaVetor();
    int tempo_inicio = 0;

    for(int i = 0; i< jobs.size(); i++){
        jobs[i].setInicio(tempo_inicio);
        if (i != jobs.size() - 1) {
            tempo_inicio += jobs[i].t->getTp() + (*prob).getTempoSetup(jobs[i].getId(), jobs[i+1].getId()) + 1;
        }
    }

    lista_jobs.clear();
    for(auto job : jobs){
        lista_jobs.push_back(job);
    }

    calculaCusto();

}

void Solucao::atualizaVetor() {
    // limpa o vetor e preenche novamente atualizado, pois a lista_jobs pode ter sofrido alteracoes
    jobs.clear();
    for(auto job : lista_jobs){
        jobs.push_back(job);
    }
}

int Solucao::getCusto() const {
    return this->custo;
}

void Solucao::fazerMutacao(int tipo) {

    /*
     * Tipo 1: mover u depois de v
     * Tipo 2: mover (u,x) depois de v
     * Tipo 3: mover (x,u) depois de v
     * Tipo 4: trocar u com v
     * Tipo 5: trocar (u,x) com v
     * Tipo 6: trocar (u,x) com (v,y)
     */

    int m, n; // numero aleatorio
    list<Job>::iterator u,v; // iteradores auxiliares
    list<Job>::iterator x,y; // iterado auxiliar que vem antes ou depois de u

    if(tipo == 1){

        do {
            m = geraPosicaoAleatoria((int) lista_jobs.size());
            n = geraPosicaoAleatoria((int) lista_jobs.size());
        } while(m == n);

        u = lista_jobs.begin();
        v = lista_jobs.begin();
        advance(u, m);
        advance(v, n + 1);
        lista_jobs.splice(v, lista_jobs, u);


    } else if(tipo == 2){

        do {
            m = geraPosicaoAleatoria((int) lista_jobs.size() - 1);
            n = geraPosicaoAleatoria((int) lista_jobs.size());
        } while(m == n || m == n + 1);

        u = lista_jobs.begin();
        v = lista_jobs.begin();
        x = lista_jobs.begin();
        advance(u, m);
        advance(x, m + 2); // intervalo aberto
        advance(v, n + 1);
        lista_jobs.splice(v, lista_jobs, u, x);

    } else if(tipo == 3){

        do {
            m = geraPosicaoAleatoria((int) lista_jobs.size());
            if(m == 0) m = 1;
            n = geraPosicaoAleatoria((int) lista_jobs.size());
        } while(m == n || m == n - 1);

        u = lista_jobs.begin();
        v = lista_jobs.begin();
        x = lista_jobs.begin();

        advance(u, m);
        advance(x, m - 1);
        swap(*x, *u);

        u = lista_jobs.begin();
        x = lista_jobs.begin();
        advance(u, m + 1); // intervalo aberto
        advance(x, m - 1);
        advance(v, n + 1);
        lista_jobs.splice(v, lista_jobs, x, u);

    } else if(tipo == 4){

        do {
            m = geraPosicaoAleatoria((int) lista_jobs.size());
            n = geraPosicaoAleatoria((int) lista_jobs.size());
        } while(m == n);

        u = lista_jobs.begin();
        v = lista_jobs.begin();
        advance(u, m);
        advance(v, n);
        swap(*u, *v);

    } else if(tipo == 5){

        do {
            m = geraPosicaoAleatoria((int) lista_jobs.size() - 1);
            n = geraPosicaoAleatoria((int) lista_jobs.size());
        } while(m == n || m == n + 1);

        u = lista_jobs.begin();
        v = lista_jobs.begin();
        x = lista_jobs.begin();
        advance(u, m);
        advance(x, m + 1);
        advance(v, n);
        swap(*u, *v);
        u = lista_jobs.begin();
        advance(u, n + 1);
        lista_jobs.splice(u, lista_jobs, x);

    } else {

        do {
            m = geraPosicaoAleatoria((int) lista_jobs.size() - 1);
            n = geraPosicaoAleatoria((int) lista_jobs.size() - 1);
        } while(m == n || m == n + 1);

        u = lista_jobs.begin();
        v = lista_jobs.begin();
        x = lista_jobs.begin();
        y = lista_jobs.begin();
        advance(u, m);
        advance(x, m + 1);
        advance(v, n);
        advance(y, n + 1);
        swap(*u, *v);
        swap(*x, *y);

    }


}



