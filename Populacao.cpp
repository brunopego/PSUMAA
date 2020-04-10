#include "Populacao.h"
#include "Problema.h"
#include <utility>
#include <random>
#include <algorithm>
#include <omp.h>

#define ALFA( ) ((double) rand()) / (((double)RAND_MAX))

bool ordernaPorCusto(const Solucao& a, const Solucao& b){
    return (a.getCusto() < b.getCusto());
}

int geraTipoMutacao(int num){
    return (rand() % num) + 1;
}

Populacao::Populacao(int mi, int lambda, int tipo, Problema* prob, int tipoEstrategia, int pctgItia, double start) {

    // Parametros utilizados
    this->mi = mi; // numero de pais selecionados
    this->lambda = lambda; // numero de filhos gerados
    /*
     * tipo 1 = edd
     * tipo 2 = tdd
     * tipo 3 = spt
     * tipo >3 = aleatorio
     */
    // nao esta utilizando esse tipo mais
    this->tipo = tipo;
    this->prob = prob;
    //this->qtdEvolucao = qtdEvolucao;
    this->tipoEstrategia = tipoEstrategia;
    this->pctgItia = pctgItia;
    //this->pctgVnd = pctgVnd;
    //this->pctgMut = pctgMut; // nao esta sendo utilizado (nao era eficaz)
    this->start =  start;

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

    /*
     * No laco abaixo sao inseridos 3 individuos gerados de forma gulosa,
     * cada individuo foi gerado com uma heuristica construtiva diferente
     */
    /*for(int i = 1; i <= 3; i++){
        Solucao s(prob); //inicia uma nova solucao (individuo)
        s.ordena(0, i); // ordena de forma gulosa utilizando 3 heuristicas construtivas
        s.gerarLinhaDoTempo(); // apos a ordenacao a linha do tempo de execucao e custo sao atualizados
        populacao_set.insert(s); //insere o individuo na populacao
    }*/

    for(int i = 1; i <= 1; i++){
        Solucao s(prob); //inicia uma nova solucao (individuo)
        s.ordena(0, i); // ordena de forma gulosa utilizando 3 heuristicas construtivas
        s.gerarLinhaDoTempo(pctgItia); // apos a ordenacao a linha do tempo de execucao e custo sao atualizados
        populacao_set.insert(s); //insere o individuo na populacao
    }

    while(i < (mi-1)){
        Solucao sol(prob); //inicia uma nova solucao (individuo)
        // a funcao geraTipoMutacao abaixo gera numero aleatorio, exemplo: 4, entao gera 1 ate 4 inclusive.
        sol.ordena(ALFA(), geraTipoMutacao(4)); // ordena o individuo de forma parcialmente gulosa
        //sol.ordena(ALFA(), 1);
        par = populacao_set.insert(sol); //funcao insert insere somente se individuo nao existir na populacao
        /* if abaixo se true, significa que o individuo foi inserido pois ainda nao existia
         * entao i++ ate inserir mi-3 individuos e gerar toda populacao inicial
         */
        if(par.second) i++;
    }

    //while(i < (mi-3)){
    //  Solucao sol(prob); //inicia uma nova solucao (individuo)
    // a funcao geraTipoMutacao abaixo gera numero aleatorio, exemplo: 4, entao gera 1 ate 4 inclusive.
    // sol.ordena(ALFA(), geraTipoMutacao(4)); // ordena o individuo de forma parcialmente gulosa
    // par = populacao_set.insert(sol); //funcao insert insere somente se individuo nao existir na populacao
    /* if abaixo se true, significa que o individuo foi inserido pois ainda nao existia
     * entao i++ ate inserir mi-3 individuos e gerar toda populacao inicial
     */
    //  if(par.second) i++;
    // }

    /*
     * Apos todos os individuos terem sidos gerados,
     * a linha do tempo de execucao e o custo de cada individuo sao atualizados
     * e os individuos que estavam em populacao_set sao passados para o vector populacao
     * onde as proximas acoes serao executadas na estrategia evolutiva
     */
    for(auto sol : populacao_set){
        sol.gerarLinhaDoTempo(pctgItia);
        //sol.itia(); // NOW
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


void Populacao::estrategiaEvolutiva() {

    //int qtd_filhos = mi/lambda; // quatidade de filhos a serem gerados a cada evolucao

    //novo
    int qtd_filhos = lambda;
    int convergencia = 100000000;
    int taxa_convergencia = 0;

    int numEvolucao = 1;

    while(true){

        for(int h = 0; h < mi; h++){ // para cada pai
            for(int j = 0; j < qtd_filhos; j++){ // gera qtd_filhos para cada pai
                //tipo_mutacao = geraTipoMutacao(6);
                Solucao s(prob);
                s = populacao[h];
                s.fazerMutacao(geraTipoMutacao(6));

                s.gerarLinhaDoTempo(pctgItia);
                //s.itia(); // NOW

                populacao.push_back(s);


            }


        }

        ordernarPopulacao();
        //cout << "Tamanho da populacao: " << populacao.size() << endl;
        populacao.resize(mi, Solucao(prob));
        //cout << "Tamanho depois do corte: " << populacao.size() << endl;

        if(tipoEstrategia == 1) {
            for(int k = 0; k < populacao.size(); k++){
                //populacao[k] = vndPM(populacao[k]);
                populacao[k] = merm(populacao[k]);
                //populacao[k].gerarLinhaDoTempo();
            }
            ordernarPopulacao();
        }

        if(populacao.front().getCusto() < convergencia){
            convergencia = populacao.front().getCusto();
            taxa_convergencia = 0;
        }


        /*
        cout << endl;
        cout << "Numeros de evolucao: " << numEvolucao << endl;
        cout << "Convergencia: " << convergencia << endl;
        cout << endl;*/

        if(populacao.front().getCusto() == convergencia) taxa_convergencia ++;

        if(taxa_convergencia == 4 * this->prob->getQtd_tarefas()) {
            populacao.front().setNumeroEvolucao(numEvolucao);
            break;
        }

        if(omp_get_wtime() - start > 1200) {
            populacao.front().setNumeroEvolucao(numEvolucao);
            break;
        }

        numEvolucao++;

    }



}

// MERM - Mutacao Evolutiva Randomica de Melhora
Solucao Populacao::merm(Solucao sol) {

    Solucao melhor(prob);

    melhor = sol;
    //melhor.gerarLinhaDoTempo();
    //melhor.itia();

    vector<int> v = {1,2,3,4,5,6};
    random_shuffle(v.begin(), v.end());

    for(int i = 1; i < 7; i++){

        sol.fazerMutacao(v[i-1]);
        sol.gerarLinhaDoTempo(100);
        if(sol.getCusto() < melhor.getCusto()) {
            melhor = sol;
            //melhor.gerarLinhaDoTempo();
            //melhor.itia();
            //break;
            i = 0;
        }


    }


    //melhor.imprimeSolucao();

    return melhor;

}

// Retorna a primeira melhor solução, no pior dos casos irá percorrer a vizinhanca toda
Solucao primeiroDeMelhora(int tipo, int qtd, Solucao melhor, Solucao atual){


    melhor.gerarLinhaDoTempo(100);
    //atual = melhor;
    bool sair = false;

    for(int i = 0; i < qtd; i++){
        for(int j = i + 1; j < qtd; j++){
            if(tipo == 1 || tipo == 2){

                atual.movimentoVnd(tipo, i, j);
                atual.gerarLinhaDoTempo(100);
                if(atual.getCusto() < melhor.getCusto()){
                    melhor = atual;
                    melhor.gerarLinhaDoTempo(100);
                    sair = true;
                    break;
                }

            } else if(qtd-i > 2 && j != i+1){
                atual.movimentoVnd(tipo, i, j);
                atual.gerarLinhaDoTempo(100);
                if(atual.getCusto() < melhor.getCusto()){
                    melhor = atual;
                    melhor.gerarLinhaDoTempo(100);
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
    melhor.gerarLinhaDoTempo(100);
    s_atual.gerarLinhaDoTempo(100);

    int tipo = 1;
    int qtd = (int) s_atual.getListaJobs().size();
    //bool sair = false;
    //int iteracoes_sem_melhora = 10;

    while(tipo <= 3){ // tres tipos de vizinhanca implementados nesse caso
        s_linha = primeiroDeMelhora(tipo, qtd, melhor, s_atual);
        s_linha.gerarLinhaDoTempo(100);
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
