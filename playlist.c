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

void salvarNoArquivo(Playlist *playlist, const char* nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    Musica *atual = playlist->cabeca;
    if (atual) {
        do {
            fprintf(arquivo, "%s;%s\n", atual->artista, atual->nome);
            atual = atual->proxima;
        } while (atual != playlist->cabeca);
    }
    fclose(arquivo);
}

void carregarMusicas(Playlist *playlist, const char* nomeArquivo, ListaOrdenada *listaOrdenada) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    char linha[MAX_LEN * 2];
    while (fgets(linha, sizeof(linha), arquivo)) {
        char *artista = strtok(linha, ";");
        char *nome = strtok(NULL, "\n");
        if (artista && nome) {
            Musica *nova = criarMusica(artista, nome);
            inserirNaListaOrdenada(listaOrdenada, nova);
            if (!playlist->cabeca) {
                playlist->cabeca = nova;
            } else {
                Musica* cauda = playlist->cabeca->anterior;
                cauda->proxima = nova;
                nova->anterior = cauda;
                nova->proxima = playlist->cabeca;
                playlist->cabeca->anterior = nova;
            }
        }
    }
    fclose(arquivo);
}
