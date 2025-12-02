#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ================== DEFINIÇÕES DE STRUCTS ==================

// Struct para representar um item do inventário
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

// Struct para nó da lista encadeada
struct No {
    struct Item dados;
    struct No* proximo;
};

// ================== VARIÁVEIS GLOBAIS ==================

// Contadores de comparações para análise de desempenho
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// ================== IMPLEMENTAÇÃO COM VETOR ==================

#define MAX_ITENS 10

struct Item mochilaVetor[MAX_ITENS];
int totalVetor = 0;

// Função para inserir item no vetor
void inserirItemVetor() {
    if (totalVetor >= MAX_ITENS) {
        printf("ERRO: Mochila (vetor) esta cheia! Capacidade maxima: %d itens.\n", MAX_ITENS);
        return;
    }
    
    printf("\n--- INSERIR ITEM NO VETOR ---\n");
    
    printf("Nome do item (max 30 caracteres): ");
    fgets(mochilaVetor[totalVetor].nome, 30, stdin);
    mochilaVetor[totalVetor].nome[strcspn(mochilaVetor[totalVetor].nome, "\n")] = 0;
    
    printf("Tipo do item (ex: arma, municao, cura, ferramenta): ");
    fgets(mochilaVetor[totalVetor].tipo, 20, stdin);
    mochilaVetor[totalVetor].tipo[strcspn(mochilaVetor[totalVetor].tipo, "\n")] = 0;
    
    printf("Quantidade: ");
    scanf("%d", &mochilaVetor[totalVetor].quantidade);
    
    while (getchar() != '\n'); // Limpar buffer
    
    totalVetor++;
    printf("Item adicionado ao vetor com sucesso!\n");
}

// Função para remover item do vetor por nome
void removerItemVetor() {
    if (totalVetor == 0) {
        printf("Mochila (vetor) esta vazia!\n");
        return;
    }
    
    printf("\n--- REMOVER ITEM DO VETOR ---\n");
    printf("Digite o nome do item a ser removido: ");
    
    char nomeBusca[30];
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;
    
    // Busca sequencial para encontrar o item
    comparacoesSequencial = 0;
    int indice = -1;
    
    for (int i = 0; i < totalVetor; i++) {
        comparacoesSequencial++;
        if (strcmp(mochilaVetor[i].nome, nomeBusca) == 0) {
            indice = i;
            break;
        }
    }
    
    if (indice == -1) {
        printf("Item '%s' nao encontrado no vetor. Comparacoes: %d\n", nomeBusca, comparacoesSequencial);
        return;
    }
    
    printf("Item encontrado! Removendo... Comparacoes realizadas: %d\n", comparacoesSequencial);
    
    // Remover item deslocando elementos
    for (int i = indice; i < totalVetor - 1; i++) {
        mochilaVetor[i] = mochilaVetor[i + 1];
    }
    
    totalVetor--;
    printf("Item removido do vetor com sucesso!\n");
}

// Função para ordenar o vetor por nome (Bubble Sort)
void ordenarVetor() {
    if (totalVetor < 2) {
        printf("Vetor tem menos de 2 itens, nao precisa ordenar.\n");
        return;
    }
    
    printf("\n--- ORDENANDO VETOR POR NOME (BUBBLE SORT) ---\n");
    
    for (int i = 0; i < totalVetor - 1; i++) {
        for (int j = 0; j < totalVetor - i - 1; j++) {
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                // Troca os itens
                struct Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }
        }
    }
    
    printf("Vetor ordenado por nome com sucesso!\n");
}

