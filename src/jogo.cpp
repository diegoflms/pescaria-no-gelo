#include "jogo.h"
#include "raylib.h"
#include <cmath>

void InicializarJogo(EstadoJogo &jogo) {
    jogo.profundidadeLinha = -1;
    jogo.qtdPeixes = 0;
    jogo.qtdIscas = 5;
    jogo.carregandoPeixe = false;
    jogo.peixeCapturadoIndex = -1;
    jogo.gameOver = false;

    jogo.rodando = true;

    jogo.texSol      = LoadTexture("../assets/sol.png");
    jogo.texNuvem    = LoadTexture("../assets/nuvem.png");
    jogo.texIglu     = LoadTexture("../assets/iglu.png");
    jogo.texPescador = LoadTexture("../assets/pescador.png");
    jogo.texPeixe    = LoadTexture("../assets/peixe.png");

    // velocidade inicial (difícil)
    jogo.peixes[0] = {0,  -50, 1, 220, false};
    jogo.peixes[1] = {1, -150, 1, 240, false};
    jogo.peixes[2] = {2, -300, 1, 260, false};

    // INICIAR THREADS
    for (int i = 0; i < 3; i++)
    {
        jogo.threadsPeixes[i] = std::thread(ThreadMovPeixe, &jogo, i);
    }
}

void AtualizarJogo(EstadoJogo &jogo) {

    // Reiniciar o jogo
    if (jogo.gameOver) {
        if (IsKeyPressed(KEY_R))
            InicializarJogo(jogo);
        return;
    }

    // Movimentação da linha (W/S)
    if (!jogo.carregandoPeixe) {
        if (IsKeyPressed(KEY_W) && jogo.profundidadeLinha > -1)
            jogo.profundidadeLinha--;
        if (IsKeyPressed(KEY_S) && jogo.profundidadeLinha < 2)
            jogo.profundidadeLinha++;
    } else {
        if (IsKeyPressed(KEY_W) && jogo.profundidadeLinha > -1)
            jogo.profundidadeLinha--;
    }

    // Tentativa de pesca (Barra de espaço)
    if (IsKeyPressed(KEY_SPACE) && !jogo.carregandoPeixe) {
        if (jogo.qtdIscas > 0)
            jogo.qtdIscas--;
        else {
            jogo.gameOver = true;
            return;
        }

        // Semáforo (impede pesca)
        if (!jogo.semaforoLinha.try_acquire()) {
            return;
        }
        std::lock_guard<std::mutex> lock(jogo.mutexPeixes);

        for (int i = 0; i < 3; i++) {
            Peixe &p = jogo.peixes[i];

            if (p.profundidade == jogo.profundidadeLinha) {
                if (std::abs(p.x - jogo.xLinha) < 30) {
                    p.capturado = true;
                    jogo.carregandoPeixe = true;
                    jogo.peixeCapturadoIndex = i;
                    break;
                }
            }
        }

        if (!jogo.carregandoPeixe)
            jogo.semaforoLinha.release();
    }

    // =============================================
    // SUBIR PEIXE
    // =============================================
    if (jogo.carregandoPeixe)
    {
        if (jogo.profundidadeLinha == -1)
        {
            std::lock_guard<std::mutex> lock(jogo.mutexPeixes);

            jogo.qtdPeixes++;

            Peixe &p = jogo.peixes[jogo.peixeCapturadoIndex];
            p.capturado = false;
            p.x = -GetRandomValue(50, 300);

            // todos os peixes aceleram → + dificuldade
            for (int i = 0; i < 3; i++)
                jogo.peixes[i].velocidade += 20;

            jogo.carregandoPeixe = false;
            jogo.peixeCapturadoIndex = -1;

            jogo.semaforoLinha.release();
        }
    }

    if (jogo.qtdIscas == 0 && !jogo.carregandoPeixe)
        jogo.gameOver = true;
}
