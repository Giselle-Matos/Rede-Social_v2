#include <string.h>
#include <stdio.h>
#include <stdlib.h>
// #include <ncurses.h>
#include "rede_social.h"

void Exibir_menu(int *choice_menu, struct dados_user *usuario_logado, int *login_sucesso, struct dados_user **lista_usuarios)
{
    printf("Menu: \n1 - Perfil\n2 - Mural\n3 - Lista de amigos\n4 - Mensagens\n5 - Trocar senha\n6 - Grupos\n7 - Log-out\nSua escolha:");
    scanf("%d", &*choice_menu);
    switch (*choice_menu)
    {
    case 1:
        Exibe_perfil(usuario_logado, lista_usuarios);
        break;
    case 2:
        Exibe_mural(usuario_logado);
        break;
    case 3:
        Main_friendlist(usuario_logado, lista_usuarios);
        break;
    case 4:
        break;
    case 5:
        Troca_senha(usuario_logado);
        break;
    case 6:
        break;
    case 7:
        *login_sucesso = 0;
        *choice_menu = 0;
        printf("Deslogando...\n");
        break;
    }
    // Reinicializar a variável choice_menu para 1 após o logout
    if (*choice_menu == 0)
    {
        *choice_menu = 1;
    }
}
