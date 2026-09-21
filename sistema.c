/* ============================================================
 * PROJETO: NOVA BANK - Sistema de Cadastro de Clientes
 * DISCIPLINA: Algoritmos e Praticas de Programacao
 * LINGUAGEM: C
 *
 * GRUPO: [COLOQUE AQUI OS NOMES DOS INTEGRANTES]
 *  - Integrante 1
 *  - Integrante 2
 *  - Integrante 3
 *
 * DESCRICAO:
 *  Programa em modo console que simula o cadastro e a gestao de
 *  clientes de um banco digital (Nova Bank). Permite cadastrar,
 *  listar, buscar, depositar, sacar e excluir clientes, usando
 *  um vetor de structs para armazenar os dados em memoria.
 * ============================================================ */

#include <stdio.h>
#include <string.h>

/* ---------------------- CONSTANTES ------------------------- */
#define MAX_CLIENTES 50
#define TAM_NOME 80
#define TAM_CPF 20
#define SALDO_MINIMO 0.0

/* ---------------------- ESTRUTURA DE DADOS ------------------ */
typedef struct {
    int codigo;
    char nome[TAM_NOME];
    char cpf[TAM_CPF];
    float saldo;
    int ativo;
} Cliente;

/* ---------------------- VARIAVEIS GLOBAIS -------------------- */
Cliente clientes[MAX_CLIENTES];
int totalClientes = 0;
int proximoCodigo = 1;

/* ---------------------- PROTOTIPOS DAS FUNCOES --------------- */
void exibirMenu(void);
void cadastrarCliente(void);
void listarClientes(void);
void depositar(void);
void sacar(void);
int buscarClientePorCpf(const char cpf[]);
void buscarCliente(void);
void excluirCliente(void);
void limparBufferEntrada(void);
void lerLinha(char destino[], int tamanho);

/* ======================= FUNCAO PRINCIPAL ==================== */
int main(void) {
    int opcao;

    do {
        exibirMenu();
        printf(">>> Escolha uma opcao (0-6): ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                cadastrarCliente();
                break;
            case 2:
                listarClientes();
                break;
            case 3:
                depositar();
                break;
            case 4:
                sacar();
                break;
            case 5:
                buscarCliente();
                break;
            case 6:
                excluirCliente();
                break;
            case 0:
                printf("\n========== ENCERRAMENTO ==========\n");
                printf("[MENSAGEM] Obrigado por usar o NOVA BANK!\n");
                printf("[MENSAGEM] Ate a proxima!\n");
                printf("==================================\n\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida!\n");
                printf("Digite um numero entre 0 e 6.\n\n");
        }

    } while (opcao != 0);

    return 0;
}

/* ======================= FUNCOES AUXILIARES =================== */

void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* descarta os caracteres restantes */
    }
}

void lerLinha(char destino[], int tamanho) {
    if (fgets(destino, tamanho, stdin) != NULL) {
        if (strchr(destino, '\n') == NULL) {
            limparBufferEntrada();
        }
        destino[strcspn(destino, "\n")] = '\0';
        destino[strcspn(destino, "\r")] = '\0';
    } else {
        destino[0] = '\0';
    }
}

void exibirMenu(void) {
    printf("\n================================================\n");
    printf("          NOVA BANK - SISTEMA BANCARIO         \n");
    printf("================================================\n");
    printf("\n     BEM-VINDO AO NOVA BANK!\n\n");
    printf(" O QUE VOCE DESEJA FAZER?\n\n");
    printf(" [1] Cadastrar novo cliente\n");
    printf("     Registre um novo cliente no sistema\n\n");
    printf(" [2] Listar todos os clientes\n");
    printf("     Veja informacoes de todos os clientes cadastrados\n\n");
    printf(" [3] Depositar (adicionar saldo)\n");
    printf("     Adicione dinheiro a conta de um cliente\n\n");
    printf(" [4] Sacar (retirar saldo)\n");
    printf("     Retire dinheiro da conta de um cliente\n\n");
    printf(" [5] Buscar cliente por CPF\n");
    printf("     Pesquise um cliente especifico\n\n");
    printf(" [6] Excluir cliente\n");
    printf("     Remova um cliente do sistema\n\n");
    printf(" [0] Sair do sistema\n");
    printf("     Encerre o programa\n\n");
    printf("================================================\n");
    printf(" Status: %d/%d clientes cadastrados\n", totalClientes, MAX_CLIENTES);
    printf("================================================\n\n");
}

