
#include "filmes.h"
#include <stdlib.h>
#include <string.h>

/*---------------cria lista---------------------------------*/
ListaUsers* cria_listaU(){
    ListaUsers* li = (ListaUsers*) malloc(sizeof(ListaUsers));
    if(li!=NULL)
        *li=NULL;
  //  printf("lista  users criada com sucesso!\n");
    return li;

}


/*---------------exclui lista---------------------------------*/


void libera_listaU(ListaUsers* li) {
    if (li == NULL) return;

    ElementoUser* noU;
    while ((*li) != NULL) {
        noU = *li;
        *li = (*li)->prox;

        // Limpa a lista de filmes interna deste usuário
        ElementoFilmes* auxF = noU->dados.liFilmes;
        while (auxF != NULL) {
            ElementoFilmes* noF = auxF;
            auxF = auxF->prox;
            free(noF); // Libera cada nó de filme assistido
        }

        free(noU); // Libera o nó do usuário
    }
    free(li);
}

/*---------------inserir na lista---------------------------------*/
void inserir_usuario(ListaUsers *li){
    char nome[30];
    if (li==NULL)
        return;
    printf("qual o nome do usuario: ");
    scanf(" %29[^\n]", nome);

    ElementoUser *vernome = *li; // ver se ja tem o nome cadastrado
    while (vernome != NULL) {
        if (strcasecmp(nome, vernome->dados.nome) == 0) {
            printf("\n O usuario '%s' ja esta cadastrado!\n", nome);
            return; // Encerra a função sem criar um novo nó
        }
        vernome = vernome->prox;
    }

    ElementoUser* no= (ElementoUser*) malloc (sizeof(ElementoUser));//alocando nó
    if(no==NULL)
            return;


    //copiando os dados para o nó, e atribuindo o proximo para o começo da lista
    strcpy(no->dados.nome, nome);

    //null para **filmesAssistidos
    no->dados.liFilmes = NULL;
    no->prox = (*li);
    no->ant = NULL;
    // se já tiver nó na lista, o ponteiro anterior vai receber este novo nó
    if(*li != NULL)
        (*li)->ant=no;
    //faz a lista apontar para este novo nó
    *li=no;

    printf("\nusuario %s cadastrado com sucesso!\n", no->dados.nome);

}


void remover_usuario(ListaUsers* li) {
    if (li == NULL || *li == NULL) {
        printf("\nSem usuarios cadastrados.\n");
        return;
    }

    char nome[30];
    printf("Digite o nome do usuario a ser removido: ");
    scanf(" %29[^\n]", nome);

    ElementoUser *noU = *li;

    //procurando usuario
    while (noU != NULL && strcasecmp(nome, noU->dados.nome) != 0) {
        noU = noU->prox;
    }

    if (noU == NULL) {
        printf("Usuario nao encontrado!\n");
        return;
    }

    //limpando a lista de filmes
    ElementoFilmes *auxF = noU->dados.liFilmes;
    while (auxF != NULL) {
        ElementoFilmes *tempF = auxF;
        auxF = auxF->prox;
        free(tempF);
    }


    if (noU->ant == NULL) {
        //vendo se é o primeiro
        *li = noU->prox;
    } else {
        // Se não for o primeiro, o anterior aponta para o próximo de noU
        noU->ant->prox = noU->prox;
    }

    if (noU->prox != NULL) {
        // Se houver um próximo, ele aponta de volta para o anterior de noU
        noU->prox->ant = noU->ant;
    }

    free(noU); // liberando usuario
    printf("Usuario '%s' e seu historico foram removidos!\n", nome);
}


void inserir_filme(ListaUsers *li){
    if (li == NULL || *li == NULL) {
        printf("Cadastre usuarios primeiro!\n");
        return;
    }

    char nomeU[30], nomeF[30], categoriaF[30];
    printf("Digite o nome do usuario escolhido: ");
    scanf(" %29[^\n]", nomeU);

    // busca usuario
    ElementoUser *noU = *li;
    while (noU != NULL && strcasecmp(nomeU, noU->dados.nome) != 0) {
        noU = noU->prox;
    }

    if (noU == NULL) {
        printf("Usuario nao encontrado!\n");
        return;
    }

    printf("Qual o nome do filme: ");
    scanf(" %29[^\n]", nomeF);

    // não deixando cadastrar mais de 1 filme com o mesmo nome por usuario
    ElementoFilmes *vernome = noU->dados.liFilmes;
    while (vernome != NULL) {
        if (strcasecmp(nomeF, vernome->dados.nome) == 0) {
            printf("\n O filme %s ja foi assistido por: %s\n", nomeF, nomeU);
            return;
        }
        vernome = vernome->prox;
    }

    printf("Qual a categoria do filme: ");
    scanf(" %29[^\n]", categoriaF);

    // alocando o filme
    ElementoFilmes* no = (ElementoFilmes*) malloc(sizeof(ElementoFilmes));
    if (no == NULL) return;

    strcpy(no->dados.nome, nomeF);
    strcpy(no->dados.categoria, categoriaF);


    // inserindo no inicio
    no->prox = noU->dados.liFilmes;
    no->ant = NULL;

    if (noU->dados.liFilmes != NULL) {
        noU->dados.liFilmes->ant = no;
    }

    noU->dados.liFilmes = no; // inicio lista

    printf("\nFilme %s cadastrado para: %s\n", no->dados.nome, noU->dados.nome);
}





/*---------------listando filmes e usuarios---------------------------------*/

void listar_users(ListaUsers* li){

    if (li == NULL || *li == NULL) {
        printf("cadastre usuarios primeiro\n");
        return;
    }

    ElementoUser *no = *li;

    while(no != NULL){
        printf("\n User: %s\n", no->dados.nome);
        no = no->prox;
    }

}

