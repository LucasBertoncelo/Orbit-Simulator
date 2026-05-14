#include <stdio.h>
#include <math.h>

#include <unistd.h> // Necessário para a função usleep() no Linux

// Constantes Físicas
// G = Constante Gravitacional Universal
#define G 6.67430e-11 
// Massa da Terra em kg (aproximada)
#define MASSA_TERRA 5.972e24 

// Estrutura para representar um vetor em 2D (Posição, Velocidade, Força)
typedef struct {
    double x;
    double y;
} Vetor2D;

// Estrutura para representar um Corpo Celeste ou Nave (ex: nossa cápsula)
typedef struct {
    char nome[30];
    double massa;      // em kg
    Vetor2D posicao;   // em metros (x, y)
    Vetor2D velocidade;// em metros por segundo (vx, vy)
} CorpoEspacial;

// Função para calcular a distância do corpo até o centro da Terra (0,0)
double calcular_distancia(Vetor2D pos) {
    // Teorema de Pitágoras para achar a distância da hipotenusa
    return sqrt(pos.x * pos.x + pos.y * pos.y);
}

// Função para atualizar a física do satélite a cada "tick" de tempo
// Usamos um ponteiro (*) para poder alterar o satélite original na memória
void atualizar_fisica(CorpoEspacial *satelite, double tempo_passo) {
    double r = calcular_distancia(satelite->posicao);
    
    // Evita divisão por zero caso o satélite caia exatamente no centro da Terra
    if (r == 0) return; 

    // 1. Calcula a magnitude da aceleração gravitacional
    // Fórmula: a = (G * M) / r^2
    double aceleracao = (G * MASSA_TERRA) / (r * r);

    // 2. Decompõe a aceleração nos eixos X e Y
    // O sinal negativo indica que a força está puxando de volta para a origem (0,0)
    double ax = -aceleracao * (satelite->posicao.x / r);
    double ay = -aceleracao * (satelite->posicao.y / r);

    // 3. Atualiza a velocidade do satélite (Velocidade = Velocidade Atual + Aceleração * Tempo)
    satelite->velocidade.x += ax * tempo_passo;
    satelite->velocidade.y += ay * tempo_passo;

    // 4. Atualiza a posição do satélite (Posição = Posição Atual + Velocidade * Tempo)
    satelite->posicao.x += satelite->velocidade.x * tempo_passo;
    satelite->posicao.y += satelite->velocidade.y * tempo_passo;
}

int main() {
    printf("Simulador Orbital Iniciado!\n");
    printf("Preparando os cálculos gravitacionais...\n\n");

    FILE *arquivo = fopen("telemetria_satelite.csv", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo CSV!\n");
        return 1;
    }

    fprintf(arquivo, "Tempo,PosicaoX,PosicaoY\n");

    
    CorpoEspacial satelite = {
        "Satelite-BR1",
        500.0,            // Massa muito menor: 500 kg
        {6771000.0, 0.0}, // Mesma altitude (LEO)
        {0.0, 7672.0}     // Mesma velocidade
    };

    double tempo_passo = 1.0; 
    int tempo_total = 0;

    printf("Objeto: %s | Massa: %.0f kg\n", satelite.nome, satelite.massa);
    printf("Iniciando LOOP INFINITO. Pressione [ Ctrl + C ] no terminal para encerrar!\n");
    printf("--------------------------------------------------\n");

    // while (1) cria um loop que nunca termina sozinho
    while (1) {
        atualizar_fisica(&satelite, tempo_passo);
        
        fprintf(arquivo, "%d,%.2f,%.2f\n", tempo_total, satelite.posicao.x, satelite.posicao.y);
        
        // A cada 60 "segundos" de simulação
        if (tempo_total % 60 == 0) {
            printf("Tempo: %d s | PosX: %.2f | PosY: %.2f\n", tempo_total, satelite.posicao.x, satelite.posicao.y);
            
            // Força a gravação dos dados no disco AGORA. 
            // Assim, se você der Ctrl+C, o que foi calculado até aqui tá salvo no CSV!
            fflush(arquivo); 
        }

        tempo_total += 1;

        // Pausa o programa por 1.000 microssegundos (0.001 segundos)
        // Isso simula o tempo passando rápido, mas impede que seu computador trave
        usleep(1000); 
    }

    // O programa nunca vai chegar nesta linha por causa do while(1), 
    // mas deixamos aqui por boas práticas.
    fclose(arquivo);
    
    return 0;
}