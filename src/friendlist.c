#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rede_social.h"

// 3 - criar funcionalidade de ver a lista de amigos dele
// 4 -  implementar algoritmo de ordenação da lista de amizade por ordem alfabeta
// obs: implementar o algoritmo mais eficiente!

void Listar_amigos(struct dados_user *usuario_logado)
{
    printf("Lista de amigos de %s:\n", usuario_logado->nome_user);
    struct dados_user *amigo = usuario_logado->lista_amigos;
    // amigo->prox = NULL;
    while (amigo != NULL)
    {
        printf("- %s\n", amigo->nome_user);
        amigo = amigo->prox;
    }
}

void Remove_amigo(struct dados_user *usuario_logado, char *username_friend)
{
    struct dados_user *amigo = usuario_logado->lista_amigos;
    struct dados_user *anterior = NULL;
    // se o usuario da lista de amigos é o primeiro da lista:
    if (amigo != NULL && strcmp(amigo->nome_user, username_friend) == 0)
    {
        usuario_logado->lista_amigos = amigo->prox;
        free(amigo);
        printf("Amigo removido com sucesso!\n");
        return;
    }
    // se nao, procura
    while (amigo != NULL && strcmp(amigo->nome_user, username_friend) != 0)
    {
        anterior = amigo;
        amigo = amigo->prox;
    }
    // se o amigo foi encontrado, remove
    if (amigo != NULL)
    {
        anterior->prox = amigo->prox;
        free(amigo);
        printf("Amigo removido com sucesso!\n");
    }
    else
    {
        printf("Usuario nao encontrado.\n");
    }
}

void Union(struct dados_user *rep1, struct dados_user *rep2)
{
    if (rep1->rank > rep2->rank)
    {
        rep2->parent = rep1;
    }
    else if (rep1->rank < rep2->rank)
    {
        rep1->parent = rep2;
    }
    else
    {
        rep2->parent = rep1;
        rep1->rank++;
    }
}

void Make_set(struct dados_user **lista_usuarios)
{
    struct dados_user *atual = *lista_usuarios;

    while (atual != NULL)
    {
        atual->parent = atual;
        atual->rank = 0;
        atual->size = 1;
        atual = atual->prox;
    }
}
struct dados_user *Find_set(struct dados_user *usuario)
{
    if (usuario != usuario->parent)
        usuario->parent = Find_set(usuario->parent);
    return usuario->parent;
}

void Find_friendship(struct dados_user *usuario_logado, char *username_friend, struct dados_user **lista_usuarios)
{
    // Verifica se o usuário logado está tentando adicionar a si mesmo como amigo
    if (strcmp(usuario_logado->nome_user, username_friend) == 0)
    {
        printf("Você não pode adicionar a si mesmo como amigo.\n");
        return;
    }

    struct dados_user *atual = *lista_usuarios;
    struct dados_user *user_found = NULL;

    while (atual != NULL)
    { // verifica se o usuario existe
        if (strcmp(atual->nome_user, username_friend) == 0)
        {
            printf("Usuário encontrado!\n");
            user_found = atual;
            break;
        }
        atual = atual->prox;
    }

    if (user_found == NULL)
    {
        printf("Usuário NÃO encontrado.\n");
        return;
    }

    // Verifica se o usuário já é amigo
    struct dados_user *amigo = usuario_logado->lista_amigos;
    while (amigo != NULL)
    {
        if (amigo == user_found)
        {
            printf("Vocês já são amigos!\n");
            return;
        }
        amigo = amigo->prox;
    }

    // Realiza a união dos conjuntos
    struct dados_user *rep1 = Find_set(user_found);
    struct dados_user *rep2 = Find_set(usuario_logado);
    if (rep1 != rep2)
    {
        Union(rep1, rep2);
        printf("Agora vocês são amigos!\n");

        // Adiciona o amigo à lista de amigos do usuário logado
        struct dados_user *novo_amigo = (struct dados_user *)malloc(sizeof(struct dados_user));
        strcpy(novo_amigo->nome_user, user_found->nome_user);
        novo_amigo->lista_amigos = NULL;
        novo_amigo->prox = usuario_logado->lista_amigos;
        usuario_logado->lista_amigos = novo_amigo;

        // Adiciona o usuário logado à lista de amigos do usuário encontrado
        novo_amigo = (struct dados_user *)malloc(sizeof(struct dados_user));
        strcpy(novo_amigo->nome_user, usuario_logado->nome_user);
        novo_amigo->lista_amigos = NULL;
        novo_amigo->prox = user_found->lista_amigos;
        user_found->lista_amigos = novo_amigo;
    }
}

void Adiciona_amigo(struct dados_user *usuario_logado, struct dados_user **lista_usuarios, char *username_friend)
{
    Find_friendship(usuario_logado, username_friend, lista_usuarios);
}

void Main_friendlist(struct dados_user *usuario_logado, struct dados_user **lista_usuarios)
{
    int friend_choice;
    int friend_control = 0;
    char username_friend[50];

    Make_set(lista_usuarios);

    while (friend_control == 0)
    {
        printf("\nLista de Amigos\n\n[1] Adicionar Amigos\n[2] Listar amigos\n[3] Remover amigos\n[4] Voltar\nSua escolha: ");
        scanf("%d", &friend_choice);
        getchar();

        switch (friend_choice)
        {
        case 1:
            printf("Digite o nome do usuário que deseja adicionar como amigo: ");
            fgets(username_friend, sizeof(username_friend), stdin);
            username_friend[strcspn(username_friend, "\n")] = '\0';
            Adiciona_amigo(usuario_logado, lista_usuarios, username_friend);
            break;
        case 2:
            Listar_amigos(usuario_logado);
            break;
        case 3:
            printf("Digite o nome do usuario que deseja desfazer amizade: ");
            fgets(username_friend, sizeof(username_friend), stdin);
            username_friend[strcspn(username_friend, "\n")] = '\0';
            Remove_amigo(usuario_logado, username_friend);
            break;
        case 4:
            friend_control = 1;
            break;
        default:
            break;
        }
    }
}
