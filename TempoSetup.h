#ifndef PSUMAA_TEMPOSETUP_H
#define PSUMAA_TEMPOSETUP_H


class TempoSetup {
private:
    int tam; // tamanho da matriz - matriz quadrada [tam][tam]
    int** matriz_ts = nullptr; // matriz com o tempo de setup

public:

    TempoSetup(const int& t);
    ~TempoSetup();
    void setTempoSetup(const int& x, const int& y, const int& valor);
    int getTempoSetup(const int& x, const int& y);

};


#endif //PSUMAA_TEMPOSETUP_H
