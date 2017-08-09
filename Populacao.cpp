#include "Populacao.h"
#include "Problema.h"
#include <utility>
#include <random>
#include <algorithm>
#include <omp.h>

#define ALFA( ) ((double) rand()) / (((double)RAND_MAX))

/*
float gerarAlfa(){
    // gera numero aleatorio entre 0 e 1
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0,1);
    return (float) dis(gen);
}
*/

bool ordernaPorCusto(const Solucao& a, const Solucao& b){
    return (a.getCusto() < b.getCusto());
}

int geraTipoMutacao(int num){
    return (rand() % num) + 1;
}

Populacao::Populacao(int mi, int lambda, int tipo, Problema* prob, int qtdEvolucao, int tipoEstrategia, int pctgVnd, int pctgMut) {

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
    this->qtdEvolucao = qtdEvolucao;
    this->tipoEstrategia = tipoEstrategia;
    this->pctgVnd = pctgVnd;
    this->pctgMut = pctgMut;

    pair<unordered_set<Solucao, HashSolucao>::iterator,bool> par;

    int i = 0;
    /*
    // adiciona um individuo construido de forma gulosa
    Solucao s(prob);
    //s.ordena(0, tipo);
    s.ordena(0, 1);
    s.ordena(0, 2);
    s.ordena(0, 3);
    s.gerarLinhaDoTempo();
    populacao_set.insert(s);
    */

    for(int i = 1; i <= 3; i++){
        Solucao s(prob);
        s.ordena(0, i);
        s.gerarLinhaDoTempo();
        populacao_set.insert(s);
    }

    while(i < (mi-3)){
        Solucao sol(prob);
        //sol.ordena(ALFA(), 1);
        //sol.ordena(gerarAlfa(), geraTipoMutacao(4));
        sol.ordena(ALFA(), geraTipoMutacao(4));
        par = populacao_set.insert(sol);
        if(par.second) i++;
    }

    for(auto sol : populacao_set){
        sol.gerarLinhaDoTempo();
        populacao.push_back(sol);
    }

}

void Populacao::imprimePopulacao() {

    for(auto sol : populacao){
        sol.imprimeSolucao();
    }

}

vector <Solucao> &Populacao::getPopulacao() {
    return populacao;
}

void Populacao::ordernarPopulacao() {
    //populacao.sort(ordernaPorCusto);
    sort(populacao.begin(), populacao.end(), ordernaPorCusto);
}

