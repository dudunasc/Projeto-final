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

int encontrarCliente(const char *cpfCliente) {
    
    char cpfFormatado[15];
    int j = 0;
    for (int i = 0; cpfCliente[i]; i++) {
        if (isdigit(cpfCliente[i])) {
            cpfFormatado[j++] = cpfCliente[i];
        }
    }
    cpfFormatado[j] = '\0';

    for (int i = 0; i < sizeof(ordensServico) / sizeof(ordensServico[0]); i++) {
        if (strcmp(ordensServico[i].cpf, cpfFormatado) == 0) {
            return i;
        }
    }
    return -1;
}

void cadastrarCliente() {
    struct Cliente novoCliente;

    printf("Digite o nome completo: ");
    if (fgets(novoCliente.nomeCompleto, sizeof(novoCliente.nomeCompleto), stdin) == NULL) {
        printf("Erro ao ler o nome completo.\n");
        return;
    }
    novoCliente.nomeCompleto[strcspn(novoCliente.nomeCompleto, "\n")] = '\0';

    novoCliente.numeroCliente = numeroCliente++;

    printf("Digite o CPF: ");
    if (fgets(novoCliente.cpf, sizeof(novoCliente.cpf), stdin) == NULL) {
        printf("Erro ao ler o CPF.\n");
        return;
    }
    novoCliente.cpf[strcspn(novoCliente.cpf, "\n")] = '\0';

    printf("Digite o endereço do cliente: ");
    if (fgets(novoCliente.endereco, sizeof(novoCliente.endereco), stdin) == NULL) {
        printf("Erro ao ler o endereço.\n");
        return;
    }
    novoCliente.endereco[strcspn(novoCliente.endereco, "\n")] = '\0';

    printf("Digite o e-mail do cliente: ");
    if (fgets(novoCliente.email, sizeof(novoCliente.email), stdin) == NULL) {
        printf("Erro ao ler o e-mail.\n");
        return;
    }
    novoCliente.email[strcspn(novoCliente.email, "\n")] = '\0';

    printf("Digite o número de telefone do cliente: ");
    if (fgets(novoCliente.telefone, sizeof(novoCliente.telefone), stdin) == NULL) {
        printf("Erro ao ler o telefone.\n");
        return;
    }
    novoCliente.telefone[strcspn(novoCliente.telefone, "\n")] = '\0';

    printf("Digite o modelo do veículo do cliente: ");
    if (fgets(novoCliente.modeloVeiculo, sizeof(novoCliente.modeloVeiculo), stdin) == NULL) {
        printf("Erro ao ler o modelo do veículo.\n");
        return;
    }
    novoCliente.modeloVeiculo[strcspn(novoCliente.modeloVeiculo, "\n")] = '\0';

    printf("Digite as reclamações do cliente: ");
    if (fgets(novoCliente.reclamacoes, sizeof(novoCliente.reclamacoes), stdin) == NULL) {
        printf("Erro ao ler as reclamações.\n");
        return;
    }
    novoCliente.reclamacoes[strcspn(novoCliente.reclamacoes, "\n")] = '\0';

    printf("Digite o ano do veículo: ");
    if (scanf("%d", &novoCliente.anoVeiculo) != 1) {
        printf("Erro ao ler o ano do veículo.\n");
        return;
    }

   
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Digite a placa do veículo: ");
    if (fgets(novoCliente.placaDoVeiculo, sizeof(novoCliente.placaDoVeiculo), stdin) == NULL) {
        printf("Erro ao ler a placa do veículo.\n");
        return;
    }
    novoCliente.placaDoVeiculo[strcspn(novoCliente.placaDoVeiculo, "\n")] = '\0';

    printf("Digite os km rodados do veículo: ");
    if (scanf("%d", &novoCliente.kmRodados) != 1) {
        printf("Erro ao ler os km rodados.\n");
        return;
    }

    printf("Digite o ano da última manutenção do veículo: ");
    if (scanf("%d", &novoCliente.anoUltimaManutencao) != 1) {
        printf("Erro ao ler o ano da última manutenção.\n");
        return;
    }


    strcpy(ordensServico[numeroOS - 1].cpf, novoCliente.cpf);

    
    ordensServico[numeroOS - 1].cliente = novoCliente;

    printf("Cliente cadastrado com sucesso!\n");

    numeroOS++;
}

