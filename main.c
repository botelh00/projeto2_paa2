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

    while(){
        fscanf(arquivo, "%d", destino);
        fscanf(arquivo, "%d", tempo);
    }

}

void rota_mais_rapida(Mapa *m, int *T, int *R){}

void imprimir_rotas(Mapa *m, int *T, int *R){}

void liberar_memoria(Mapa *m, int *T, int *R){}