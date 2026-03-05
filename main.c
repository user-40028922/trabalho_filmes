#include <stdio.h>
#include <stdlib.h>
#include "filmes.h"

int main()
{
    int opcao=0,opcaosec=-1;
    /*-----------declarando lista------------*/
    ListaUsers *liUsers;

    /*-----------criando lista------------*/
    liUsers= cria_listaU();

    do{
        printf("\n-------------------------------------------------------------------\n");
        printf("selecione a opcao:\n 0: Sair\n 1: opcoes usuario\n 2: opcoes filme\n");
        scanf("%d",&opcao);

        switch (opcao){
            case 0:
                break; //sair

            case 1://opcoes usuarios
                printf("selecione a opcao:\n 1: Cadastrar Usuario\n 2: Remover usuario\n 3: Cadastrar filme assistido pelo usuario\n 4: Listar usuarios\n");
                scanf("%d", &opcaosec);

                switch (opcaosec){
                    case 1:
                        inserir_usuario(liUsers);
                        break;
                    case 2:
                        listar_users(liUsers);
                        remover_usuario(liUsers);
                        break;
                    case 3:
                        inserir_filme(liUsers);
                        break;
                    case 4:
                        listar_users(liUsers);
                        break;
                }
                break;

            case 2://opcao filmes
                printf("selecione a opcao:\n 1: Listar Filmes assistido pelo usuario\n 2: Listar por categoria\n 3: listar os mais assistidos\n 4: Listar usuarios que assistiram o filme\n");
                scanf("%d", &opcaosec);

                switch (opcaosec){
                    case 1:
                        listar_users(liUsers);
                        listar_filmes(liUsers);
                        break;
                    case 2:
                        listar_por_categoria(liUsers);
                        break;
                    case 3:
                        listar_mais_assistidos(liUsers);
                        break;
                    case 4:
                        assistiram_ao_filme(liUsers);
                        break;
                }

                break;

        }

    }while(opcao != 0);

    /*-----------liberando lista------------*/
    libera_listaU(liUsers);

    return 0;
}

