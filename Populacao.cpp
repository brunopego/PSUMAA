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

Populacao::Populacao(int mi, int lambda, int tipo, Problema* prob, int qtdEvolucao, int tipoEstrategia, int pctgVnd, int pctgMut, double start) {

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
    this->qtdEvolucao = qtdEvolucao;
    this->tipoEstrategia = tipoEstrategia;
    this->pctgVnd = pctgVnd;
    this->pctgMut = pctgMut; // nao esta sendo utilizado (nao era eficaz)
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
        s.gerarLinhaDoTempo(); // apos a ordenacao a linha do tempo de execucao e custo sao atualizados
        populacao_set.insert(s); //insere o individuo na populacao
    }

    while(i < (mi-1)){
        Solucao sol(prob); //inicia uma nova solucao (individuo)
        // a funcao geraTipoMutacao abaixo gera numero aleatorio, exemplo: 4, entao gera 1 ate 4 inclusive.
        sol.ordena(ALFA(), 1); // ordena o individuo de forma parcialmente gulosa
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
        sol.gerarLinhaDoTempo();
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

void Populacao::estrategiaEvolutivaParalela() {

    int qtd_filhos = lambda/mi; // quatidade de filhos a serem gerados a cada evolucao
    int convergencia = 100000000;
    int taxa_convergencia = 0;

    for(int i = 0; i < qtdEvolucao; i++){

        if(omp_get_wtime() - start > 1200) break;

        #pragma omp parallel for
            for(int h = 0; h < mi; h++){ // para cada pai
                    for(int j = 0; j < qtd_filhos; j++){ // gera qtd_filhos para cada pai
                        Solucao s(prob);
                        s = populacao[h];
                        s.fazerMutacao(geraTipoMutacao(6));

                        s.gerarLinhaDoTempo();

                        #pragma omp critical
                        {
                            populacao.push_back(s);
                        };

                    }


            }

        if(tipoEstrategia == 1){ // merm e vnd
            if(i < 95*qtdEvolucao/100){
                #pragma omp parallel for schedule (dynamic, (mi+lambda)/50)
                    for(int k = 0; k < populacao.size(); k++){

                        if(pctgVnd >= geraTipoMutacao(100)){
                            populacao[k] = merm(populacao[k]);
                            populacao[k].gerarLinhaDoTempo();
                        }


                        /*if(50 >= geraTipoMutacao(100)){
                            populacao[k].itia();
                        }*/

                    }
            } else {
                #pragma omp parallel for schedule (dynamic, (mi+lambda)/50)
                    for(int k = 0; k < populacao.size(); k++){

                        if(pctgVnd >= geraTipoMutacao(100)){
                            populacao[k] = vndPM(populacao[k]);
                            populacao[k].gerarLinhaDoTempo();
                        }


                        /*if(50 >= geraTipoMutacao(100)){
                            populacao[k].itia();
                        }*/

                    }
            }

        } else if(tipoEstrategia == 2) { // vnd
            #pragma omp parallel for schedule (dynamic, (mi+lambda)/50)
                for(int k = 0; k < populacao.size(); k++){

                    if(pctgVnd >= geraTipoMutacao(100)){
                        populacao[k] = vndPM(populacao[k]);
                        populacao[k].gerarLinhaDoTempo();
                    }


                    /*if(50 >= geraTipoMutacao(100)){
                            populacao[k].itia();
                    }*/

                }

        }




        ordernarPopulacao();
        //cout << "Tamanho da populacao: " << populacao.size() << endl;
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

    int qtd_filhos = mi/lambda; // quatidade de filhos a serem gerados a cada evolucao
    int convergencia = 100000000;
    int taxa_convergencia = 0;

    for(int i = 0; i < qtdEvolucao; i++){

        for(int h = 0; h < mi; h++){ // para cada pai
            for(int j = 0; j < qtd_filhos; j++){ // gera qtd_filhos para cada pai
                //tipo_mutacao = geraTipoMutacao(6);
                Solucao s(prob);
                s = populacao[h];
                s.fazerMutacao(geraTipoMutacao(6));

                s.gerarLinhaDoTempo();
                //s.itia(); // NOW

                populacao.push_back(s);


            }


        }
        /*
        if(tipoEstrategia == 1){ // merm e vnd
            if(i < 95*qtdEvolucao/100){

                for(int k = 0; k < populacao.size(); k++){

                    if(pctgVnd >= geraTipoMutacao(100)){
                        populacao[k] = merm(populacao[k]);
                        populacao[k].gerarLinhaDoTempo();
                    }


                    if(50 >= geraTipoMutacao(100)){
                        populacao[k].itia();
                    }


                    if(omp_get_wtime() - start > 1200) break;

                }
            } else {

                for(int k = 0; k < populacao.size(); k++){

                    if(pctgVnd >= geraTipoMutacao(100)){
                        populacao[k] = vndPM(populacao[k]);
                        populacao[k].gerarLinhaDoTempo();
                    }


                    if(50 >= geraTipoMutacao(100)){
                        populacao[k].itia();
                    }


                    if(omp_get_wtime() - start > 1200) break;

                }
            }

        } else if(tipoEstrategia == 2){ // vnd
            for(int k = 0; k < populacao.size(); k++){

                if(pctgVnd >= geraTipoMutacao(100)){
                    populacao[k] = vndPM(populacao[k]);
                    populacao[k].gerarLinhaDoTempo();
                    //populacao[k].itia();
                }


                if(50 >= geraTipoMutacao(100)){
                    populacao[k].itia();
                }


                if(omp_get_wtime() - start > 1200) break;

            }

        }*/


        /*for(int k = 0; k < populacao.size(); k++){

            populacao[k] = merm(populacao[k]);
            populacao[k].gerarLinhaDoTempo();
            //populacao[k].itia();
            if(omp_get_wtime() - start > 1200) break;

        }*/



        ordernarPopulacao();
        //cout << "Tamanho da populacao: " << populacao.size() << endl;
        populacao.resize(mi, Solucao(prob));
        cout << "Tamanho depois do corte: " << populacao.size() << endl;

        for(int k = 0; k < populacao.size(); k++){
            //populacao[k] = vndPM(populacao[k]);
            populacao[k] = merm(populacao[k]);
            populacao[k].gerarLinhaDoTempo();
        }
        ordernarPopulacao();

        if(populacao.front().getCusto() < convergencia){
            convergencia = populacao.front().getCusto();
            taxa_convergencia = 0;
        }

        cout << endl;
        cout << "Numeros de evolucao: " << i+1 << endl;
        cout << "Convergencia: " << convergencia << endl;
        cout << endl;

        if(populacao.front().getCusto() == convergencia) taxa_convergencia ++;

        //if(taxa_convergencia == 4 * this->prob->getQtd_tarefas()) break; // 4 * n
        if(taxa_convergencia == 40) break;

        if(omp_get_wtime() - start > 1200) break;

    }



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

            } else if(qtd-i > 2 && j != i+1){
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