void Populacao::estrategiaEvolutivaParalela() {

    int qtd_filhos = lambda/mi; // quatidade de filhos a serem gerados a cada evolucao
    list<Solucao> aux; // vetor auxiliar de populacao onde os filhos gerados sao colocados antes de juntar ao pais
    int convergencia = 100000000;
    int taxa_convergencia = 0;

    for(int i = 0; i < qtdEvolucao; i++){

        #pragma omp parallel for
            for(int h = 0; h < mi; h++){ // para cada pai
                    for(int j = 0; j < qtd_filhos; j++){ // gera qtd_filhos para cada pai
                        Solucao s(prob);
                        s = populacao[h];
                        //while(pctgMut >= geraTipoMutacao(100)){
                            s.fazerMutacao(geraTipoMutacao(6));
                        //}

                        //------------------------------------------------------------------
                        /*
                        int tipoMutacao = geraTipoMutacao(6);
                        int tamanho = int(s.getJobs().size());
                        for(int m = 0; m < tamanho; m++){
                            if(pctgMut >= geraTipoMutacao(100)){
                                for(int n = m+1; n < tamanho; n++){
                                    if(tipoMutacao == 1 || tipoMutacao == 4){ // Tipo 1: mover u depois de v, Tipo 4: trocar u com v
                                        if(m < tamanho - 1){
                                            s.fazerMutacao(tipoMutacao, m, n);
                                            break;
                                        }
                                    } else if(tipoMutacao == 2){ // mover (u,x) depois de v
                                        if(tamanho - m > 2 && n == m + 2){
                                            s.fazerMutacao(tipoMutacao, m, n);
                                            break;
                                        }
                                    } else if(tipoMutacao == 3){ // mover (x,u) depois de v
                                        if(m > 0 && m < tamanho - 1){
                                            s.fazerMutacao(tipoMutacao, m, n);
                                            break;
                                        }
                                    } else if(tipoMutacao == 5){ // trocar (u,x) com v
                                        if(n != m + 1 && tamanho - m >= 3){
                                            s.fazerMutacao(tipoMutacao, m, n);
                                            break;
                                        }
                                    } else if(tipoMutacao == 6){ // trocar (u,x) com (v,y)
                                        if(m + 1 != n && tamanho - m >= 4 && tamanho - n >= 2){
                                            s.fazerMutacao(tipoMutacao, m, n);
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        */





                        //------------------------------------------------------------------


                        s.gerarLinhaDoTempo();

                        #pragma  omp critical
                        {
                            //aux.push_back(s);
                            populacao.push_back(s);
                        };

                    }


            }

        //populacao.splice(populacao.end(), aux);

        if(tipoEstrategia == 1){ // merm e vnd
            if(i < 95*qtdEvolucao/100){
                #pragma omp parallel for schedule (dynamic, (mi+lambda)/50)
                    for(int k = 0; k < populacao.size(); k++){

                        if(pctgVnd >= geraTipoMutacao(100)){
                            populacao[k] = merm(populacao[k]);
                            populacao[k].gerarLinhaDoTempo();
                        }

                        /*
                        if(50 >= geraTipoMutacao(100)){
                            populacao[k].itia();
                        }
                        */

                    }
            } else {
                #pragma omp parallel for schedule (dynamic, (mi+lambda)/50)
                    for(int k = 0; k < populacao.size(); k++){

                        if(pctgVnd >= geraTipoMutacao(100)){
                            populacao[k] = vndPM(populacao[k]);
                            //populacao[k].itia();
                            //populacao[k] = ils(populacao[k]);
                            populacao[k].gerarLinhaDoTempo();
                        }

                        /*
                        if(50 >= geraTipoMutacao(100)){
                            populacao[k].itia();
                        }
                        */

                    }
            }

        } else if(tipoEstrategia == 2) { // vnd
            #pragma omp parallel for schedule (dynamic, (mi+lambda)/50)
                for(int k = 0; k < populacao.size(); k++){

                    if(pctgVnd >= geraTipoMutacao(100)){
                        populacao[k] = vndPM(populacao[k]);
                        //populacao[k].itia();
                        //populacao[k] = ils(populacao[k]);
                        populacao[k].gerarLinhaDoTempo();
                    }

                    /*
                    if(50 >= geraTipoMutacao(100)){
                        populacao[k].itia();
                    }
                    */

                }

        }




        ordernarPopulacao();
        //cout << "Tamanho da populacao: " << populacao.size() << endl;
        //int tam = (int) (0.08 * populacao.size());
        //cout << "Tamanho do corte: " << tam << endl;
        populacao.resize(mi, Solucao(prob));
        //cout << "Tamanho depois do corte: " << populacao.size() << endl;

        if(populacao.front().getCusto() < convergencia){
            convergencia = populacao.front().getCusto();
            taxa_convergencia = 0;
        }

        //cout << endl;
        //cout << "Numeros de evolucao: " << i+1 << endl;
        //cout << "Convergencia: " << convergencia << endl;
        //cout << endl;

        if(populacao.front().getCusto() == convergencia) taxa_convergencia ++;

        if(taxa_convergencia == 4 * this->prob->getQtd_tarefas()) break; // 4 * n

    }



}

