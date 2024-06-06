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
