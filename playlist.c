#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "playlist.h"

Musica* criarMusica(char* artista, char* nome) {
    Musica* nova = (Musica*)malloc(sizeof(Musica));
    strcpy(nova->artista, artista);
    strcpy(nova->nome, nome);
    nova->proxima = nova->anterior = nova;
    return nova;
}

void inicializarListaOrdenada(ListaOrdenada *listaOrdenada) {
    listaOrdenada->cabeca = NULL;
}

void inserirNaListaOrdenada(ListaOrdenada *listaOrdenada, Musica *musica) {
    NoOrdenado *novoNo = (NoOrdenado*)malloc(sizeof(NoOrdenado));
    novoNo->musica = musica;
    novoNo->proximo = NULL;

    if (!listaOrdenada->cabeca || strcmp(musica->nome, listaOrdenada->cabeca->musica->nome) < 0) {
        novoNo->proximo = listaOrdenada->cabeca;
        listaOrdenada->cabeca = novoNo;
    } else {
        NoOrdenado *atual = listaOrdenada->cabeca;
        while (atual->proximo && strcmp(musica->nome, atual->proximo->musica->nome) >= 0) {
            atual = atual->proximo;
        }
        novoNo->proximo = atual->proximo;
        atual->proximo = novoNo;
    }
}
