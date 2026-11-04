//Beatriz de Assis Siqueira, RA:10741570 
//Daniel Arais Motta, RA:10419718 
// Matheus Santos Medeiros, RA:10748040 
// Pedro Araujo Botelho, RA:10738317

//Conversa com gemini: https://share.gemini.google/NEVyMziL6C8a

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int num_esquinas;
    int index_esquina;
    int **mapa;
} Mapa;

int carregar_mapa(const char *nome_arquivo, Mapa *m){
    //ler arquivo 
    FILE *arquivo = fopen(nome_arquivo, "r");
    //verificar se está vazio
    if(arquivo==NULL) return 0;

    //ler linha 1 com o destino
    fscanf(arquivo, "%d", &m->index_esquina);
    m->index_esquina -= 1;
    //ler a quantidade de esquinas
    fscanf(arquivo, "%d", &m->num_esquinas);

    m->mapa = (int**) malloc(m->num_esquinas*sizeof(int*));
    for(int i=0; i<m->num_esquinas; i++){
        m->mapa[i] = (int*) calloc(m->num_esquinas, sizeof(int));
    }
    int origem, destino, tempo;

    while(fscanf(arquivo, "%d", &origem) == 1 && origem != 0){
        fscanf(arquivo, "%d %d", &destino, &tempo);
        m->mapa[origem-1][destino-1] = tempo;

    }
    fclose(arquivo);
    return 1;

}

void rota_mais_rapida(Mapa *m, int *T, int *R){
    //criar o vetor auxiliar de esquinas
    int *E = (int*)malloc(m->num_esquinas*sizeof(int));

    for(int i=0; i < m->num_esquinas; i++){
        E[i] = 1;
        T[i] = INT_MAX;
        R[i] = -1;
    }
    T[0] = 0;
    for (int cont = 0; cont < m->num_esquinas; cont++) {
        int v = -1;
        int menor_tempo = INT_MAX;
        for(int i = 0; i < m->num_esquinas; i++) {
            if(E[i]==1 && T[i]<menor_tempo){
                menor_tempo = T[i];
                v=i;
            }
        }
        if(v==-1) {
            break;
        }
        E[v] = 0;
        for(int e=0; e < m->num_esquinas; e++) {
            if(m->mapa[v][e] > 0 && E[e] == 1) {
                if(T[e] > T[v] + m->mapa[v][e]){
                    T[e] = T[v] + m->mapa[v][e];
                    R[e] = v;
                }
            }
        }

    }
    free(E);
}

void imprimir_rotas(Mapa *m, int *T, int *R){
    int *pilha = (int*)malloc(m->num_esquinas*sizeof(int));

    int atual = m->index_esquina;
    int topo = 0;
    while(atual != -1) {
        pilha[topo] = atual;
        topo++;
        atual = R[atual];
    }
    printf("Rota até a esquina #%d: ", m->index_esquina + 1);
    for(int i = topo -1; i >=0; i--){
        printf("%d ", pilha[i]+1);
    }
    printf("\n");
    printf("Tempo calculado para rota = %d min.\n", T[m->index_esquina]);
    free(pilha);

}

void liberar_memoria(Mapa *m, int *T, int *R){
    for(int i=0; i < m->num_esquinas; i++) {
        free(m->mapa[i]);
    }
    free(m->mapa);

    free(T);
    free(R);
}

int main(){
    Mapa m;

    if(carregar_mapa("pizzaria.txt", &m) == 0) {
        return 0;
    }

    int *T = (int*)malloc(m.num_esquinas*sizeof(int));
    int *R = (int*)malloc(m.num_esquinas*sizeof(int));
    rota_mais_rapida(&m, T, R);
    imprimir_rotas(&m, T, R);
    liberar_memoria(&m, T, R);
    return 0;    
}