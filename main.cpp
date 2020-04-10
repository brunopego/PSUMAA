#include <iostream>
#include <random>
#include <ctime>
#include <chrono>
#include <cstdlib>
#include <cstring>

#include "Problema.h"
#include "Solucao.h"
#include "Populacao.h"
#include <omp.h>


using namespace std;
using namespace std::chrono;


char* getParamName(char* target, const char* str) {
    unsigned int i;
    unsigned int size;
    unsigned int pos;
    pos = 0;
    size = strlen(str);
    for ( i=0 ; i<size ; i++ ) {
        if (str[i] != '-') {
            if (str[i] != '=') {
                target[pos++] = str[i];
            } else {
                break;
            }
        }
    }
    target[pos] = '\0';
    return target;
}

char* getParamValue(char* target, const char* str) {
    unsigned int i;
    unsigned int size;
    size = strlen(str);
    unsigned int destSize = 0;
    for ( i=0 ; i<size ; i++) {
        if (str[i]=='=') break;
    }
    i++;
    for ( ; i<size ; i++) {
        target[destSize] = str[i];
        destSize++;
    }
    target[destSize] = 0;
    return target;
}


int main(int argc, char **argv) {

    char pName[256], pValue[256];
    int paralelo=1;
    string nomeArquivo = "";
    int mi = 1, lambda = 1, tipo = 1, qtdEvolucao = 0, tipoEstrategia = 0, pctgVnd = 0, pctgMut = 0, pctgItia = 100;

    for(int i = 1; i < argc; i++)
    {

        getParamName( pName, argv[i] );
        getParamValue( pValue, argv[i] );

        /*
        if (strcmp( pName, "paralelo" )==0)
        {
            paralelo = atoi(pValue);
            continue;
        }
         */

        if (strcmp( pName, "nomeArquivo" )==0)
        {
            nomeArquivo = std::string(pValue);
            continue;
        }



        if (strcmp( pName, "mi" )==0)
        {
            mi = atoi(pValue);
            continue;
        }

        if (strcmp( pName, "lambda" )==0)
        {
            lambda = atoi(pValue);
            continue;
        }

        if (strcmp( pName, "tipo" )==0)
        {
           tipo = atoi(pValue);
            continue;
        }

        /*
        if (strcmp( pName, "qtdEvolucao" )==0)
        {
            qtdEvolucao = atoi(pValue);
            continue;
        }*/

        if (strcmp( pName, "tipoEstrategia" )==0)
        {
            tipoEstrategia = atoi(pValue);
            continue;
        }

        if (strcmp( pName, "pctgItia" )==0)
        {
            pctgItia = atoi(pValue);
            continue;
        }

        /*
        if (strcmp( pName, "pctgVnd" )==0)
        {
            pctgVnd = atoi(pValue);
            continue;
        }*/

        /*
        if (strcmp( pName, "pctgMut" )==0)
        {
            pctgMut = atoi(pValue);
            continue;
        }
         */

    }

    //high_resolution_clock::time_point t1 = high_resolution_clock::now();

    double start = omp_get_wtime();

    // Alfa =  0 -> Guloso, 1 -> totalmente aleatorio

    // semente para a funcao rand() para gerar um valor aleatorio
    srand(time(NULL));

    //Problema p("instancias/dados/INST0703.dat");
    //Problema p("instancias/dados/INST0801.dat");
    //Problema p("instancias/dados/INST1001.dat");
    //Problema p("instancias/dados/INST2002.dat");
    //Problema p("instancias/dados/INST2006.dat");
    //Problema p("instancias/dados/INST04.dat");
    //Problema p("instancias/dados/INST2004.dat");
    //Problema p("instancias/dados/INST2501.dat");
    //Problema p("instancias/dados/INST3001.dat");

    string caminho = nomeArquivo;
    //Problema p(caminho);
    //Problema p("instancias/gomesjunior/" + caminho);
    Problema p("instancias/amostra/" + caminho);

    //Problema p("instancias/dados/INST5001.dat");
    //Problema p("instancias/dados/INST7501.dat");

    //Problema p("instancias/brunorosa/INSTDT7511.dat");
    //Problema p("instancias/brunorosa/INSTDT2011.dat");

    //Populacao pop(mi, lambda, tipo, &prob, qtdEvolucao, tipoEstrategia, pctgVnd)

    //paralelo = 0;
    //Problema p("instancias/dados/INST1001.dat");
    //Problema p("instancias/gomesjunior/INST0803.dat");
    //Problema p("instancias/brunorosa/INSTDT0813.dat");
    //Problema p("instancias/novas/NI00813.dat");
    //Populacao pop(200, 20, 1, &p, 1000, 1, 20,20, start);
    //Populacao pop(200, 1000, 1, &p, 600, 1, 40, 2);
    //lambda *= mi;
    lambda = lambda/mi;
    Populacao pop(mi, lambda, 1, &p, tipoEstrategia, pctgItia, start);
    //Populacao pop(mi, lambda, 1, &p, 1, 10, start);
    pop.estrategiaEvolutiva();
    double segundos = omp_get_wtime() - start;

    //cout << endl;

    //pop.getPopulacao().front().imprimeSolucao2();
    //cout << endl;

    //pop.getPopulacao().front().itia();
    //pop.getPopulacao().front().imprimeSolucao2();
    //cout << endl;


    //Problema p("instancias/brunorosa/INSTDT0813.dat");
    //Problema p("instancias/dados/INST0004.dat"); --deixar comentado
    //Solucao solu(&p);
    //solu.ordena(0, 1);
    //solu.atualizaLista(); // necessario para o arquivo 0004 pois nao usa o ordena --deixar comentado
    //solu.gerarLinhaDoTempo();
    // a funcao imprimeSolucao está errada
    //solu.imprimeSolucao2();
    //cout << "Custo: " << solu.getCusto(); --deixar comentado


    /*cout << endl;
    cout << "Após ITIA";
    cout << endl;

    solu.itia();
    solu.imprimeSolucao2();
    //cout << "Custo: " << solu.getCusto();
    cout << endl;
    cout << endl;*/



    //comentado aqui
    //cout << nomeArquivo << ";" << mi << ";" << lambda/mi << ";" << qtdEvolucao << ";" << tipoEstrategia << ";" << pctgVnd << ";";

    //novo
    //cout << nomeArquivo << ";" << mi << ";" << lambda << ";" << qtdEvolucao << ";" << tipoEstrategia << ";" << pctgVnd << ";";
    cout << nomeArquivo << ";" << mi << ";" << lambda * mi << ";" << tipoEstrategia << ";" << pctgItia << ";";

    //imprime em qual evolucao parou
    cout << pop.getPopulacao().front().getNumeroEvolucao();
    cout << ";";

    // imprime o custo
    cout << pop.getPopulacao().front().getCusto();
    cout << ";";


    //cout << endl;
    //high_resolution_clock::time_point t2 = high_resolution_clock::now();
    //auto duracao = duration_cast<milliseconds>( t2 - t1 ).count();
    //float segundos = float (duracao)/1000;
    //double segundos = omp_get_wtime() - start;
    cout << segundos << endl;

    return 0;
}