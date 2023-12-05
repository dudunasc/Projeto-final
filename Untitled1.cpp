#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Cliente {
    char nome[50];
    char modeloVeiculo[50];
    char reclamacoes[200];
    int anoVeiculo;
    char placaDoVeiculo[10];
    int kmRodados;
    int anoUltimaManutencao;
}
struct OrdemServico {
    int numeroOS;
    struct Cliente cliente;
    char checklist[200];
    char pecas[200];
    char servicosRealizados[200];
    char mecanico[50];
    char atendente[50];
}
struct Produto {
    char nome[50];
    float preco;
    int quantidadeEstoque;
}

struct OrdemServico ordensServico[100];
int numeroOs = 1;

struct Produto produtos [100];
int numeroProdutos = 0;

void exibirTabelaPrecos () {
    printf("\nTabela de Produtos Cadastrados:\n");
    printf("%-3s%-25s%-20s%s\n", "Nº", "Nome do Produto", "Preço (R$)", "Estoque");

    for (int i = 0; i < numerosdeProdutos, i++){
        printf("%-3d%-25s%-20.2f%d\n", i + 1, produtos[i].nome, produtos[i].preco, produtos[i].quantidadeEstoque);
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

        novaOS.numeroOS = numeroOS;
        novaOS.cliente = novoCliente;

        ordensServico[numeroOS - 1] = novaOS;
        numeroOS++;

        printf("Cliente cadastrado e OS gerada com sucesso!\n");
    } else {
        printf("Limite máximo de Ordens de Serviço atingido.\n");
    }
}

int main(){

}
