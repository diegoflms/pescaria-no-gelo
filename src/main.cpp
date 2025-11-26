#include "raylib.h"
#include "jogo.h"
#include "render.h"

int main() {

    // Iniciar o jogo
    InitWindow(800, 500, "Jogo de Pesca - Trabalho SO");
    SetTargetFPS(60);
    EstadoJogo jogo;
    InicializarJogo(jogo);

    // Jogo executando
    while (!WindowShouldClose()) {
        AtualizarJogo(jogo);
        DesenharTela(jogo);
    }

    // Encerrar threads e o jogo
    jogo.rodando = false;
    for (int i = 0; i < 3; i++)
        if (jogo.threadsPeixes[i].joinable())
            jogo.threadsPeixes[i].join();
    CloseWindow();
    return 0;
}
