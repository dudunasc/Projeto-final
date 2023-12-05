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


int main(){

}
