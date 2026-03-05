#ifndef FILMES_H
#define FILMES_H

#include <stdio.h>
#include <stdlib.h>



/*-----------------filmes-------------*/
typedef struct filme{
    char nome[30];
    char categoria[30];
}Filme;

//lista de filmes
struct elementoFilmes{
    struct elementoFilmes *prox;
    Filme dados;
    struct elementoFilmes *ant;
};
typedef struct elementoFilmes* ListaFilmes;
typedef struct elementoFilmes ElementoFilmes;

/*-----------------users-------------*/


typedef struct user{
    char nome[30];
    ListaFilmes liFilmes;
}User;


typedef struct elementoUser* ListaUsers;

struct elementoUser{
    struct elementoUser *prox;
    User dados;
    struct elementoUser *ant;
};
typedef struct elementoUser ElementoUser;



//----------utilizado nas funções de filme mais assistido e assistido por mais de 1
typedef struct {
    char nome[30];
    int qtd;
}Contabilizador;










/*-----------------funções-------------*/

ListaUsers* cria_listaU();

void libera_listaU(ListaUsers* li);
void inserir_usuario(ListaUsers *li);
void listar_users(ListaUsers* li);
void remover_usuario(ListaUsers* li);
void inserir_filme(ListaUsers *li);
void listar_filmes(ListaUsers* li);
void assistiram_ao_filme(ListaUsers* li);
void listar_mais_assistidos(ListaUsers *li);
void listar_por_categoria(ListaUsers* li);



#endif