// Função de busca sequencial no vetor
void buscarSequencialVetor() {
    if (totalVetor == 0) {
        printf("Mochila (vetor) esta vazia!\n");
        return;
    }
    
    printf("\n--- BUSCA SEQUENCIAL NO VETOR ---\n");
    printf("Digite o nome do item a ser buscado: ");
    
    char nomeBusca[30];
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;
    
    comparacoesSequencial = 0;
    int encontrado = 0;
    
    for (int i = 0; i < totalVetor; i++) {
        comparacoesSequencial++;
        if (strcmp(mochilaVetor[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado na posicao %d:\n", i);
            printf("- Nome: %s\n", mochilaVetor[i].nome);
            printf("- Tipo: %s\n", mochilaVetor[i].tipo);
            printf("- Quantidade: %d\n", mochilaVetor[i].quantidade);
            encontrado = 1;
            break;
        }
    }
    
    if (!encontrado) {
        printf("Item '%s' nao encontrado no vetor.\n", nomeBusca);
    }
    
    printf("Comparacoes realizadas na busca sequencial: %d\n", comparacoesSequencial);
}

// Função de busca binária no vetor (requer vetor ordenado)
void buscarBinariaVetor() {
    if (totalVetor == 0) {
        printf("Mochila (vetor) esta vazia!\n");
        return;
    }
    
    // Verificar se o vetor está ordenado
    int ordenado = 1;
    for (int i = 0; i < totalVetor - 1; i++) {
        if (strcmp(mochilaVetor[i].nome, mochilaVetor[i + 1].nome) > 0) {
            ordenado = 0;
            break;
        }
    }
    
    if (!ordenado) {
        printf("AVISO: O vetor precisa estar ordenado para busca binaria!\n");
        printf("Deseja ordenar agora? (s/n): ");
        char resposta;
        scanf("%c", &resposta);
        while (getchar() != '\n');
        
        if (resposta == 's' || resposta == 'S') {
            ordenarVetor();
        } else {
            printf("Busca binaria cancelada. Use busca sequencial.\n");
            return;
        }
    }
    
    printf("\n--- BUSCA BINARIA NO VETOR (VETOR ORDENADO) ---\n");
    printf("Digite o nome do item a ser buscado: ");
    
    char nomeBusca[30];
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;
    
    comparacoesBinaria = 0;
    int inicio = 0;
    int fim = totalVetor - 1;
    int encontrado = 0;
    
    while (inicio <= fim) {
        comparacoesBinaria++;
        int meio = (inicio + fim) / 2;
        
        int comparacao = strcmp(mochilaVetor[meio].nome, nomeBusca);
        
        if (comparacao == 0) {
            printf("\nItem encontrado na posicao %d:\n", meio);
            printf("- Nome: %s\n", mochilaVetor[meio].nome);
            printf("- Tipo: %s\n", mochilaVetor[meio].tipo);
            printf("- Quantidade: %d\n", mochilaVetor[meio].quantidade);
            encontrado = 1;
            break;
        } else if (comparacao < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    
    if (!encontrado) {
        printf("Item '%s' nao encontrado no vetor.\n", nomeBusca);
    }
    
    printf("Comparacoes realizadas na busca binaria: %d\n", comparacoesBinaria);
}

// Função para listar todos os itens do vetor
void listarVetor() {
    printf("\n=== ITENS NA MOCHILA (VETOR) ===\n");
    printf("Total: %d/%d itens\n\n", totalVetor, MAX_ITENS);
    
    if (totalVetor == 0) {
        printf("A mochila (vetor) esta vazia.\n");
        return;
    }
    
    for (int i = 0; i < totalVetor; i++) {
        printf("Item %d:\n", i + 1);
        printf("  Nome: %s\n", mochilaVetor[i].nome);
        printf("  Tipo: %s\n", mochilaVetor[i].tipo);
        printf("  Quantidade: %d\n\n", mochilaVetor[i].quantidade);
    }
}

// ================== IMPLEMENTAÇÃO COM LISTA ENCADEADA ==================

struct No* inicioLista = NULL;
int totalLista = 0;

// Função para criar um novo nó
struct No* criarNo(struct Item item) {
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    if (novoNo == NULL) {
        printf("ERRO: Falha na alocacao de memoria!\n");
        return NULL;
    }
    
    novoNo->dados = item;
    novoNo->proximo = NULL;
    return novoNo;
}

// Função para inserir item no início da lista encadeada
void inserirItemLista() {
    printf("\n--- INSERIR ITEM NA LISTA ENCADEADA ---\n");
    
    struct Item novoItem;
    
    printf("Nome do item (max 30 caracteres): ");
    fgets(novoItem.nome, 30, stdin);
    novoItem.nome[strcspn(novoItem.nome, "\n")] = 0;
    
    printf("Tipo do item (ex: arma, municao, cura, ferramenta): ");
    fgets(novoItem.tipo, 20, stdin);
    novoItem.tipo[strcspn(novoItem.tipo, "\n")] = 0;
    
    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);
    
    while (getchar() != '\n'); // Limpar buffer
    
    struct No* novoNo = criarNo(novoItem);
    if (novoNo == NULL) return;
    
    // Inserir no início da lista
    novoNo->proximo = inicioLista;
    inicioLista = novoNo;
    totalLista++;
    
    printf("Item adicionado a lista encadeada com sucesso!\n");
}

// Função para remover item da lista encadeada por nome
void removerItemLista() {
    if (inicioLista == NULL) {
        printf("Lista encadeada esta vazia!\n");
        return;
    }
    
    printf("\n--- REMOVER ITEM DA LISTA ENCADEADA ---\n");
    printf("Digite o nome do item a ser removido: ");
    
    char nomeBusca[30];
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;
    
    comparacoesSequencial = 0;
    struct No* atual = inicioLista;
    struct No* anterior = NULL;
    int encontrado = 0;
    
    while (atual != NULL) {
        comparacoesSequencial++;
        if (strcmp(atual->dados.nome, nomeBusca) == 0) {
            encontrado = 1;
            break;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    
    if (!encontrado) {
        printf("Item '%s' nao encontrado na lista. Comparacoes: %d\n", nomeBusca, comparacoesSequencial);
        return;
    }
    
    printf("Item encontrado! Removendo... Comparacoes realizadas: %d\n", comparacoesSequencial);
    
    // Remover o nó encontrado
    if (anterior == NULL) {
        // Remover o primeiro nó
        inicioLista = atual->proximo;
    } else {
        // Remover nó do meio ou final
        anterior->proximo = atual->proximo;
    }
    
    free(atual);
    totalLista--;
    printf("Item removido da lista encadeada com sucesso!\n");
}

// Função de busca sequencial na lista encadeada
void buscarSequencialLista() {
    if (inicioLista == NULL) {
        printf("Lista encadeada esta vazia!\n");
        return;
    }
    
    printf("\n--- BUSCA SEQUENCIAL NA LISTA ENCADEADA ---\n");
    printf("Digite o nome do item a ser buscado: ");
    
    char nomeBusca[30];
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;
    
    comparacoesSequencial = 0;
    struct No* atual = inicioLista;
    int posicao = 1;
    int encontrado = 0;
    
    while (atual != NULL) {
        comparacoesSequencial++;
        if (strcmp(atual->dados.nome, nomeBusca) == 0) {
            printf("\nItem encontrado na posicao %d da lista:\n", posicao);
            printf("- Nome: %s\n", atual->dados.nome);
            printf("- Tipo: %s\n", atual->dados.tipo);
            printf("- Quantidade: %d\n", atual->dados.quantidade);
            encontrado = 1;
            break;
        }
        atual = atual->proximo;
        posicao++;
    }
    
    if (!encontrado) {
        printf("Item '%s' nao encontrado na lista encadeada.\n", nomeBusca);
    }
    
    printf("Comparacoes realizadas na busca sequencial: %d\n", comparacoesSequencial);
}

// Função para listar todos os itens da lista encadeada
void listarLista() {
    printf("\n=== ITENS NA MOCHILA (LISTA ENCADEADA) ===\n");
    printf("Total: %d itens\n\n", totalLista);
    
    if (inicioLista == NULL) {
        printf("A lista encadeada esta vazia.\n");
        return;
    }
    
    struct No* atual = inicioLista;
    int posicao = 1;
    
    while (atual != NULL) {
        printf("Item %d:\n", posicao);
        printf("  Nome: %s\n", atual->dados.nome);
        printf("  Tipo: %s\n", atual->dados.tipo);
        printf("  Quantidade: %d\n\n", atual->dados.quantidade);
        
        atual = atual->proximo;
        posicao++;
    }
}

// ================== MENU E FUNÇÕES AUXILIARES ==================

void menuVetor() {
    int opcao;
    
    do {
        printf("\n=== MENU VETOR (LISTA SEQUENCIAL) ===\n");
        printf("1. Inserir item\n");
        printf("2. Remover item por nome\n");
        printf("3. Listar todos os itens\n");
        printf("4. Buscar item (busca sequencial)\n");
        printf("5. Ordenar vetor por nome\n");
        printf("6. Buscar item (busca binaria - requer ordenacao)\n");
        printf("7. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        
        scanf("%d", &opcao);
        while (getchar() != '\n'); // Limpar buffer
        
        switch(opcao) {
            case 1: inserirItemVetor(); break;
            case 2: removerItemVetor(); break;
            case 3: listarVetor(); break;
            case 4: buscarSequencialVetor(); break;
            case 5: ordenarVetor(); break;
            case 6: buscarBinariaVetor(); break;
            case 7: printf("Retornando ao menu principal...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while(opcao != 7);
}

void menuLista() {
    int opcao;
    
    do {
        printf("\n=== MENU LISTA ENCADEADA ===\n");
        printf("1. Inserir item\n");
        printf("2. Remover item por nome\n");
        printf("3. Listar todos os itens\n");
        printf("4. Buscar item (busca sequencial)\n");
        printf("5. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        
        scanf("%d", &opcao);
        while (getchar() != '\n'); // Limpar buffer
        
        switch(opcao) {
            case 1: inserirItemLista(); break;
            case 2: removerItemLista(); break;
            case 3: listarLista(); break;
            case 4: buscarSequencialLista(); break;
            case 5: printf("Retornando ao menu principal...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while(opcao != 5);
}

void compararDesempenho() {
    printf("\n=== COMPARACAO DE DESEMPENHO ===\n");
    
    // Criar dados de teste
    struct Item itensTeste[5] = {
        {"Pistola", "Arma", 1},
        {"Municao", "Municao", 30},
        {"Kit Medico", "Cura", 2},
        {"Faca", "Arma", 1},
        {"Bandagem", "Cura", 5}
    };
    
    // Teste com vetor
    printf("\n--- TESTE COM VETOR ---\n");
    clock_t inicio, fim;
    
    // Inserção
    inicio = clock();
    for (int i = 0; i < 5; i++) {
        if (totalVetor < MAX_ITENS) {
            mochilaVetor[totalVetor++] = itensTeste[i];
        }
    }
    fim = clock();
    printf("Tempo de insercao de 5 itens: %.6f segundos\n", 
           (double)(fim - inicio) / CLOCKS_PER_SEC);
    
    // Busca sequencial
    inicio = clock();
    buscarSequencialVetor();
    fim = clock();
    printf("Tempo da busca sequencial: %.6f segundos\n", 
           (double)(fim - inicio) / CLOCKS_PER_SEC);
    
    // Ordenação
    inicio = clock();
    ordenarVetor();
    fim = clock();
    printf("Tempo da ordenacao: %.6f segundos\n", 
           (double)(fim - inicio) / CLOCKS_PER_SEC);
    
    // Busca binária
    inicio = clock();
    buscarBinariaVetor();
    fim = clock();
    printf("Tempo da busca binaria: %.6f segundos\n", 
           (double)(fim - inicio) / CLOCKS_PER_SEC);
    
    printf("\n--- TESTE COM LISTA ENCADEADA ---\n");
    
    // Inserção na lista
    inicio = clock();
    for (int i = 0; i < 5; i++) {
        struct No* novoNo = criarNo(itensTeste[i]);
        if (novoNo != NULL) {
            novoNo->proximo = inicioLista;
            inicioLista = novoNo;
            totalLista++;
        }
    }
    fim = clock();
    printf("Tempo de insercao de 5 itens: %.6f segundos\n", 
           (double)(fim - inicio) / CLOCKS_PER_SEC);
    
    // Busca sequencial na lista
    inicio = clock();
    buscarSequencialLista();
    fim = clock();
    printf("Tempo da busca sequencial: %.6f segundos\n", 
           (double)(fim - inicio) / CLOCKS_PER_SEC);
    
    printf("\n=== ANALISE DE DESEMPENHO ===\n");
    printf("\nVANTAGENS DO VETOR:\n");
    printf("- Acesso direto por indice (O(1))\n");
    printf)- Permite busca binaria apos ordenacao (O(log n))\n";
    printf("- Menor overhead de memoria (sem ponteiros)\n");
    
    printf("\nVANTAGENS DA LISTA ENCADEADA:\n");
    printf("- Insercao/remocao eficiente no inicio (O(1))\n");
    printf)- Tamanho dinamico (sem limite fixo)\n";
    printf("- Nao requer realocacao ou deslocamento de elementos\n");
    
    printf("\nCONCLUSOES:\n");
    printf("- Use VETOR quando: acesso aleatorio frequente, tamanho fixo conhecido\n");
    printf("- Use LISTA ENCADEADA quando: muitas insercoes/remocoes, tamanho variavel\n");
}

int main() {
    printf("========================================\n");
    printf("  SISTEMA COMPARATIVO: VETOR vs LISTA  \n");
    printf("   MOCHILA DE SOBREVIVENCIA - JOGO     \n");
    printf("========================================\n\n");
    
    int opcaoPrincipal;
    
    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Trabalhar com VETOR (Lista Sequencial)\n");
        printf("2. Trabalhar com LISTA ENCADEADA\n");
        printf("3. Comparar desempenho das estruturas\n");
        printf("4. Sair do programa\n");
        printf("Escolha uma opcao: ");
        
        scanf("%d", &opcaoPrincipal);
        while (getchar() != '\n'); // Limpar buffer
        
        switch(opcaoPrincipal) {
            case 1: menuVetor(); break;
            case 2: menuLista(); break;
            case 3: compararDesempenho(); break;
            case 4: printf("Encerrando programa...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while(opcaoPrincipal != 4);
    
    // Liberar memória da lista encadeada
    struct No* atual = inicioLista;
    while (atual != NULL) {
        struct No* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    
    return 0;
}