void cadastrarCliente(void) {
    int dummy;

    if (totalClientes >= MAX_CLIENTES) {
        printf("\n[ERRO] Limite de clientes atingido!\n");
        printf("Nao e possivel cadastrar mais clientes.\n");
        printf("Capacidade maxima: %d clientes\n\n", MAX_CLIENTES);
        printf("......................................................\n\n");
        printf("[OPCAO] Digite 0 para voltar ao menu inicial: ");
        scanf("%d", &dummy);
        limparBufferEntrada();
        return;
    }

    Cliente novo;
    novo.codigo = proximoCodigo;
    novo.ativo = 1;
    novo.saldo = 0.0;

    printf("\n========== OPCAO 1: CADASTRO DE NOVO CLIENTE ==========\n");
    printf("\nPreencha os dados do novo cliente passo a passo:\n\n");
    printf("......................................................\n\n");

    printf("[PASSO 1/3] DIGITE O NOME COMPLETO\n");
    printf("Exemplo: Maria da Silva\n");
    printf(">>> Digite o nome: ");
    lerLinha(novo.nome, TAM_NOME);
    printf("\n......................................................\n\n");

    printf("[PASSO 2/3] DIGITE O CPF (SOMENTE NUMEROS)\n");
    printf("Exemplo: 12345678901\n");
    printf(">>> Digite o CPF: ");
    lerLinha(novo.cpf, TAM_CPF);
    printf("\n......................................................\n\n");

    if (strlen(novo.nome) == 0 || strlen(novo.cpf) == 0) {
        printf("[ERRO] Nome e CPF sao obrigatorios!\n");
        printf("Cadastro cancelado.\n\n");
        printf("......................................................\n\n");
        printf("[OPCAO] Digite 0 para voltar ao menu inicial: ");
        scanf("%d", &dummy);
        limparBufferEntrada();
        return;
    }

    if (buscarClientePorCpf(novo.cpf) != -1) {
        printf("[ERRO] CPF ja cadastrado no sistema!\n");
        printf("Nao e permitido duplicar CPFs.\n");
        printf("Cadastro cancelado.\n\n");
        printf("......................................................\n\n");
        printf("[OPCAO] Digite 0 para voltar ao menu inicial: ");
        scanf("%d", &dummy);
        limparBufferEntrada();
        return;
    }

    printf("[PASSO 3/3] DIGITE O DEPOSITO INICIAL (EM REAIS)\n");
    printf("Exemplo: 1000 (para R$ 1.000,00)\n");
    printf("Minimo: R$ 0,00\n");
    printf(">>> Digite o valor: R$ ");
    float depositoInicial;
    scanf("%f", &depositoInicial);
    limparBufferEntrada();
    printf("\n......................................................\n\n");

    if (depositoInicial >= SALDO_MINIMO) {
        novo.saldo = depositoInicial;
    } else {
        printf("[AVISO] Valor negativo. Saldo iniciado com R$ 0,00.\n\n");
        novo.saldo = 0.0;
    }

    clientes[totalClientes] = novo;
    totalClientes++;
    proximoCodigo++;

    printf("[SUCESSO] Cliente cadastrado com sucesso!\n\n");
    printf("RESUMO DO CADASTRO:\n");
    printf("  Codigo : %d\n", novo.codigo - 1);
    printf("  Nome   : %s\n", novo.nome);
    printf("  CPF    : %s\n", novo.cpf);
    printf("  Saldo  : R$ %.2f\n\n", novo.saldo);
    printf("......................................................\n\n");
    printf("[OPCAO] Digite 0 para voltar ao menu inicial: ");
    scanf("%d", &dummy);
    limparBufferEntrada();
}

void listarClientes(void) {
    int dummy;

    printf("\n========== OPCAO 2: LISTA DE CLIENTES ==========\n\n");

    if (totalClientes == 0) {
        printf("[INFORMACAO] Nenhum cliente cadastrado ainda.\n");
        printf("Use a opcao 1 para registrar um novo cliente.\n\n");
        printf("......................................................\n\n");
        printf("[OPCAO] Digite 0 para voltar ao menu inicial: ");
        scanf("%d", &dummy);
        limparBufferEntrada();
        return;
    }

    int clientesAtivos = 0;
    printf("[RESULTADO] Clientes cadastrados no sistema:\n\n");
    printf("......................................................\n\n");
    printf(" %-3s | %-25s | %-15s | %12s\n", "COD", "NOME", "CPF", "SALDO");
    printf("......................................................\n");

    for (int i = 0; i < totalClientes; i++) {
        if (clientes[i].ativo == 1) {
            printf(" %-3d | %-25s | %-15s | R$ %10.2f\n",
                   clientes[i].codigo,
                   clientes[i].nome,
                   clientes[i].cpf,
                   clientes[i].saldo);
            clientesAtivos++;
        }
    }
    printf("......................................................\n\n");
    printf("[RESUMO] Total de clientes ativos: %d / %d\n\n", clientesAtivos, totalClientes);
    printf("......................................................\n\n");
    printf("[OPCAO] Digite 0 para voltar ao menu inicial: ");
    scanf("%d", &dummy);
    limparBufferEntrada();
}

