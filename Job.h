#ifndef PSUMAA_JOB_H
#define PSUMAA_JOB_H

#include "Problema.h"

class Job {
private:
    int id; // id do job = id da tarefa
    int inicio; // tempo de inicio de processamento do job/tarefa
    Problema *prob;

public:

    Job();

    Job(Problema *prob, const int& id);

    Job(Problema *prob, const int& id, const int& inicio);

    int getId() const;

    void setId(int id);

    int getInicio() const;

    void setInicio(int inicio);

};


#endif //PSUMAA_JOB_H