void Populacao::estrategiaEvolutiva() {

    int qtd_filhos = lambda/mi; // quatidade de filhos a serem gerados a cada evolucao
    list<Solucao> aux; // vetor auxiliar de populacao onde os filhos gerados sao colocados antes de juntar ao pais
    int convergencia = 100000000;
    int taxa_convergencia = 0;

    for(int i = 0; i < qtdEvolucao; i++){


        for(int h = 0; h < mi; h++){ // para cada pai
            for(int j = 0; j < qtd_filhos; j++){ // gera qtd_filhos para cada pai
                //tipo_mutacao = geraTipoMutacao(6);
                Solucao s(prob);
                s = populacao[h];
                //while(pctgMut >= geraTipoMutacao(100)){ // geraTipoMutacao gera um numero entre 1 e 100 no caso
                    s.fazerMutacao(geraTipoMutacao(6));
                //}

                s.gerarLinhaDoTempo();


                //aux.push_back(s);
                populacao.push_back(s);


            }


        }

        //populacao.splice(populacao.end(), aux);

        if(tipoEstrategia == 1){ // merm e vnd

            if(i < 95*qtdEvolucao/100){

                for(int k = 0; k < populacao.size(); k++){

                    if(pctgVnd >= geraTipoMutacao(100)){
                        populacao[k] = merm(populacao[k]);
                        populacao[k].gerarLinhaDoTempo();
                    }

                    /*
                    if(50 >= geraTipoMutacao(100)){
                        populacao[k].itia();
                    }
                    */

                }
            } else {

                for(int k = 0; k < populacao.size(); k++){

                    if(pctgVnd >= geraTipoMutacao(100)){
                        populacao[k] = vndPM(populacao[k]);
                        populacao[k].gerarLinhaDoTempo();
                    }

                    /*
                    if(50 >= geraTipoMutacao(100)){
                        populacao[k].itia();
                    }
                    */

                }
            }

        } else if(tipoEstrategia == 2){ // vnd

            for(int k = 0; k < populacao.size(); k++){

                if(pctgVnd >= geraTipoMutacao(100)){
                    populacao[k] = vndPM(populacao[k]);
                    populacao[k].gerarLinhaDoTempo();
                }

                /*
                if(50 >= geraTipoMutacao(100)){
                    populacao[k].itia();
                }
                */

            }

        }



        ordernarPopulacao();
        //cout << "Tamanho da populacao: " << populacao.size() << endl;
        //int tam = (int) (0.08 * populacao.size());
        //cout << "Tamanho do corte: " << tam << endl;
        populacao.resize(mi, Solucao(prob));
        //cout << "Tamanho depois do corte: " << populacao.size() << endl;

        if(populacao.front().getCusto() < convergencia){
            convergencia = populacao.front().getCusto();
            taxa_convergencia = 0;
        }

        //cout << endl;
        //cout << "Numeros de evolucao: " << i+1 << endl;
        //cout << "Convergencia: " << convergencia << endl;
        //cout << endl;

        if(populacao.front().getCusto() == convergencia) taxa_convergencia ++;

        if(taxa_convergencia == 4 * this->prob->getQtd_tarefas()) break; // 4 * n

    }



}

// MERMS - Mutacao Evolutiva Randomica de Melhora Simples
Solucao Populacao::merms(Solucao sol) {

    Solucao melhor(prob);
    melhor = sol;
    melhor.gerarLinhaDoTempo();


    for(int i = 1; i < 7; i++){

        sol.fazerMutacao(i);
        sol.gerarLinhaDoTempo();
        if(sol.getCusto() < melhor.getCusto()) {
            melhor = sol;
            melhor.gerarLinhaDoTempo();
            break;
            //i--;
        }


    }


    //melhor.imprimeSolucao();

    return melhor;

}

// MERM - Mutacao Evolutiva Randomica de Melhora
Solucao Populacao::merm(Solucao sol) {

    Solucao melhor(prob);
    melhor = sol;
    melhor.gerarLinhaDoTempo();

    vector<int> v = {1,2,3,4,5,6};
    random_shuffle(v.begin(), v.end());

    for(int i = 1; i < 7; i++){

        sol.fazerMutacao(v[i-1]);
        sol.gerarLinhaDoTempo();
        if(sol.getCusto() < melhor.getCusto()) {
            melhor = sol;
            melhor.gerarLinhaDoTempo();
            //break;
            i = 0;
        }


    }


    //melhor.imprimeSolucao();

    return melhor;

}

// Retorna a primeira melhor solução, no pior dos casos irá percorrer a vizinhanca toda
Solucao primeiroDeMelhora(int tipo, int qtd, Solucao melhor, Solucao atual){


    melhor.gerarLinhaDoTempo();
    //atual = melhor;
    bool sair = false;

    for(int i = 0; i < qtd; i++){
        for(int j = i + 1; j < qtd; j++){
            if(tipo == 1 || tipo == 2){

                atual.movimentoVnd(tipo, i, j);
                atual.gerarLinhaDoTempo();
                if(atual.getCusto() < melhor.getCusto()){
                    melhor = atual;
                    melhor.gerarLinhaDoTempo();
                    sair = true;
                    break;
                }

            } else if(qtd-i > 2 && j == i+2){
                atual.movimentoVnd(tipo, i, j);
                atual.gerarLinhaDoTempo();
                if(atual.getCusto() < melhor.getCusto()){
                    melhor = atual;
                    melhor.gerarLinhaDoTempo();
                    sair = true;
                    break;
                }
            }
        }
        if(sair) break;
    }

    return melhor;

}

