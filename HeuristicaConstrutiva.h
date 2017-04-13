#ifndef PSUMAA_HEURISTICACONSTRUTIVA_H
#define PSUMAA_HEURISTICACONSTRUTIVA_H

#include "Solucao.h"
#include "Job.h"

using namespace std;

class HeuristicaConstrutiva {

public:

    // Metodo parcialmente guloso Data de Entrega mais Próxima - EDD (Earliest Due Date)
    Solucao edd(const Solucao& sol);
    // Metodo guloso Data de Entrega mais Próxima - EDD (Earliest Due Date)
    Solucao edd_gulosa(const Solucao& sol);
    // Metodo parcialmente guloso Data de Entrega mais Distante - TDD (Tardiest Due Date)
    Solucao tdd(const Solucao& sol);
    // Metodo guloso Data de Entrega mais Distante - TDD (Tardiest Due Date)
    Solucao tdd_gulosa(const Solucao& sol);
    // Metodo parcialmente guloso Menor Tempo de Processamento - SPT (Shortest Processing Time)
    Solucao spt(const Solucao& sol);
    // Metodo guloso Menor Tempo de Processamento - SPT (Shortest Processing Time)
    Solucao spt_gulosa(const Solucao& sol);
    // Metodo de construcao aleatorio - Random
    Solucao aleatoria(const Solucao& sol);


};


#endif //PSUMAA_HEURISTICACONSTRUTIVA_H
