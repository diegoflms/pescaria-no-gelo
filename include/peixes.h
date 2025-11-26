#ifndef PEIXES_H
#define PEIXES_H

struct Peixe {
    int profundidade = 0;
    float x = 0;
    int direcao = 1;
    float velocidade = 160;
    bool capturado = false;
};

#endif