// VND Primeiro de Melhora
Solucao Populacao::vndPM(Solucao s_atual) {

    Solucao melhor(prob), s_linha(prob);
    melhor = s_linha = s_atual;
    melhor.gerarLinhaDoTempo();
    s_atual.gerarLinhaDoTempo();

    int tipo = 1;
    int qtd = (int) s_atual.getListaJobs().size();
    //bool sair = false;
    //int iteracoes_sem_melhora = 10;

    while(tipo <= 3){ // tres tipos de vizinhanca implementados nesse caso
        s_linha = primeiroDeMelhora(tipo, qtd, melhor, s_atual);
        s_linha.gerarLinhaDoTempo();
        if(s_linha.getCusto() < s_atual.getCusto()){
            s_atual = s_linha;
            tipo = 1;
        } else {
            tipo++;
        }
    }

    //melhor.imprimeSolucao();

    return s_atual;
}

Solucao Populacao::ils(Solucao s) {

    Solucao sol_ls = vndPM(s);
    Solucao s_l = sol_ls;
    Solucao s_ll(prob);

    for (int i = 0; i < 60; i++) {

        for (int j = 0; j < int(0.5 * s.getJobs().size()); j++) {
            s_l.fazerMutacao(geraTipoMutacao(6));
        }
        s_l.gerarLinhaDoTempo();
        s_ll = vndPM(s_l);

        if(s_ll.getCusto() < sol_ls.getCusto()){
            sol_ls = s_ll;
        }


    }

    return sol_ls;
}

/*
void Populacao::vnd() {

    Solucao melhor(prob), aux(prob);
    melhor = aux = populacao.front();
    melhor.calculaCusto();

    vector<int> v = {1,2,3,4,5,6};
    random_shuffle(v.begin(), v.end());


    for(int i = 1; i < 7; i++){

        aux.fazerMutacao(v[i - 1]);
        aux.gerarLinhaDoTempo();

        if(aux.getCusto() < melhor.getCusto()) {
            melhor = aux;
            melhor.calculaCusto();
            i = 0;
        }


    }


    melhor.imprimeSolucao();

}
*/

/*
bool menorPair(const pair<int,float>& a, const pair<int,float>& b){
    return (a.second < b.second);
}

void Populacao::vnd() {

    Solucao melhor(prob), aux(prob);
    melhor = aux = populacao.front();
    melhor.gerarLinhaDoTempo();

    //vector<int> v = {1,2,3,4,5,6};
    //random_shuffle(v.begin(), v.end());
    //sort(v.begin(),v.end());
    //v.back();
    vector<pair<int,float>> peso = {{1,0},{2,0},{3,0},{4,0},{5,0},{6,0}};

    for(int i = 0; i < 5; i++){
        for(int i = 1; i < 7; i++){
            aux.fazerMutacao(i);
            aux.gerarLinhaDoTempo();

            peso[i-1].second += (float) aux.getCusto() / (float) melhor.getCusto();
            aux = melhor;

        }
    }

    sort(peso.begin(),peso.end(),menorPair);

    for(int i = 1; i < 7; i++){

        aux.fazerMutacao(peso[i-1].first);
        aux.gerarLinhaDoTempo();

        if(aux.getCusto() < melhor.getCusto()) {
            melhor = aux;
            melhor.gerarLinhaDoTempo();
            i = 0;
        }


    }


    melhor.imprimeSolucao();

}
*/

void Populacao::setPopulacao(const list<Solucao>& sol, int mi, int lambda, int tipo, Problema* prob) {

    this->mi = mi;
    this->lambda = lambda;
    this->tipo = tipo;
    this->prob = prob;

    this->populacao.clear();
    for(auto s : sol){
        this->populacao.push_back(s);
    }

}

