#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rede_social.h"

struct dados_user *Pesquisa_perfil(struct dados_user **lista_usuarios)
{
    char nome_user_search[50];
    printf("Digite o nome do usuario que quer encontrar: ");
    scanf("%s", nome_user_search);
    getchar();

    struct dados_user *atual = *lista_usuarios;
    while (atual != NULL)
    {
        if (strcmp(atual->nome_user, nome_user_search) == 0)
        {
            printf("\nUsuário encontrado!\n");
            return atual;
        }
        atual = atual->prox;
    }
    printf("Usuário NAO encontrado!\n");
    return NULL;
}

void Edita_perfil(struct dados_user *usuario_logado)
{
    int edit_perfil;
    // mudando o nome completo
    printf("Alterar o nome?[S=1/N=0]\nSua escolha: ");
    scanf("%d", &edit_perfil);
    if (edit_perfil == 1)
    {
        getchar();
        printf("Digite o nome: ");
        fgets(usuario_logado->nome_completo_user, sizeof(usuario_logado->nome_completo_user), stdin);
        usuario_logado->nome_completo_user[strcspn(usuario_logado->nome_completo_user, "\n")] = '\0'; // Remove o '\n' da string
    }
    // mudando o
    printf("Alterar ocupação social?[S=1/N=0]\nSua escolha: ");
    scanf("%d", &edit_perfil);
    if (edit_perfil == 1)
    {
        getchar();
        printf("Digite sua ocupação social: ");
        fgets(usuario_logado->ocupacao_social_user, sizeof(usuario_logado->ocupacao_social_user), stdin);
        usuario_logado->ocupacao_social_user[strcspn(usuario_logado->ocupacao_social_user, "\n")] = '\0'; // Remove o '\n' da string
    }
    printf("Alterar endereço?[S=1/N=0]\nSua escolha: \n");
    scanf("%d", &edit_perfil);
    if (edit_perfil == 1)
    {
        getchar();
        printf("Digite seu endereço: ");
        fgets(usuario_logado->endereco_user, sizeof(usuario_logado->endereco_user), stdin);
        usuario_logado->endereco_user[strcspn(usuario_logado->endereco_user, "\n")] = '\0'; // Remove o '\n' da string
    }
    printf("Alterar biografia?[S=1/N=0]\nSua escolha: \n");
    scanf("%d", &edit_perfil);
    if (edit_perfil == 1)
    {
        getchar();
        printf("Digite sua biografia: ");
        fgets(usuario_logado->biografia_user, sizeof(usuario_logado->biografia_user), stdin);
        usuario_logado->biografia_user[strcspn(usuario_logado->biografia_user, "\n")] = '\0'; // Remove o '\n' da string
    }
}

void Exibe_perfil(struct dados_user *usuario_logado, struct dados_user **lista_usuarios)
{
    int edit_perfil;
    printf("Perfil\n");
    printf("[1] Nome: %s\n", usuario_logado->nome_completo_user);
    printf("[2] Ocupação social: %s\n", usuario_logado->ocupacao_social_user);
    printf("[3] Endereço: %s\n", usuario_logado->endereco_user);
    printf("[4] Biografia: %s\n", usuario_logado->biografia_user);
    printf("Digite 1 para editar o perfil\nDigite 2 para pesquisar perfis de outros usuarios\nDigite 0 para sair\n");
    scanf("%d", &edit_perfil);
    if (edit_perfil == 1)
    {
        Edita_perfil(usuario_logado);
        printf("Perfil editado!\n");
        printf("[1] Nome: %s\n", usuario_logado->nome_completo_user); // mudar essa parte para uma função
        printf("[2] Ocupação social: %s\n", usuario_logado->ocupacao_social_user);
        printf("[3] Endereço: %s\n", usuario_logado->endereco_user);
        printf("[4] Biografia: %s\n", usuario_logado->biografia_user);
    }
    if (edit_perfil == 2)
    {
        struct dados_user *busca_perfil = Pesquisa_perfil(lista_usuarios);
        if (busca_perfil != NULL)
        {
            printf("Nome de usuário: %s\nNome: %s\nOcupação social: %s\nEndereço: %s\nBiografia: %s\n",
                   busca_perfil->nome_user, busca_perfil->nome_completo_user, busca_perfil->ocupacao_social_user,
                   busca_perfil->endereco_user, busca_perfil->biografia_user);
        }
        // pesquisar perfis, passar usuario logado como parametro
    }
}
