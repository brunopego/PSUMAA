#ifndef PSUMAA_JOB_H
#define PSUMAA_JOB_H

#include "Problema.h"

class Job {
private:
    int id; // id do job = id da tarefa
    int inicio = 0; // tempo de inicio de processamento do job/tarefa

public:

    const Tarefa* t;

    Job();

    Job(Tarefa *t, const int& id);

    Job(Tarefa *t, const int& id, const int& inicio);

    int getId() const;

    void setId(int id);

    int getInicio() const;

    void setInicio(int inicio);

    int getFim() const;

    bool operator==(const Job&  job) const;

    bool operator!=(const Job&  job) const;

    Job& operator=(Job job);

};


#endif //PSUMAA_JOB_H

