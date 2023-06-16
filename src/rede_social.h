// rede_social.h
#ifndef REDE_SOCIAL_H
#define REDE_SOCIAL_H

/*struct friendlist {
    char username[50];
    int rank;
    int parent;
    int size;
};*/

/**
 * Struct posts: struct responsavel pelo armazenamento das postagens dos usuários, formando uma
 * lista encadeada. Cada nó dessa lista encadeada contem a postagem do usuário, o nome
 * do usuario que a criou e um ponteiro para o próximo nó.
 */

struct posts
{
    char postagem[500];
    char user_post[50];
    struct posts *prox;
};

/**
 * Struct dados_user: struct responsável pelo armazenamento dos dados dos usuários, com comportamento
 * de uma lista encadeada. Cada nó da lista encadeada contem username, senha, nome completo,
 * ocupação social, endereço e biografia. Os quatro últimos são dados utilizados no perfil do
 *  usuario. Além disso, a struct contem um ponteiro para a struct posts, um ponteiro para a
 *  struct friendlist e um ponteiro para o próximo nó.
 */

struct dados_user
{
    char nome_user[50]; // atributo identificador
    char senha_user[50];
    char nome_completo_user[128];
    char ocupacao_social_user[128];
    char endereco_user[128];
    char biografia_user[501];
    int rank;
    struct dados_user *parent;
    int size;
    struct dados_user *prox;
    struct posts *posts;
    struct dados_user *lista_amigos;
};

/*!
 * extern struct dados_user *usuario_logado: declaração de nó do tipo
 * struct dados_user responsável por armazenar os dados do usuário
 * que está logado no sistema no momento.
 *
 */

extern struct dados_user *usuario_logado;

void Listar_amigos(struct dados_user *usuario_logado);

void Make_set(struct dados_user **lista_usuarios);

struct dados_user *Find_set(struct dados_user *usuario);

void Find_friendship(struct dados_user *usuario_logado, char *username_friend, struct dados_user **lista_usuarios);

void Adiciona_amigo(struct dados_user *usuario_logado, struct dados_user **lista_usuarios, char *username_friend);

void Main_friendlist(struct dados_user *usuario_logado, struct dados_user **lista_usuarios);
/*!
 * Troca_senha(): responsável pela mudança da senha do usuário. Por motivos de segurança,
 * é pedida a senha anterior do usuário antes da senha atual e a senha é ocultada enquanto
 * o usuário a insere.
 * @param struct dados_user *usuario_logado - Responsável pelo recebimento correto da nova
 * senha por usuario_logado->senha_user
 */
void Troca_senha(struct dados_user *usuario_logado);
/*!
 * Mostra_posts(): função responsável por mostrar os posts existentes associados
 * ao usuario logado no momento.
 * @param struct posts *lista_posts - Nó da lista encadeada contendo a postagem e o nome
 * usuário responsavel pela postagem
 */
void Mostra_posts(struct posts **lista_posts);
/*!
 * Busca_posts(): função responsável pela pesquisa pelo nome do usuário que deseja ser
 * buscado, informado pelo usuário que interage com o programa. A função percorre a lista
 * encadeada contendo todas as postagens do sistema e verifica se o nome do usuário informado
 * corresponde a algum nome de usuário de algum nó da lista encadeada. Caso seja igual, imprime
 * a postagem desse usuário na tela.
 * @param struct posts **lista_posts - Nó da lista encadeada contendo a postagem e o nome
 * usuário responsavel pela postagem
 * @param char busca_post_user -  utilizado na comparação com o nó da lista encadeada ao
 * percorre-la
 */
void Busca_posts(struct posts **lista_posts, char busca_post_user[50]);
/*!
 * Edita_mural(): função responsável pela alteração das postagens da lista encadeada, que ocorre
 * quando o usuário escolhe "Adicionar post". A função recebe como parametro a struct posts **lista_posts
 * e a struct dados_user *usuario_logado, de forma que seja possível percorrer a lista encadeada de postagens
 * e buscar pelo nome do usuario logado no sistema no momento. Dessa forma, apenas os posts do usuário logado
 * são mostrados na tela.
 * @param struct posts **lista_posts - nó da lista encadeada contendo a postagem e o nome do usuario responsavel
 * pela postagem
 * @param struct dados_user *usuario_logado - utilizado na comparação com o nó da lista encadeada lista_posts
 * ao percorre-la.
 */
void Edita_mural(struct posts **lista_posts, struct dados_user *usuario_logado);
/*!
 * Exibe_mural(): função responsável por mostrar ao usuario uma tela de opções.
 * O usuário pode escolher Adicionar posts, Pesquisar posts (de outros usuarios
 * ou dele proprio) ou voltar. Ao escolher alguma dessas alternativas, é direcionado
 * para uma outra tela para a execução da funcionalidade escolhida.
 */
