#include "render.h"
#include "raylib.h"

void DesenharTela(const EstadoJogo &jogo) {

    // Constantes
    const int LARGURA_TELA = 800;
    const int ALTURA_TELA  = 500;
    const int Y_SUPERFICIE = 180;

    // Inicialização
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Fundo
    DrawRectangle(0, 0, LARGURA_TELA, Y_SUPERFICIE, (Color){135, 206, 235, 255}); // Cèu
    DrawRectangle(0, Y_SUPERFICIE, LARGURA_TELA, ALTURA_TELA - Y_SUPERFICIE, (Color){0,51,102,255}); // Água
    DrawRectangle(0, Y_SUPERFICIE - 20, LARGURA_TELA, 20, (Color){230,242,255,255}); // Gelo

    // Texturas
    DrawTexture(jogo.texSol, 40, 30, WHITE); // Sol
    DrawTexture(jogo.texNuvem, 260, 40, WHITE); // Nuvem
    DrawTexture(jogo.texNuvem, 520, 20, WHITE); // Nuvem
    DrawTexture(jogo.texIglu, 60, Y_SUPERFICIE - jogo.texIglu.height - 10, WHITE); // Iglu
    DrawTexture(jogo.texPescador, jogo.xLinha - jogo.texPescador.width + 18, Y_SUPERFICIE - jogo.texPescador.height, WHITE); // Pescador

    // Linha da vara
    int xBase = jogo.xLinha;
    int yBase = Y_SUPERFICIE;
    int yTopo = Y_SUPERFICIE - 40;
    DrawLine(xBase, yTopo, xBase, yBase, BLACK); // Linha de fora do gelo
    int yLinha = (jogo.profundidadeLinha == -1) ? 180 : jogo.yProfundidade[jogo.profundidadeLinha];
    DrawLine(xBase, yBase, xBase, yLinha, BLACK); // Linha de dentro da água
    DrawCircle(xBase, yLinha, 6, BLACK); // Anzol

    // Peixes (toda a lógica)
    for (int i = 0; i < 3; i++) {
        const Peixe &p = jogo.peixes[i];
        if (p.capturado) {
            int yReal = yLinha - jogo.texPeixe.height/2;
            DrawTexture(jogo.texPeixe, jogo.xLinha - jogo.texPeixe.width/2, yReal, WHITE); // Exibe o peixe em cima do anzol
        } else {
            int yReal = jogo.yProfundidade[i] - jogo.texPeixe.height/2;
            DrawTexture(jogo.texPeixe, p.x, yReal, WHITE); // Exibe o peixe nadando
        }
    }

    // Contagem dos peixes
    int caixaPeixeY = Y_SUPERFICIE - 60;
    DrawRectangle(480, caixaPeixeY, 130, 50, (Color){181,101,29,255});
    DrawRectangleLines(480, caixaPeixeY, 130, 50, DARKBROWN);
    DrawText("PEIXES", 490, caixaPeixeY + 5, 18, BLACK);
    DrawText(TextFormat("%02i", jogo.qtdPeixes), 490, caixaPeixeY + 25, 20, BLACK);

    // Contagem das iscas
    DrawRectangle(620, Y_SUPERFICIE - 50, 90, 40, (Color){181,101,29,255});
    DrawRectangleLines(620, Y_SUPERFICIE - 50, 90, 40, DARKBROWN);
    DrawText("ISCAS", 630, Y_SUPERFICIE - 45, 16, BLACK);
    DrawText(TextFormat("%02i", jogo.qtdIscas), 630, Y_SUPERFICIE - 23, 18, BLACK);

    // Mensagem de tutorial do jogo
    DrawText("W/S: mover linha | ESPACO: pescar | ESC: sair", 10, 10, 18, BLACK);

    // Tela de game over
    if (jogo.gameOver) {
        DrawRectangle(0, 0, LARGURA_TELA, ALTURA_TELA, Fade(BLACK, 0.5f));
        DrawText("FIM DE JOGO", 260, 180, 40, RED);
        DrawText(TextFormat("PEIXES PESCADOS: %i", jogo.qtdPeixes), 230, 240, 30, WHITE);
        DrawText("Aperte R para reiniciar", 245, 300, 26, YELLOW);
    }

    // Encerrar jogo
    EndDrawing();
}
