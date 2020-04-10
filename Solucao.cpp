#include "Solucao.h"
#include "Tarefa.h"
#include "Problema.h"

#include <algorithm>
#include <random>
#include <ctime>
#include <iomanip>
#include <cmath>
#include <deque>

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

    /*for (int i = 1; i <= prob->getQtd_tarefas() ; ++i) {
        this->jobs.push_back(Job(&(prob->getTarefas()[i-1]), i));
    }*/

    // no for de cima o id eu coloca o i iterado do laco, portanto se a ordem no arquivo
    // fosse 3,4,1,2.. quando lia o Job que era pra ser id 3 fica como 1 e sucessivamente
    // o for abaixo corrige isso
    for (int i = 1; i <= prob->getQtd_tarefas() ; ++i) {
        this->jobs.push_back(Job(&(prob->getTarefas()[i-1]), prob->getTarefas()[i-1].getId() ));
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

void Solucao::ordena(double alfa, int tipo) {
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

void Solucao::imprimeSolucao() {

    list<Job>::iterator it;

    cout << left;
    cout << endl;
    cout << "==========================SOLUCAO==========================" << endl << endl;
    cout << "Problema: " << (*prob).getNome_arq() << endl;
    cout << "Numero de Jobs: " << (*prob).getQtd_tarefas() << endl;
    cout << "Custo: " << calculaCusto() << endl;
    cout << endl;

    cout << setw(6) << "Job"; // id do job
    cout << setw(8) << "TI[i]"; // tempo de inicio
    cout << setw(8) << "TP[i]"; // tempo de processamento
    cout << setw(8) << "S[i][j]"; // tempo de setup
    cout << setw(8) << "H1[i]"; // tempo adiantado
    cout << setw(8) << "C1[i]"; // valor da penalidade por antecipacao
    cout << setw(8) << "H2[i]"; // tempo atrasado
    cout << setw(8) << "C2[i]"; // valor da penalidade por atraso
    cout << endl;

    for (it = lista_jobs.begin(); it != lista_jobs.end(); it++){
        cout << setw(6) << (*it).getId();
        cout << setw(8) << (*it).getInicio();
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
    cout << "===========================================================" << endl;

}

void Solucao::imprimeSolucao2() {

    cout << left;
    cout << endl;
    cout << "==========================SOLUCAO==========================" << endl << endl;
    cout << "Problema: " << (*prob).getNome_arq() << endl;
    cout << "Numero de Jobs: " << (*prob).getQtd_tarefas() << endl;
    cout << "Custo: " << calculaCusto() << endl;
    cout << endl;

    cout << setw(6) << "Job"; // id do job
    cout << setw(8) << "TI[i]"; // tempo de inicio
    cout << setw(8) << "TP[i]"; // tempo de processamento
    cout << setw(8) << "S[i][j]"; // tempo de setup
    cout << setw(8) << "H1[i]"; // tempo adiantado
    cout << setw(8) << "C1[i]"; // valor da penalidade por antecipacao
    cout << setw(8) << "H2[i]"; // tempo atrasado
    cout << setw(8) << "C2[i]"; // valor da penalidade por atraso
    cout << endl;

    for(int i = 0; i < jobs.size(); i++) {
        cout << setw(6) << jobs[i].getId();
        cout << setw(8) << jobs[i].getInicio();
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
    cout << "===========================================================" << endl;

}

bool Solucao::operator==(const Solucao &sol) const {
    if (sol.jobs.size() != this->jobs.size()) return false;
    for(unsigned int i = 0; i < sol.jobs.size(); i++)
        if(sol.jobs[i] != this->jobs[i])
            return false;
    return true;
}

void Solucao::gerarLinhaDoTempo(int pctgItia) {

    /* Esta funcao mantem a lista e o vetor de jobs atualizados,
     * gerando a linha de tempo de execucao das tarefas
     * determinando o tempo de inicio e fim de cada tarefa
     */

    atualizaVetor();
    int tempo_inicio = 0;

    for(int i = 0; i< jobs.size(); i++){
        jobs[i].setInicio(tempo_inicio);
        if (i != jobs.size() - 1) {
            tempo_inicio += jobs[i].t->getTp() + (*prob).getTempoSetup(jobs[i].getId(), jobs[i+1].getId());
        }
    }

    lista_jobs.clear();
    for(auto job : jobs){
        lista_jobs.push_back(job);
    }


    calculaCusto();

    int numProbalidade = geraPosicaoAleatoria(100)+1;
    if(pctgItia >= numProbalidade) {
        itia();
    }

}

void Solucao::atualizaVetor() {
    // limpa o vetor e preenche novamente atualizado, pois a lista_jobs pode ter sofrido alteracoes
    // como alguma mutacao na solucao que afetou a ordem dos jobs por exemplo
    // como algumas operacoes sao possiveis somente com vetores ou listas e mantido as duas
    // estruturas para facilitar o desenvolvimento
    jobs.clear();
    for(auto job : lista_jobs){
        jobs.push_back(job);
    }
}

void Solucao::atualizaLista() {
    /*funcao de teste feita dia 28/07/18 para usar o arquivo de 4 jobs igual o do artigo do ITIA*/
    lista_jobs.clear();
    for(auto job : jobs){
        lista_jobs.push_back(job);
    }
}

int Solucao::getCusto() const {
    return this->custo;
}

int Solucao::getNumeroEvolucao() const {
    return this->numeroEvolucao;
}

void Solucao::setNumeroEvolucao(int numeroEvolucao) {
    Solucao::numeroEvolucao = numeroEvolucao;
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
        } while(n + 1 == m);

        u = lista_jobs.begin();
        v = lista_jobs.begin();
        advance(u, m);
        advance(v, n + 1);
        lista_jobs.splice(v, lista_jobs, u);


    } else if(tipo == 2){

        do {
            m = geraPosicaoAleatoria((int) lista_jobs.size() - 1);
            n = geraPosicaoAleatoria((int) lista_jobs.size());
        } while(m == n || m == n + 1 || m + 1 == n);

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
        } while(m == n || n == m - 1 || n + 1 == m - 1);

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
        } while(m == n || m == n + 1 || n == m + 1);

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
        } while(m == n || m == n + 1 || m + 1 == n);

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

void Solucao::movimentoVnd(int tipo, int m, int n) {
    /*
     * Tipo 1: trocar u com v
     * Tipo 2: mover u depois de v
     * Tipo 3: mover (u,x) depois de v
     */

    list<Job>::iterator u,v; // iteradores auxiliares
    list<Job>::iterator x,y; // iterado auxiliar que vem antes ou depois de u

    if(tipo == 1){

        u = lista_jobs.begin();
        v = lista_jobs.begin();
        advance(u, m);
        advance(v, n);
        swap(*u, *v);

    } else if(tipo == 2){

        u = lista_jobs.begin();
        v = lista_jobs.begin();
        advance(u, m);
        advance(v, n + 1);
        lista_jobs.splice(v, lista_jobs, u);

    } else {
        // tipo 3
        u = lista_jobs.begin();
        v = lista_jobs.begin();
        x = lista_jobs.begin();
        advance(u, m);
        advance(x, m + 2); // intervalo aberto
        advance(v, n + 1);
        lista_jobs.splice(v, lista_jobs, u, x);

    }


}

Solucao& Solucao::operator=(Solucao sol) {
  //  if(this == &sol) return *this;

    this->lista_jobs.clear();

    for(auto s : sol.lista_jobs){
        this->lista_jobs.push_back(s);
    }
    this->atualizaVetor();
    this->prob = sol.prob;
    this->custo = sol.custo;

    return *this;
}

void Solucao::moveBloco(int inicio, deque<Job>& bloco) {

    // calculo a data de inicio de todas as tarefas baseado na data de inicio da primeira tarefa do bloco
    for(int i = 0; i < bloco.size(); i++){
        if(i == 0) {
            bloco[i].setInicio(inicio);
        } else {
            int setup = this->prob->getTempoSetup(bloco[i-1].getId(), bloco[i].getId());
            int fimAnterior = bloco[i-1].getFim();
            //int Panterior = bloco[i-1].t->getTp(); // tempo de processamento do job anterior
            //int inicioAnterior = bloco[i-1].getInicio();
            //bloco[i].setInicio(inicioAnterior + Panterior + setup); // TODO: conferir se necessita inicioAnterior
            bloco[i].setInicio(fimAnterior + setup);
        }
    }

}

deque<Job> copiaBloco (deque<Job*> bloco) {
    deque<Job> novo;
    for(auto job : bloco){
        novo.push_back(*job);
    }
    return novo;
}

int Solucao::MC(const deque<Job> &bloco) {

    int mc = 0;
    for(auto j : bloco){
        if(j.getFim() < j.t->getE()){
            mc += (-1) * j.t->getAlfa();
        }

        if(j.getFim() >= j.t->getT()){
            mc += j.t->getBeta();
        }
    }

    return mc;

}

int Solucao::M1(const deque<Job> &bloco) {

    int m1 = 99999999;

    for(auto b : bloco){
        if(b.t->getE() <= b.getFim() && b.getFim() < b.t->getT()){
            int v = b.t->getT() - b.getFim();
            if(v < m1) m1 = v;
        }
    }

    return m1;
}

int Solucao::M2(const deque<Job> &bloco) {

    int m2 = 99999999;

    for(auto b : bloco){
        if(b.getFim() < b.t->getE()){
            int v = b.t->getE() - b.getFim();
            if(v < m2) m2 = v;
        }
    }

    return m2;
}

void Solucao::itia() {

    //atualizaVetor();
    deque<Job> sol;
    for(auto job : lista_jobs){
        sol.push_back(job);
    }

    deque<deque<Job*>> blocos;

    int mc = 0; // custo marginal
    int fi = 0; // unidades a serem deslocadas

    blocos.push_front(deque<Job*>{});


    for (int i = int(sol.size() - 1); i >= 0; i--) {
        //blocos.push_front(deque<Job*>{}); //inseri agora, equivale ao de cima
        blocos.front().push_front(&sol[i]); //inseri agora, equivale ao de baixo

        if(sol[i].getFim() < sol[i].t->getE()){
            //blocos.front().push_front(&sol[i]); --comentei agora
            //blocos.push_front(deque<Job*>{&sol[i]});

            mc = MC(copiaBloco(blocos.front()));

            while(mc < 0){

                // linha 12 pseudo -> if last(xi) != xn then
                if(blocos.front().back()->getId() != sol[sol.size() - 1].getId()){

                    //int setup = prob->getTempoSetup(sol[i].getId(), sol[i+1].getId());
                    int setup = prob->getTempoSetup(blocos.front().back()->getId(), blocos[1].front()->getId());
                    //fi = min(sol[i+1].getFim() - sol[i+1].t->getTp() - setup, min(M1(copiaBloco(blocos.front())), M2(copiaBloco(blocos.front()))));
                    int m1 = M1(copiaBloco(blocos.front()));
                    int m2 = M2(copiaBloco(blocos.front()));
                    int tempo = (blocos[1].front()->getFim() - blocos[1].front()->t->getTp() - setup) - blocos.front().back()->getFim();
                    fi = min(tempo, min(m1, m2));
                } else {
                    fi = min(M1(copiaBloco(blocos.front())), M2(copiaBloco(blocos.front())));
                }

                // arrasta o bloco fi posicoes - linha 15 e 16 do pseudo
                blocos.front()[0]->setInicio(blocos.front()[0]->getInicio() + fi);
                for (int j = 1; j < blocos.front().size(); j++) {
                    int setup = prob->getTempoSetup(blocos.front()[j-1]->getId(),  blocos.front()[j]->getId());
                    blocos.front()[j]->setInicio(blocos.front()[j-1]->getFim() + setup);
                }

                if(blocos.front().back()->getId() != sol[sol.size() - 1].getId()){
                    // linha 17 pseudo
                    int setup = this->prob->getTempoSetup(blocos.front().back()->getId(),  blocos[1].front()->getId());
                    if(blocos.front().back()->getFim() + setup + blocos[1].front()->t->getTp() == blocos[1].front()->getFim()){
                        // linha 19 pseudo
                        for (int j = int(blocos.front().size() - 1); j >= 0; j--) {
                            blocos[1].push_front(blocos.front()[j]);
                        }
                        blocos.pop_front();
                    }

                    // se nao for igual creio que nao precisa juntar os blocos

                    /*else {
                        // linha 21 pseudo
                        blocos.push_front(deque<Job*>{&sol[i]});
                    }*/



                }

                mc = MC(copiaBloco(blocos.front()));

            }

            blocos.push_front(deque<Job*>{});

        } /*else { // nao consta no pseudo mas creio que precisa adicionar quando nao atende o if para saber quais jobs pertencem ao bloco
            blocos.front().push_front(&sol[i]);
            //blocos.push_front(deque<Job*>{});
        }*/


    }

    lista_jobs.clear(); // no itia as operacoes sao feitas com vetor, portanto a lista deve ser atualizada apos o final

    // atualiza lista de jobs com as alteracoes feitas no vetor de jobs
    for(auto job: sol){
        lista_jobs.push_back(job);
    }

    // atualiza o vetor de escopo global, ja que as alteracoes sao feitas num vetor de escopo local
    atualizaVetor();

    calculaCusto(); // apos concluir o itia, chama a funca para calcular o custo e atualizar o valor da variavel de escopo global custo

}