void Exibe_mural(struct dados_user *usuario_logado);
/**
 * Pesquisa_perfil(): função responsável pela pesquisa do perfil de um determinado usuário.
 * Caso encontre o usuário, retorna o nó relacionado a esse usuário. Caso não encontre,
 * retorna NULL.
 * @param struct dados_user **lista_usuarios - utilizado para percorrer a lista encadeada
 * relacionada aos usuarios cadastrados no sistema
 */
struct dados_user *Pesquisa_perfil(struct dados_user **lista_usuarios);
/**
 * Criar_usuario(): Função responsável pela alocação de memoria para criar um novo usuário.
 * Retorna o proprio nó alocado.
 */
struct dados_user *Criar_usuario();
/**
 * Adicionar_usuario(): Função responsável por adicionar o nó alocado pela função
 * Criar_usuario() na lista encadeada lista_usuarios. Na função, é verificado se a lista está
 * vazia ou se contém algum elemento. Caso esteja vazia, o nó é adicionado na primeira posição.
 * Caso exista um ou mais elementos, a lista é percorrida até o final, onde o nó é então alocado.
 * @param struct dados_user **lista_usuarios - utilizado para percorrer a lista encadeada
 * relacionada aos usuarios cadastrados no sistema
 * @param struct dados_user *novo_user - nó alocado pela função Criar_usuario
 */
void Adicionar_usuario(struct dados_user **lista_usuarios, struct dados_user *novo_usuario);
/**
 * Liberar_usuarios(): função responsável por liberar a memoria que estava sendo ocupada pela
 * lista encadeada relacionada aos usuarios cadastrados no sistema.
 * @param struct dados_user **lista_usuarios - utilizado para percorrer a lista encadeada
 * relacionada aos usuarios cadastrados no sistema
 */
void Liberar_usuarios(struct dados_user **lista_usuarios);
/**
 * Edita_perfil(): função responsável pela mudança dos dados relacionados ao perfil do usuario
 * em struct dados_usuarios.
 * @param struct dados_user *usuario_logado - nó contendo das informações do usuario logado
 * no sistema no momento
 */
void Edita_perfil(struct dados_user *usuario_logado);
/**
 * Exibe_perfil(): Função que mostra os dados do usuario logado no momento e fornece a opção de
 * alterar as informações do perfil, pesquisar perfis ou voltar para a tela anterior.
 * @param struct dados_user *usuario_logado - nó contendo as informações do usuario logado no
 * sistema no momento
 * @param struct dados_user **lista_usuarios - nó da lista encadeada relacionada aos usuarios
 * cadastrados no sistema
 */
void Exibe_perfil(struct dados_user *usuario_logado, struct dados_user **lista_usuarios);
/**
 * Login(): Função responsável pelo login do usuário no sistema. Pede ao usuario que insira
 * seu nome de usuario e sua senha e verifica se os dados inseridos são iguais aos dados
 * de algum nó da lista encadeada relacionada aos usuarios cadastrados no sistema. Caso
 * sejam iguais a um nó, o usuário tem acesso ao sistema. Caso contrário, é informado ao
 * usuario que os dados estao incorretos.
 * @param struct dados_user **lista_usuarios -  nó da lista encadeada relacionada aos usuarios
 * cadastrados no sistema
 * @param int *login_sucesso - ponteiro para uma variavel de controle que informa se o usuário
 * está logado no sistema ou não
 * @param struct dados_user **usuario_logado - nó contendo das informações do usuario logado
 * no sistema no momento
 */

void Login(struct dados_user **lista_usuarios, int *login_sucesso, struct dados_user **usuario_logado);
/**
 * Criar_conta(): função responsável pela criação da conta do usuário. Pede ao usuário que
 * informe seu nome de usuario e senha para que seja cadastrado no sistema atraves da função
 * Adiciona_usuario().
 * @param strucr dados_user **lista_usuarios - nó da lista encadeada relacionada aos usuarios
 * cadastrados no sistema
 */
void Criar_conta(struct dados_user **lista_usuarios);
/**
 * Exibir_menu(): Função responsável pela exibição do menu principal mostrado ao usuário apos
 * o login ser efetuado com sucesso. Atraves dele, o usuario pode navegar para o perfil, mural,
 * lista de amigos, mensagens, troca de senha, grupos ou log-out.
 * @param int *choice_menu - ponteiro para uma variavel de controle para loops e switch
 * @param struct dados_user *usuario_logado - nó contendo das informações do usuario logado
 * no sistema no momento
 * @param int *login_sucesso - ponteiro para uma variavel de controle que informa se o usuario
 * esta logado no sistema ou não
 * @param struct dados_user **lista_usuarios - nó da lista encadeada relacionada aos usuarios
 * cadastrados no sistema
 */
void Exibir_menu(int *choice_menu, struct dados_user *usuario_logado, int *login_sucesso, struct dados_user **lista_usuarios);

#endif