int buscarClientePorCpf(const char cpf[]) {

    int posicaoEncontrada = -1;
    int i = 0;

    while (i < totalClientes && posicaoEncontrada == -1) {
        if (strcmp(clientes[i].cpf, cpf) == 0 && clientes[i].ativo == 1) {
            posicaoEncontrada = i;
        }
        i++;
    }

    return posicaoEncontrada;
}

void buscarCliente(void) {
    char cpfBusca[TAM_CPF];
    int dummy;

    printf("\n========== OPCAO 5: BUSCAR CLIENTE ==========\n\n");
    printf("Pesquise um cliente pelo seu CPF:\n\n");
    printf("......................................................\n\n");

    printf("[PASSO 1/1] DIGITE O CPF (SOMENTE NUMEROS)\n");
    printf("Exemplo: 12345678901\n");
    printf(">>> Digite o CPF: ");
    lerLinha(cpfBusca, TAM_CPF);
    printf("\n......................................................\n\n");

    int pos = buscarClientePorCpf(cpfBusca);

    if (pos == -1) {
        printf("[ERRO] Cliente nao encontrado!\n");
        printf("Verifique se o CPF foi digitado corretamente.\n\n");
    } else {
        printf("[SUCESSO] Cliente encontrado!\n\n");
        printf("DADOS DO CLIENTE:\n\n");
        printf("  Codigo : %d\n", clientes[pos].codigo);
        printf("  Nome   : %s\n", clientes[pos].nome);
        printf("  CPF    : %s\n", clientes[pos].cpf);
        printf("  Saldo  : R$ %.2f\n\n", clientes[pos].saldo);
    }
    printf("......................................................\n\n");
    printf("[OPCAO] Digite 0 para voltar ao menu inicial: ");
    scanf("%d", &dummy);
    limparBufferEntrada();
}

void depositar(void) {
    char cpfBusca[TAM_CPF];
    float valor;
    int dummy;

    printf("\n========== OPCAO 3: REALIZAR DEPOSITO ==========\n\n");
    printf("Adicione dinheiro a conta de um cliente:\n\n");
    printf("......................................................\n\n");

    printf("[PASSO 1/2] DIGITE O CPF DO CLIENTE (SOMENTE NUMEROS)\n");
    printf("Exemplo: 12345678901\n");
    printf(">>> Digite o CPF: ");
    lerLinha(cpfBusca, TAM_CPF);
    printf("\n......................................................\n\n");

    int pos = buscarClientePorCpf(cpfBusca);

    if (pos == -1) {
        printf("[ERRO] Cliente nao encontrado!\n");
        printf("Verifique o CPF ou cadastre o cliente primeiro.\n\n");
        printf("......................................................\n\n");
        printf("[OPCAO] Digite 0 para voltar ao menu inicial: ");
        scanf("%d", &dummy);
        limparBufferEntrada();
        return;
    }

    printf("[INFORMACAO] Cliente encontrado: %s\n", clientes[pos].nome);
    printf("[INFORMACAO] Saldo atual: R$ %.2f\n\n", clientes[pos].saldo);
    printf("......................................................\n\n");

    printf("[PASSO 2/2] DIGITE O VALOR DO DEPOSITO (EM REAIS)\n");
    printf("Exemplo: 500 (para R$ 500,00)\n");
    printf(">>> Digite o valor: R$ ");
    scanf("%f", &valor);
    limparBufferEntrada();
    printf("\n......................................................\n\n");

    if (valor > 0) {
        float saldoAnterior = clientes[pos].saldo;
        clientes[pos].saldo += valor;
        printf("[SUCESSO] Deposito realizado com sucesso!\n\n");
        printf("RESUMO DA TRANSACAO:\n");
        printf("  Cliente          : %s\n", clientes[pos].nome);
        printf("  Saldo anterior   : R$ %.2f\n", saldoAnterior);
        printf("  Valor depositado : R$ %.2f\n", valor);
        printf("  Novo saldo       : R$ %.2f\n\n", clientes[pos].saldo);
    } else {
        printf("[ERRO] Valor de deposito invalido!\n");
        printf("O deposito deve ser maior que R$ 0,00.\n\n");
    }
    printf("......................................................\n\n");
    printf("[OPCAO] Digite 0 para voltar ao menu inicial: ");
    scanf("%d", &dummy);
    limparBufferEntrada();
}

