#include <cctype>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>


struct Cliente {
    char nomeCompleto[100];
    int numeroCliente;
    char cpf[15];
    char endereco[100];
    char email[50];
    char modeloVeiculo[50];
    char reclamacoes[200];
    int anoVeiculo;
    char placaDoVeiculo[10];
    int kmRodados;
    int anoUltimaManutencao;
    char telefone[15];
};

struct Produto {
    char nome[50];
    float preco;
    int quantidadeEstoque;
};

struct OrdemServico {
    int numeroOS;
    char cpf[15];  
    struct Cliente cliente;
    char checklist[200];
    char pecas[200];
    char servicosRealizados[200];
    char mecanico[50];
    char atendente[50];
    int aceitaServico; 
    float precoTotalProdutos; 
};

struct OrdemServico ordensServico[100];
int numeroOS = 1;

struct Produto produtos[100];
int numeroProdutos = 0;

static int numeroCliente = 1;

struct Funcionario {
    char login[20];
    char senha[20];
    char nome[50]; 
};  

struct Funcionario funcionarios[3] = {
    {"admin", "admin123", "Administrador"},
};

int numeroFuncionarios = 0;



void salvarFuncionariosEmArquivo() {
    FILE *arquivo = fopen("funcionarios.txt", "w");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo de funcionários");
        return;
    }

    for (int i = 0; i < numeroFuncionarios; i++) {
        fprintf(arquivo, "%s %s %s\n", funcionarios[i].login, funcionarios[i].senha, funcionarios[i].nome);
    }

    fclose(arquivo);
}


void carregarFuncionariosDoArquivo() {
    FILE *arquivo = fopen("funcionarios.txt", "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo de funcionários");
        return;
    }

    while (fscanf(arquivo, "%s %s %s", funcionarios[numeroFuncionarios].login, funcionarios[numeroFuncionarios].senha, funcionarios[numeroFuncionarios].nome) == 3) {
        numeroFuncionarios++;
        if (numeroFuncionarios >= sizeof(funcionarios) / sizeof(funcionarios[0])) {
            printf("Limite de funcionários atingido. Alguns funcionários podem não ter sido carregados.\n");
            break;
        }
    }

    fclose(arquivo);
}

void cadastrarFuncionario() {
    struct Funcionario novoFuncionario;

    printf("Digite o login do novo funcionário: ");
    scanf("%s", novoFuncionario.login);

    printf("Digite a senha do novo funcionário: ");
    scanf("%s", novoFuncionario.senha);

    printf("Digite o nome do novo funcionário: ");
    scanf("%s", novoFuncionario.nome);

    for (int i = 0; i < numeroFuncionarios; i++) {
        if (strcmp(funcionarios[i].login, novoFuncionario.login) == 0) {
            printf("Login já existente. Escolha outro login.\n");
            return;
        }
    }

    if (numeroFuncionarios < sizeof(funcionarios) / sizeof(funcionarios[0])) {
        funcionarios[numeroFuncionarios] = novoFuncionario;
        printf("Funcionário cadastrado com sucesso!\n");
        numeroFuncionarios++;
        salvarFuncionariosEmArquivo();
    } else {
        printf("Limite de funcionários atingido. Não foi possível cadastrar.\n");
    }
}


void exibirTabelaPrecos() {
    printf("\nTabela de Produtos Cadastrados:\n");
    printf("%-3s%-25s%-20s%s\n", "Nº", "Nome do Produto", "Preço (R$)", "Estoque");

    for (int i = 0; i < numeroProdutos; i++) {
        printf("%-3d%-25s%-20.2f%d\n", i + 1, produtos[i].nome, produtos[i].preco, produtos[i].quantidadeEstoque);
    }
}
    }
}
void cadastrarClienteGerarOS() {
    if (numeroOS < 100) {
        struct Cliente novoCliente;
        struct OrdemServico novaOS;

        printf("Digite o nome do cliente: ");
        if (fgets(novoCliente.nome, sizeof(novoCliente.nome), stdin) == NULL) {
        }
        novoCliente.nome[strcspn(novoCliente.nome, "\n")] = '\0';

        printf("Digite o modelo do veículo: ");
        if (fgets(novoCliente.modeloVeiculo, sizeof(novoCliente.modeloVeiculo), stdin) == NULL) {
        }
        novoCliente.modeloVeiculo[strcspn(novoCliente.modeloVeiculo, "\n")] = '\0';

        printf("Digite as reclamações do cliente: ");
        if (fgets(novoCliente.reclamacoes, sizeof(novoCliente.reclamacoes), stdin) == NULL) {
        }
        novoCliente.reclamacoes[strcspn(novoCliente.reclamacoes, "\n")] = '\0';

        printf("Digite o ano do veículo: ");
        if (scanf("%d", &novoCliente.anoVeiculo) != 1) {
        }

        printf("Digite a placa do veículo: ");
        if (fgets(novoCliente.placaDoVeiculo, sizeof(novoCliente.placaDoVeiculo), stdin) == NULL) {
        }
        novoCliente.placaDoVeiculo[strcspn(novoCliente.placaDoVeiculo, "\n")] = '\0';

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        printf("Digite os km rodados do veículo: ");
        if (scanf("%d", &novoCliente.kmRodados) != 1) {
            // Lidar com erro de entrada
        }
        int clearBuffer;
        while ((clearBuffer = getchar()) != '\n' && clearBuffer != EOF);
        printf("Digite o ano da última manutenção do veículo: ");
        if (scanf("%d", &novoCliente.anoUltimaManutencao) != 1) {
        }

 srand(time(NULL));  

        novaOS.numeroOS = rand();  

        novaOS.cliente = novoCliente;

        ordensServico[numeroOS - 1] = novaOS;
        numeroOS++;

        printf("Cliente cadastrado e OS gerada com sucesso!\n");

        
        printf("Número do Cliente: %d\n", novaOS.numeroOS);
    } else {
        printf("Limite máximo de Ordens de Serviço atingido.\n");
    }
} void preencherChecklist() {
    int produtoSelecionado;
    char continuar;

    printf("Mecânico, selecione os produtos utilizados no checklist (digite o número do produto):\n");

    do {
        exibirTabelaPrecos();

        printf("Digite 'fim' para encerrar a seleção.\n");

        printf("Escolha: ");
        if (scanf("%d", &produtoSelecionado) != 1);

        if (produtoSelecionado >= 1 && produtoSelecionado <= sizeof(produtos) / sizeof(produtos[0])) {
            printf("Produto selecionado: %s\n", produtos[produtoSelecionado - 1].nome);

            if (produtos[produtoSelecionado - 1].quantidadeEstoque > 0) {
                produtos[produtoSelecionado - 1].quantidadeEstoque--;
                printf("Quantidade em estoque atualizada: %d\n", produtos[produtoSelecionado - 1].quantidadeEstoque);
            } else {
                printf("Estoque esgotado para este produto.\n");
            }
        } else if (produtoSelecionado != 0) {
            printf("Opção inválida. Tente novamente.\n");
        }

        while (getchar() != '\n');

        printf("Deseja adicionar mais produtos? (s/n): ");
        if (scanf("%c", &continuar) != 1);

    } while (continuar == 's');
}


