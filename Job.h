#ifndef PSUMAA_JOB_H
#define PSUMAA_JOB_H


class Job {
private:
    int id; // id do job = id da tarefa
    int inicio; // tempo de inicio de processamento do job/tarefa

public:

    Job();

    Job(const int& id);

    Job(const int& id, const int& inicio);

    int getId() const;

    void setId(int id);

    int getInicio() const;

    void setInicio(int inicio);


};


#endif //PSUMAA_JOB_H