void sacar(void) {
    char cpfBusca[TAM_CPF];
    float valor;
    int dummy;

    printf("\n========== OPCAO 4: REALIZAR SAQUE ==========\n\n");
    printf("Retire dinheiro da conta de um cliente:\n\n");
    printf("......................................................\n\n");

    printf("[PASSO 1/2] DIGITE O CPF DO CLIENTE (SOMENTE NUMEROS)\n");
    printf("Exemplo: 12345678901\n");
    printf(">>> Digite o CPF: ");
    lerLinha(cpfBusca, TAM_CPF);
    printf("\n......................................................\n\n");

    int pos = buscarClientePorCpf(cpfBusca);

    if (pos == -1) {
        printf("[ERRO] Cliente nao encontrado!\n");
        printf("Verifique o CPF ou cadastre o cliente primeiro.\n\n");
        printf("......................................................\n\n");
        printf("[OPCAO] Digite 0 para voltar ao menu inicial: ");
        scanf("%d", &dummy);
        limparBufferEntrada();
        return;
    }

    printf("[INFORMACAO] Cliente encontrado: %s\n", clientes[pos].nome);
    printf("[INFORMACAO] Saldo disponivel: R$ %.2f\n\n", clientes[pos].saldo);
    printf("......................................................\n\n");

    printf("[PASSO 2/2] DIGITE O VALOR DO SAQUE (EM REAIS)\n");
    printf("Exemplo: 200 (para R$ 200,00)\n");
    printf(">>> Digite o valor: R$ ");
    scanf("%f", &valor);
    limparBufferEntrada();
    printf("\n......................................................\n\n");

    if (valor > 0 && valor <= clientes[pos].saldo) {
        float saldoAnterior = clientes[pos].saldo;
        clientes[pos].saldo -= valor;
        printf("[SUCESSO] Saque realizado com sucesso!\n\n");
        printf("RESUMO DA TRANSACAO:\n");
        printf("  Cliente         : %s\n", clientes[pos].nome);
        printf("  Saldo anterior  : R$ %.2f\n", saldoAnterior);
        printf("  Valor sacado    : R$ %.2f\n", valor);
        printf("  Novo saldo      : R$ %.2f\n\n", clientes[pos].saldo);
    } else if (valor <= 0) {
        printf("[ERRO] Valor de saque invalido!\n");
        printf("O saque deve ser maior que R$ 0,00.\n\n");
    } else {
        printf("[ERRO] Saldo insuficiente!\n");
        printf("Saldo disponivel : R$ %.2f\n", clientes[pos].saldo);
        printf("Valor do saque   : R$ %.2f\n\n", valor);
    }
    printf("......................................................\n\n");
    printf("[OPCAO] Digite 0 para voltar ao menu inicial: ");
    scanf("%d", &dummy);
    limparBufferEntrada();
}

void excluirCliente(void) {
    char cpfBusca[TAM_CPF];
    char confirmacao[2];
    int dummy;

    printf("\n========== OPCAO 6: EXCLUIR CLIENTE ==========\n\n");
    printf("[ATENCAO] Esta operacao e IRREVERSIVEL!\n\n");
    printf("......................................................\n\n");

    printf("[PASSO 1/2] DIGITE O CPF DO CLIENTE (SOMENTE NUMEROS)\n");
    printf("Exemplo: 12345678901\n");
    printf(">>> Digite o CPF: ");
    lerLinha(cpfBusca, TAM_CPF);
    printf("\n......................................................\n\n");

    int pos = buscarClientePorCpf(cpfBusca);

    if (pos == -1) {
        printf("[ERRO] Cliente nao encontrado!\n");
        printf("Verifique o CPF digitado.\n\n");
        printf("......................................................\n\n");
        printf("[OPCAO] Digite 0 para voltar ao menu inicial: ");
        scanf("%d", &dummy);
        limparBufferEntrada();
        return;
    }

    printf("[CONFIRMACAO] Cliente encontrado:\n\n");
    printf("  Nome  : %s\n", clientes[pos].nome);
    printf("  CPF   : %s\n", clientes[pos].cpf);
    printf("  Saldo : R$ %.2f\n\n", clientes[pos].saldo);
    printf("......................................................\n\n");

    printf("[PASSO 2/2] CONFIRME A EXCLUSAO\n");
    printf("Tem CERTEZA que deseja excluir este cliente?\n");
    printf("Digite S para sim ou N para nao\n");
    printf(">>> Sua resposta: ");
    lerLinha(confirmacao, 2);
    printf("\n......................................................\n\n");
    
    if (confirmacao[0] == 'S' || confirmacao[0] == 's') {
        clientes[pos].ativo = 0;
        printf("[SUCESSO] Cliente '%s' foi excluido do sistema.\n\n", clientes[pos].nome);
    } else {
        printf("[CANCELADO] Operacao de exclusao cancelada.\n\n");
    }
    printf("......................................................\n\n");
    printf("[OPCAO] Digite 0 para voltar ao menu inicial: ");
    scanf("%d", &dummy);
    limparBufferEntrada();
}