void preencherChecklist() {
  int resposta;
  char cpfCliente[15];

  printf("Digite o CPF do cliente: ");
  if (fgets(cpfCliente, sizeof(cpfCliente), stdin) == NULL) {
      perror("Erro ao ler o CPF do cliente");
      return;
    }
    cpfCliente[strcspn(cpfCliente, "\n")] = '\0';

    int indexOS = encontrarCliente(cpfCliente);
        
     if (indexOS != -1) {
        printf("\nRespostas do Cliente %s:\n", ordensServico[indexOS].cliente.nomeCompleto);

        printf("Modelo do veículo: %s\n", ordensServico[indexOS].cliente.modeloVeiculo);
        printf("Reclamações do cliente: %s\n", ordensServico[indexOS].cliente.reclamacoes);
        printf("Ano do veículo: %d\n", ordensServico[indexOS].cliente.anoVeiculo);
        printf("Placa do veículo: %s\n", ordensServico[indexOS].cliente.placaDoVeiculo);
        printf("Km rodados do veículo: %d\n", ordensServico[indexOS].cliente.kmRodados);
        printf("Ano da última manutenção do veículo: %d\n", ordensServico[indexOS].cliente.anoUltimaManutencao);
        printf("\nChecklist para o cliente %s:\n", ordensServico[indexOS].cliente.nomeCompleto);
        printf("1. Pneus:\n");
        printf("   Os pneus estão em boa condição? Eles têm a pressão correta e a profundidade mínima legal? (1 - Sim / 0 - Não): ");
        if (scanf("%d", &resposta) != 1) {
            fflush(stdin); 
        }
        ordensServico[indexOS].checklist[0] = (resposta == 1) ? '1' : '0';
         
        printf("2. Fluidos:\n");
        printf("   Os fluidos do veículo estão no nível correto? (1 - Sim / 0 - Não): ");
        if (scanf("%d", &resposta) != 1) {
            fflush(stdin); 
        }
        ordensServico[indexOS].checklist[1] = (resposta == 1) ? '1' : '0';

        printf("3. Freios:\n");
        printf("   O sistema de freios está funcionando corretamente? (1 - Sim / 0 - Não): ");
        if (scanf("%d", &resposta) != 1) {
            fflush(stdin); 
        }
        ordensServico[indexOS].checklist[2] = (resposta == 1) ? '1' : '0';

        printf("4. Iluminação:\n");
        printf("   O sistema de iluminação do veículo está operando corretamente? (1 - Sim / 0 - Não): ");
        if (scanf("%d", &resposta) != 1) {
            fflush(stdin); 
        }
        ordensServico[indexOS].checklist[3] = (resposta == 1) ? '1' : '0';

        printf("5. Suspensão:\n");
        printf("   O sistema de suspensão está em boas condições? (1 - Sim / 0 - Não): ");
        if (scanf("%d", &resposta) != 1) {
            fflush(stdin); 
        }
        ordensServico[indexOS].checklist[4] = (resposta == 1) ? '1' : '0';

        printf("6. Direção:\n");
        printf("   O sistema de direção está operando corretamente? (1 - Sim / 0 - Não): ");
        if (scanf("%d", &resposta) != 1) {
            fflush(stdin); 
        }
        ordensServico[indexOS].checklist[5] = (resposta == 1) ? '1' : '0';

        printf("7. Bateria:\n");
        printf("   A bateria do veículo está em bom estado? (1 - Sim / 0 - Não): ");
        if (scanf("%d", &resposta) != 1) {
            fflush(stdin); 
        }
        ordensServico[indexOS].checklist[6] = (resposta == 1) ? '1' : '0';

        printf("8. Sistema Elétrico:\n");
        printf("   O sistema elétrico do veículo está funcionando corretamente? (1 - Sim / 0 - Não): ");
        if (scanf("%d", &resposta) != 1) {
            fflush(stdin);
        }
        ordensServico[indexOS].checklist[7] = (resposta == 1) ? '1' : '0';

        printf("\nChecklist preenchido com sucesso para o cliente %s!\n", ordensServico[indexOS].cliente.nomeCompleto);
    } else {
        printf("Cliente não encontrado.\n");
    }
}

