#include "jogo.h"
#include "raylib.h"
#include <thread>
#include <chrono>

void ThreadMovPeixe(EstadoJogo *jogo, int index) {
    while (jogo->rodando) {
        {
            std::lock_guard<std::mutex> lock(jogo->mutexPeixes);

            Peixe &p = jogo->peixes[index];

            if (!p.capturado) {
                // Movimento baseado em passo fixo
                p.x += p.velocidade * 0.016f;  // ~60 updates/s

                if (p.x > 850)
                    p.x = -jogo->texPeixe.width;
            }
        }

        // taxa de atualização da thread (~ 60Hz)
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}
