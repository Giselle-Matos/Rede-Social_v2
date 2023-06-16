#include <stdio.h>
#include <stdlib.h>
#include "rede_social.h"

/**
 * Função main: Função principal em que é mostrado um menu inicial ao usuário mostrando
 * opções de criar uma conta, logar em uma conta existente ou sair do programa.
 * Caso o usuario selecione a opção "criar uma conta", é direcionado a pagina da função Criar_conta();
 * Caso o usuario selecione a opção "Logar em uma conta existente", é direcionado a função Login();
 */
struct dados_user *usuario_logado = NULL;

int main(void)
{

	struct dados_user *lista_usuarios = (struct dados_user *)malloc(sizeof(struct dados_user));
	lista_usuarios = NULL;

	int choice_inicio, login_sucesso = 0, choice_menu = 1, choice_main = 1;
	while (choice_main != 0)
	{ // criar um loop infinito proposital
		printf("\nBem-Vindo a Rede Social!\n");
		printf("Selecione uma opção:\n\n1 - Criar uma conta\n2 - Logar em uma conta existente\n3 - Sair\nSua resposta: ");
		scanf("%d", &choice_inicio);
		getchar(); // Consumir o caractere de nova linha pendente

		switch (choice_inicio)
		{
		case 1:
			printf("Vamos criar uma conta!\n");
			Criar_conta(&lista_usuarios);

			printf("\nDeseja logar? [S=1/N=0]\n");
			scanf("%d", &choice_inicio);
			getchar(); // Consumir o caractere de nova linha pendente
			if (choice_inicio == 0)
			{
				break;
			}

		case 2:
			printf("Olá! Vamos fazer o login\n");
			printf("Pressione qualquer tecla para continuar");
			Login(&lista_usuarios, &login_sucesso, &usuario_logado);
			break;
		case 3:
			Liberar_usuarios(&lista_usuarios);
			login_sucesso = 0;
			printf("Saindo...\n");
			return 0;
		default:
			printf("Opção inválida!\n");
			break;
		}

		while (login_sucesso == 1 && choice_menu != 0)
		{

			Exibir_menu(&choice_menu, usuario_logado, &login_sucesso, &lista_usuarios);
		}
	}
	return 0;
}