#include <iostream>
#include <random>
#include <ctime>
#include <chrono>
#include <cstdlib>
#include <cstring>

#include "Problema.h"
#include "Solucao.h"
#include "Populacao.h"


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
    int mi = 1, lambda = 1, tipo = 1, qtdEvolucao = 0, tipoEstrategia = 0, pctgVnd = 0, pctgMut = 0;

    for(int i = 1; i < argc; i++)
    {

        getParamName( pName, argv[i] );
        getParamValue( pValue, argv[i] );

        if (strcmp( pName, "paralelo" )==0)
        {
            paralelo = atoi(pValue);
            continue;
        }

        if (strcmp( pName, "nomeArquivo" )==0)
        {
            //nomeArquivo = pValue;
            nomeArquivo = std::string(pValue);
            //strcpy(nomeArquivo,pValue);
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

        if (strcmp( pName, "qtdEvolucao" )==0)
        {
            qtdEvolucao = atoi(pValue);
            continue;
        }

        if (strcmp( pName, "tipoEstrategia" )==0)
        {
            tipoEstrategia = atoi(pValue);
            continue;
        }

        if (strcmp( pName, "pctgVnd" )==0)
        {
            pctgVnd = atoi(pValue);
            continue;
        }

        if (strcmp( pName, "pctgMut" )==0)
        {
            pctgMut = atoi(pValue);
            continue;
        }

    }

    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    // Alfa =  0 -> Guloso, 1 -> totalmente aleatorio

    // semente para a funcao rand() para gerar um valor aleatorio
    //srand(1167405666);
    time_t semente = time(NULL);
    srand(semente);
    //cout << "Semente: " << semente << endl;

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
    Problema p("instancias/dados/" + caminho);

    //Problema p("instancias/dados/INST5001.dat");
    //Problema p("instancias/dados/INST7501.dat");

    //Problema p("instancias/brunorosa/INSTDT7511.dat");
    //Problema p("instancias/brunorosa/INSTDT2011.dat");

    //Populacao pop(mi, lambda, tipo, &prob, qtdEvolucao, tipoEstrategia, pctgVnd)

    //Populacao pop(200,5000,1,&p);
    //paralelo = 0;
    //Populacao pop(50, 3000, 1, &p, 150, 1, 20);
    //Populacao pop(200, 1000, 1, &p, 600, 1, 40, 2);
    lambda *= mi;
    Populacao pop(mi, lambda, 1, &p, qtdEvolucao, tipoEstrategia, pctgVnd, pctgVnd);
    if(paralelo){
        pop.estrategiaEvolutivaParalela();
    } else{
        pop.estrategiaEvolutiva();
    }

    //cout << endl;

    //pop.getPopulacao().front().imprimeSolucao();
    //cout << endl;

    pop.getPopulacao().front().itia();
    //pop.getPopulacao().front().imprimeSolucao();
    //cout << endl;

    //cout << "Instancia" << ";" << "Mi" << ";" << "Lambda" << ";" << "N de Evolucoes" << ";" << "Tipo da Estrategia" << ";" << "% VND" << ";" << "% Mutacao"<< ";" << "Paralelo" << endl;
    cout << nomeArquivo << ";" << mi << ";" << lambda << ";" << qtdEvolucao << ";" << tipoEstrategia << ";" << pctgVnd << ";" << pctgMut << ";" << paralelo << ";";
    //cout << nomeArquivo << ";" << mi << ";" << lambda << ";" << qtdEvolucao << ";" << tipoEstrategia << ";" << pctgVnd << ";" << paralelo << ";";

    // imprime o custo
    cout << pop.getPopulacao().front().getCusto();
    cout << ";";

    //cout << endl;
    //pop.getPopulacao().front().addoip();
    //pop.getPopulacao().front().imprimeSolucao();


    //cout << endl;
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duracao = duration_cast<milliseconds>( t2 - t1 ).count();
    float segundos = float (duracao)/1000;
    cout << segundos << endl;

    return 0;
}