void listar_filmes(ListaUsers* li){
    char nome[30];
    if (li == NULL || *li == NULL) {
        return;
    }
    printf("informe o nome do usuario para listar filmes:\n ");
    scanf(" %29[^\n]", nome);

    ElementoUser *noU = *li;
    while (noU != NULL && strcasecmp(nome, noU->dados.nome) != 0) {
        noU = noU->prox;
    }

    if (noU == NULL) {
        printf("Usuario nao encontrado!\n");
        return;
    }


    ElementoFilmes *noF = noU->dados.liFilmes;
    int cont=0;
    while(noF != NULL){
        cont++;
        printf("\n Filmes: %s", noF->dados.nome);
        noF = noF->prox;
    }
    printf("\n foram assistidos %d filmes por esse usuario\n",cont);

}


void assistiram_ao_filme(ListaUsers* li){
    int achou=0;
    char nome[30];
    printf("informe o nome do filme:\n ");
    scanf(" %29[^\n]", nome);


    ElementoUser *noU = *li;
    while (noU != NULL ) {
        ElementoFilmes *noF = noU->dados.liFilmes;

        while(noF != NULL){
            if(strcasecmp(nome, noF->dados.nome) == 0){
                achou=1;
                printf("\n %s assistiu! \n", noU->dados.nome);
                break;

            }

            noF = noF->prox;
        }
        noU = noU->prox;
    }
    if(achou==0){
        printf("\n filme nao assistido\n");
    }

}


// a partir daqui preciosu da criação de uma novo struct nao prevista no inicio do projeto,

//essa função tenta cumprir 2 objeitos. primeiro: mostrar todos os filmes assistidos por mais de 1 usuario. segundo: mostrar o mais assistido.
//possui uma limitação, por conta do vetor, de 30 filmes amostrados.
void listar_mais_assistidos(ListaUsers *li){
    if (li == NULL || *li == NULL) {
        return;
    }

    Contabilizador vet[30];
    int enchimento = 0;

    // Inicializa o vetor
    for(int i = 0; i < 30; i++) {
        vet[i].qtd = 0;
        strcpy(vet[i].nome, "");
    }

    //navega pela lista de usuários
    ElementoUser *noU = *li;
    while (noU != NULL) {
        ElementoFilmes *noF = noU->dados.liFilmes;
        while (noF != NULL) {
            int achou = 0;

            //busca se o filme já está no vetor até o limite do enchimento, e add qtd +1
            for (int i = 0; i < enchimento; i++) {
                if (strcasecmp(noF->dados.nome, vet[i].nome) == 0) {
                    vet[i].qtd++;
                    achou = 1;
                    break;
                }
            }

            //aqui verifica se o filme é novo no vetor, e se o vetor ainda comporta, caso seja será add
            if (achou == 0 && enchimento < 30) {
                strcpy(vet[enchimento].nome, noF->dados.nome);
                vet[enchimento].qtd = 1;
                enchimento++; //incrementa o enchimento
            }
            noF = noF->prox; //passa pro proximo nó, ainda no mesmo usuario
        }
        noU = noU->prox; //passa para o prox usuario
    }

    //ordenando bubble sort -- comparando por pares -- pior case: n^2
    for (int i = 0; i < enchimento - 1; i++) { //-1 pois o bubble sort ordena por pares, além de que o maior elemento é carregado para o fim
        for (int j = 0; j < enchimento - i - 1; j++) {//rodando o vetor
            if (vet[j].qtd < vet[j+1].qtd) {
                Contabilizador aux = vet[j]; // aux para nao deixar a struct sumir
                vet[j] = vet[j+1];//inverte as posicoes
                vet[j+1] = aux;
            }
        }
    }

    // printando
    printf("\n---------------filmes mais assistidos------------- \n");
    int exibiu = 0;
    for (int i = 0; i < enchimento; i++){
        if (vet[i].qtd > 1){
            printf("%d º lugar --- %s | %d visualizacoes\n", i + 1, vet[i].nome, vet[i].qtd);
            exibiu = 1;
        }
    }

    if (exibiu == 0) {
        printf("nenhum filme possui mais que uma visualicao\n");
    }
}






//essa funçao possuia um problema: nao conseguia controla para que o mesmo filmes assistido por 2 usuarios difente nao fosse printada 2 vezes.
//solução: informar que certo filme foi assistido por certo usuario, informando o nome do usuario, desse modo nao torna tao redundante a repitição do filme na exibição

void listar_por_categoria(ListaUsers *li){
    if (li == NULL || *li == NULL) {
        return;
    }

    char cat[30];
    int achoufilmes = 0;

    printf("Digite a categoria que deseja filtrar: ");
    scanf(" %29[^\n]", cat);

    ElementoUser *noU = *li;

    printf("\n----------CATEGORIA: %s ---------\n", cat);

    // percorre usuario
    while (noU != NULL) {
        ElementoFilmes *noF = noU->dados.liFilmes;
        int exibiuUsuario = 0;

        // percorre filmes
        while (noF != NULL) {
            //compara
            if (strcasecmp(cat, noF->dados.categoria) == 0) {

                // imprime o nome do usuario apenas uma vez
                if (exibiuUsuario==0) {
                    printf("\nUsuario: %s\n", noU->dados.nome);
                    exibiuUsuario = 1;
                }

                printf(" %s\n", noF->dados.nome);
                achoufilmes = 1;
            }
            noF = noF->prox;
        }
        noU = noU->prox;
    }

    if (achoufilmes==0) {
        printf("Nenhum filme encontrado nesta categoria\n", cat);
    }

}







