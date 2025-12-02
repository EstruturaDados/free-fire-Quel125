#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definição da struct Item para representar um item no inventário
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

// Declaração do vetor de itens (mochila) com capacidade para 10 itens
struct Item mochila[10];
int totalItens = 0; // Contador de itens atualmente na mochila

// Protótipos das funções
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();
void exibirMenu();

int main() {
    printf("=== SISTEMA DE INVENTARIO - MOCHILA DE LOOT ===\n");
    printf("Bem-vindo ao sistema de gerenciamento de inventario!\n");
    
    int opcao;
    
    do {
        exibirMenu();
        printf("\nDigite sua opcao: ");
        scanf("%d", &opcao);
        
        // Limpar buffer de entrada
        while (getchar() != '\n');
        
        switch(opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 5:
                printf("Saindo do sistema... Ate a proxima!\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
        
        printf("\n");
        
    } while(opcao != 5);
    
    return 0;
}

// Função para exibir o menu de opções
void exibirMenu() {
    printf("\n========== MENU ==========\n");
    printf("1. Inserir item\n");
    printf("2. Remover item\n");
    printf("3. Listar todos os itens\n");
    printf("4. Buscar item por nome\n");
    printf("5. Sair\n");
    printf("==========================\n");
}

// Função para inserir um novo item na mochila
void inserirItem() {
    // Verificar se a mochila está cheia
    if (totalItens >= 10) {
        printf("ERRO: A mochila esta cheia! Capacidade maxima: 10 itens.\n");
        return;
    }
    
    printf("\n--- INSERIR NOVO ITEM ---\n");
    
    // Ler dados do novo item
    printf("Nome do item (max 30 caracteres): ");
    fgets(mochila[totalItens].nome, 30, stdin);
    mochila[totalItens].nome[strcspn(mochila[totalItens].nome, "\n")] = 0; // Remover quebra de linha
    
    printf("Tipo do item (ex: arma, municao, cura, ferramenta): ");
    fgets(mochila[totalItens].tipo, 20, stdin);
    mochila[totalItens].tipo[strcspn(mochila[totalItens].tipo, "\n")] = 0; // Remover quebra de linha
    
    printf("Quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);
    
    // Limpar buffer após scanf
    while (getchar() != '\n');
    
    totalItens++;
    printf("Item adicionado com sucesso!\n");
    
    // Listar todos os itens após inserção
    listarItens();
}

// Função para remover um item da mochila pelo nome
void removerItem() {
    if (totalItens == 0) {
        printf("A mochila esta vazia! Nao ha itens para remover.\n");
        return;
    }
    
    printf("\n--- REMOVER ITEM ---\n");
    printf("Digite o nome do item a ser removido: ");
    
    char nomeBusca[30];
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0; // Remover quebra de linha
    
    // Busca sequencial para encontrar o item
    int indice = -1;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            indice = i;
            break;
        }
    }
    
    if (indice == -1) {
        printf("Item '%s' nao encontrado na mochila.\n", nomeBusca);
        return;
    }
    
    // Exibir item encontrado
    printf("Item encontrado:\n");
    printf("- Nome: %s\n", mochila[indice].nome);
    printf("- Tipo: %s\n", mochila[indice].tipo);
    printf("- Quantidade: %d\n", mochila[indice].quantidade);
    
    printf("Tem certeza que deseja remover este item? (s/n): ");
    char confirmacao;
    scanf("%c", &confirmacao);
    
    // Limpar buffer após scanf
    while (getchar() != '\n');
    
    if (confirmacao == 's' || confirmacao == 'S') {
        // Remover item deslocando os elementos seguintes
        for (int i = indice; i < totalItens - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        
        totalItens--;
        printf("Item removido com sucesso!\n");
        
        // Listar todos os itens após remoção
        listarItens();
    } else {
        printf("Operacao cancelada.\n");
    }
}

// Função para listar todos os itens da mochila
void listarItens() {
    printf("\n--- ITENS NA MOCHILA (%d/10) ---\n", totalItens);
    
    if (totalItens == 0) {
        printf("A mochila esta vazia.\n");
        return;
    }
    
    for (int i = 0; i < totalItens; i++) {
        printf("\nItem %d:\n", i + 1);
        printf("- Nome: %s\n", mochila[i].nome);
        printf("- Tipo: %s\n", mochila[i].tipo);
        printf("- Quantidade: %d\n", mochila[i].quantidade);
    }
    
    printf("----------------------------\n");
}

// Função de busca sequencial para localizar um item pelo nome
void buscarItem() {
    if (totalItens == 0) {
        printf("A mochila esta vazia! Nao ha itens para buscar.\n");
        return;
    }
    
    printf("\n--- BUSCAR ITEM POR NOME ---\n");
    printf("Digite o nome do item a ser buscado: ");
    
    char nomeBusca[30];
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0; // Remover quebra de linha
    
    // Busca sequencial
    int encontrados = 0;
    
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado na posicao %d:\n", i + 1);
            printf("- Nome: %s\n", mochila[i].nome);
            printf("- Tipo: %s\n", mochila[i].tipo);
            printf("- Quantidade: %d\n", mochila[i].quantidade);
            encontrados++;
        }
    }
    
    if (encontrados == 0) {
        printf("Nenhum item com o nome '%s' foi encontrado na mochila.\n", nomeBusca);
    } else {
        printf("\nTotal de itens encontrados: %d\n", encontrados);
    }
}
