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

void exibirPlaylist(Playlist *playlist, Musica *musicaAtual) {
    if (!playlist->cabeca) {
        printf("Playlist vazia.\n");
        return;
    }
    Musica *atual = playlist->cabeca;
    do {
        if (atual == musicaAtual) {
            printf("** %s - %s **\n", atual->artista, atual->nome);
        } else {
            printf("%s - %s\n", atual->artista, atual->nome);
        }
        atual = atual->proxima;
    } while (atual != playlist->cabeca);
    printf("\n");
}

void exibirPlaylistOrdenada(ListaOrdenada *listaOrdenada, Musica *musicaAtual) {
    if (!listaOrdenada->cabeca) {
        printf("Playlist vazia.\n");
        return;
    }
    NoOrdenado *atual = listaOrdenada->cabeca;
    while (atual) {
        Musica *musicaAtualOrdenada = atual->musica;
        if (musicaAtualOrdenada == musicaAtual) {
            printf("** %s - %s **\n", musicaAtualOrdenada->artista, musicaAtualOrdenada->nome);
        } else {
            printf("%s - %s\n", musicaAtualOrdenada->artista, musicaAtualOrdenada->nome);
        }
        atual = atual->proximo;
    }
    printf("\n");
}

void capitalizar(char *str) {
    int proximaMaiuscula = 1;
    while (*str) {
        if (isspace(*str)) {
            proximaMaiuscula = 1;
        } else if (proximaMaiuscula && isalpha(*str)) {
            *str = toupper(*str);
            proximaMaiuscula = 0;
        } else {
            *str = tolower(*str);
        }
        str++;
    }
}

void buscarMusica(Playlist *playlist, char* nome) {
    if (!playlist->cabeca) {
        printf("Playlist vazia.\n");
        return;
    }

    Musica *atual = playlist->cabeca;
    do {
        if (strcasecmp(atual->nome, nome) == 0) {
            printf("Musica encontrada: %s - %s\n", atual->artista, atual->nome);
            printf("\n");
            return;
        }
        atual = atual->proxima;
    } while (atual != playlist->cabeca);
    printf("Musica nao encontrada.\n");
    printf("\n");
}
