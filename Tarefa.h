#ifndef PSUMAA_TAREFA_H
#define PSUMAA_TAREFA_H

#include <iostream>
using namespace std;

class Tarefa {

private:

    int id; // id da tarefa
    int tp; // tempo necessario para processamento da tarefa
    int e; // e -> earliness, data de inicio da janela
    int t; // t -> tardiness, data final da janela
    int alfa; // custo de antecipacao
    int beta; // custo de atraso
    int inicio;
    int fim;

public:

    // Construtor da classe
    Tarefa();
    Tarefa(int id, int tp, int e, int t, int alfa, int beta);

    int getId() const;

    void setId(int id);

    int getTp() const;

    void setTp(int tp);

    int getE() const;

    void setE(int e);

    int getT() const;

    void setT(int t);

    int getAlfa() const;

    void setAlfa(int alfa);

    int getBeta() const;

    void setBeta(int beta);

    int getInicio() const;

    void setInicio(int inicio);

    int getFim() const;

    void setFim(int fim);

    int getAntecipacao() const;

    int getAtraso() const;

};


#endif //PSUMAA_TAREFA_H
