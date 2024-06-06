#ifndef PLAYLIST_H
#define PLAYLIST_H
#define MAX_LEN 100

typedef struct Musica {
    char artista[MAX_LEN];
    char nome[MAX_LEN];
    struct Musica *proxima;
    struct Musica *anterior;
} Musica;

typedef struct {
    Musica *cabeca;
} Playlist;

typedef struct NoOrdenado {
    Musica *musica;
    struct NoOrdenado *proximo;
} NoOrdenado;

typedef struct {
    NoOrdenado *cabeca;
} ListaOrdenada;

Musica* criarMusica(char* artista, char* nome);
void inicializarListaOrdenada(ListaOrdenada *listaOrdenada);
void inserirNaListaOrdenada(ListaOrdenada *listaOrdenada, Musica *musica);
void salvarNoArquivo(Playlist *playlist, const char* nomeArquivo);
void carregarMusicas(Playlist *playlist, const char* nomeArquivo, ListaOrdenada *listaOrdenada);
void exibirPlaylist(Playlist *playlist, Musica *musicaAtual);
void exibirPlaylistOrdenada(ListaOrdenada *listaOrdenada, Musica *musicaAtual);
void capitalizar(char *str);
void buscarMusica(Playlist *playlist, char* nome);
Musica* removerMusica(Playlist *playlist, char* nome, Musica *musicaAtual);
void inserirMusica(Playlist *playlist, ListaOrdenada *listaOrdenada, char* artista, char* nome);
Musica* avancarMusica(Musica *musicaAtual);
Musica* voltarMusica(Musica *musicaAtual);
void exibirMenu(Musica *musicaAtual);

#endif
