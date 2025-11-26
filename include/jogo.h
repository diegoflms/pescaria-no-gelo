#ifndef JOGO_H
#define JOGO_H

#include <raylib.h>
#include <mutex>
#include <semaphore>
#include <thread>
#include "peixes.h"

struct EstadoJogo {

    // Threads dos peixes
    std::thread threadsPeixes[3];
    bool rodando = true;

    // Mutex dos peixes
    std::mutex mutexPeixes;

    // Semáforo da vara
    std::binary_semaphore semaforoLinha{1};

    // Peixes em si
    Peixe peixes[3];

    // Linha da vara
    int profundidadeLinha = -1;
    int yProfundidade[3] = {260, 340, 420};
    int xLinha = 800/2;

    // Contadores iniciais
    int qtdPeixes = 0;
    int qtdIscas = 5;

    // Estados
    bool carregandoPeixe = false;
    int peixeCapturadoIndex = -1;
    bool gameOver = false;

    // Texturas
    Texture2D texSol;
    Texture2D texNuvem;
    Texture2D texIglu;
    Texture2D texPescador;
    Texture2D texPeixe;
};

// Funções
void ThreadMovPeixe(EstadoJogo *jogo, int index);
void InicializarJogo(EstadoJogo &jogo);
void AtualizarJogo(EstadoJogo &jogo);

#endif
