#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rede_social.h"

void Busca_posts(struct posts **lista_posts, char busca_post_user[50])
{
    struct posts *atual = *lista_posts;
    int i = 1;
    while (atual != NULL)
    {
        if (strcmp(atual->user_post, busca_post_user) == 0)
        {
            printf("\nUser: %s - Post %d\n %s\n", atual->user_post, i, atual->postagem);
            i++;
        }
        atual = atual->prox;
    }
    if (i == 1)
    {
        printf("Nenhum post encontrado para o usuário '%s'.\n", busca_post_user);
    }
}
// mudar mostra posts para receber como entrada o nome do usuario que
// se quer pesquisar posts ou o proprio usuario logado
void Mostra_posts(struct posts **lista_posts)
{
    struct posts *atual = *lista_posts;
    int i = 1;
    while (atual != NULL)
    {
        printf("Post %d:\n %s\n", i, atual->postagem);
        i++;
        atual = atual->prox;
    }
}

void Edita_mural(struct posts **lista_posts, struct dados_user *usuario_logado)
{
    struct posts *novo_post = (struct posts *)malloc(sizeof(struct posts));
    if (novo_post == NULL)
    {
        printf("Erro ao criar novo_post");
        return;
    }
    novo_post->prox = NULL;
    strcpy(novo_post->user_post, usuario_logado->nome_user);

    getchar();
    printf("Crie seu novo post: ");
    fgets(novo_post->postagem, sizeof(novo_post->postagem), stdin);
    novo_post->postagem[strcspn(novo_post->postagem, "\n")] = '\0';

    // adicionando o novo_post a lista encadeada

    if (*lista_posts == NULL)
    {
        *lista_posts = novo_post;
    }
    else
    {
        struct posts *atual = (struct posts *)malloc(sizeof(struct posts));
        atual = *lista_posts;
        while (atual->prox != NULL)
        {
            atual = atual->prox;
        }
        atual->prox = novo_post; // adiciona no final da lista
    }
}

void Exibe_mural(struct dados_user *usuario_logado)
{
    int choice_mural, break_mural = 0;
    char busca_post_user[50];
    struct posts *lista_posts = NULL;

    while (break_mural == 0)
    {
        printf("\nSeu Mural\n-----\n");
        Mostra_posts(&(usuario_logado->posts));
        printf("\n[1] Adicionar posts \n[2] Pesquisar posts\n[3] Voltar\nSua Resposta: ");
        scanf("%d", &choice_mural);
        switch (choice_mural)
        {
        case 1:
            Edita_mural(&(usuario_logado->posts), usuario_logado);
            printf("\nPost adicionado!\n");
            break;
        case 2:
            getchar();
            printf("Digite o username para pesquisar post: ");
            fgets(busca_post_user, sizeof(busca_post_user), stdin);
            busca_post_user[strcspn(busca_post_user, "\n")] = '\0';
            Busca_posts(&(usuario_logado->posts), busca_post_user);
            break;
        case 3:
            break_mural = 1;
            break;
        default:
            printf("Opção inválida!\n");
        }
    }
}