void adicionarProdutoOS(int indexOS, int *quantidadeProdutos, float *valorProdutos) {
int opcaoProduto;
int quantidade;

printf("\nAdicionar produtos à Ordem de Serviço:\n");

while (1) {
        
        exibirTabelaPrecos();
        printf("Escolha um produto (digite o número) ou 0 para sair: ");
        if (scanf("%d", &opcaoProduto) != 1) {
            printf("Entrada inválida.\n");
            return;
        }

        if (opcaoProduto == 0) {
            break; 
        }

        if (opcaoProduto >= 1 && opcaoProduto <= numeroProdutos) {

            printf("Digite a quantidade desejada: ");
            if (scanf("%d", &quantidade) != 1) {
                printf("Entrada inválida.\n");
                return;
            }

            if (quantidade > 0 && quantidade <= produtos[opcaoProduto - 1].quantidadeEstoque) {

                strcat(ordensServico[indexOS].pecas, produtos[opcaoProduto - 1].nome);
                strcat(ordensServico[indexOS].pecas, "; ");
                produtos[opcaoProduto - 1].quantidadeEstoque -= quantidade;


               *quantidadeProdutos += quantidade;


               *valorProdutos += produtos[opcaoProduto - 1].preco * quantidade;
             } else {
                printf("Quantidade inválida ou insuficiente em estoque.\n");
             }
         }     else {
                printf("Opção de produto inválida.\n");
         }
    }
    
    printf("Produtos adicionados à Ordem de Serviço com sucesso!\n");
}




int fazerLogin(struct Funcionario *usuarioLogado) {
    char login[20];
    char senha[20];

    printf("Login: ");
    scanf("%s", login);

    printf("Senha: ");
    scanf("%s", senha);

    for (int i = 0; i < sizeof(funcionarios) / sizeof(funcionarios[0]); i++) {
        if (strcmp(funcionarios[i].login, login) == 0 && strcmp(funcionarios[i].senha, senha) == 0) {
            printf("Login bem-sucedido!\n");
            *usuarioLogado = funcionarios[i];
            return 1;
        }
    }

    printf("Login ou senha incorretos.\n");
    return 0;
}

int main(){
    carregarFuncionariosDoArquivo();

    int tentativas = 3;
    struct Funcionario usuarioLogado; 
     while (tentativas > 0) {
        printf("Bem-vindo à Oficina Mecânica!\n");

         if (fazerLogin(&usuarioLogado)) {
            system("cls");
             
            int opcao = 0;
            while (opcao != 7) {
                printf("\nBem-vindo, %s!\n", usuarioLogado.nome);
                printf("Escolha a opção:\n");
                printf("1 - Cadastrar Cliente\n");
                printf("2 - Preencher Checklist\n");
                printf("3 - Consultar Peças e Gerar Orçamento\n");
                printf("4 - Registrar Serviços Realizados\n");
                printf("5 - Cadastrar Produto\n");
                printf("6 - Cadastrar Funcionário\n");
                printf("7 - Sair\n");
                
                printf("Escolha: ");
                scanf("%d", &opcao);

                while (getchar() != '\n');

                 switch (opcao) {
                    case 1:
                        cadastrarCliente();
                        break;
                    case 2:
                        preencherChecklist();
                        break;
                      case 3:
                        consultarPecasGerarOrcamento();
                        break;
                    case 4:
                        registrarServicosRealizados();
                        break;
                     case 5:
                        cadastrarProduto();
                        break;
                    case 6:
                        cadastrarFuncionario();
                        break;
                       case 7:
                        printf("Saindo...\n");
                        break;
                    default:
                        printf("Opção inválida. Tente novamente.\n");
                }

                system("pause");
                system("cls");
}
        break;
        } else {
            tentativas--;
            printf("Tentativas restantes: %d\n", tentativas);
        }
    }
  if (tentativas == 0) {
        printf("Número de tentativas excedido. Saindo...\n");
}

    return 0;
}


