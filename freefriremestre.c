#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ================== DEFINIÇÃO DA STRUCT ==================

struct Componente {
    char nome[30];
    char tipo[20];
    int prioridade;
};

// ================== VARIÁVEIS GLOBAIS ==================

struct Componente componentes[20];  // Vetor de componentes
int totalComponentes = 0;           // Contador de componentes cadastrados
int comparacoes = 0;                // Contador global de comparações
double tempoExecucao = 0.0;         // Tempo de execução do último algoritmo

// ================== FUNÇÕES DE ENTRADA/SAÍDA ==================

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void cadastrarComponente() {
    if (totalComponentes >= 20) {
        printf("\nERRO: Capacidade maxima de componentes atingida (20 componentes)!\n");
        return;
    }
    
    printf("\n=== CADASTRO DE COMPONENTE %d/20 ===\n", totalComponentes + 1);
    
    // Ler nome do componente
    printf("Nome do componente (ex: 'chip central', 'propulsor', 'sistema de controle'): ");
    fgets(componentes[totalComponentes].nome, 30, stdin);
    componentes[totalComponentes].nome[strcspn(componentes[totalComponentes].nome, "\n")] = '\0';
    
    // Ler tipo do componente
    printf("Tipo (controle, suporte, propulsao, energia, seguranca): ");
    fgets(componentes[totalComponentes].tipo, 20, stdin);
    componentes[totalComponentes].tipo[strcspn(componentes[totalComponentes].tipo, "\n")] = '\0';
    
    // Ler prioridade
    printf("Prioridade (1-10, onde 10 é mais critico): ");
    while (1) {
        if (scanf("%d", &componentes[totalComponentes].prioridade) == 1) {
            if (componentes[totalComponentes].prioridade >= 1 && 
                componentes[totalComponentes].prioridade <= 10) {
                limparBuffer();
                break;
            }
        }
        limparBuffer();
        printf("Prioridade invalida! Digite um numero entre 1 e 10: ");
    }
    
    totalComponentes++;
    printf("Componente cadastrado com sucesso!\n");
}

void mostrarComponentes() {
    if (totalComponentes == 0) {
        printf("\nNenhum componente cadastrado ainda!\n");
        return;
    }
    
    printf("\n=== COMPONENTES CADASTRADOS (%d/20) ===\n", totalComponentes);
    printf("=============================================\n");
    printf("| %-25s | %-15s | %-10s |\n", "NOME", "TIPO", "PRIORIDADE");
    printf("=============================================\n");
    
    for (int i = 0; i < totalComponentes; i++) {
        printf("| %-25s | %-15s | %-10d |\n", 
               componentes[i].nome, 
               componentes[i].tipo, 
               componentes[i].prioridade);
    }
    printf("=============================================\n");
}

// ================== ALGORITMOS DE ORDENAÇÃO ==================

// Bubble Sort: Ordena por nome (string)
void bubbleSortNome() {
    if (totalComponentes < 2) {
        printf("\nPrecisa de pelo menos 2 componentes para ordenar!\n");
        return;
    }
    
    comparacoes = 0;
    clock_t inicio = clock();
    
    printf("\n=== ORDENANDO POR NOME (BUBBLE SORT) ===\n");
    
    for (int i = 0; i < totalComponentes - 1; i++) {
        for (int j = 0; j < totalComponentes - i - 1; j++) {
            comparacoes++;
            if (strcmp(componentes[j].nome, componentes[j + 1].nome) > 0) {
                // Troca os componentes
                struct Componente temp = componentes[j];
                componentes[j] = componentes[j + 1];
                componentes[j + 1] = temp;
            }
        }
    }
    
    clock_t fim = clock();
    tempoExecucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
    
    printf("Ordenacao concluida!\n");
    printf("Comparacoes realizadas: %d\n", comparacoes);
    printf("Tempo de execucao: %.6f segundos\n", tempoExecucao);
}

// Insertion Sort: Ordena por tipo (string)
void insertionSortTipo() {
    if (totalComponentes < 2) {
        printf("\nPrecisa de pelo menos 2 componentes para ordenar!\n");
        return;
    }
    
    comparacoes = 0;
    clock_t inicio = clock();
    
    printf("\n=== ORDENANDO POR TIPO (INSERTION SORT) ===\n");
    
    for (int i = 1; i < totalComponentes; i++) {
        struct Componente chave = componentes[i];
        int j = i - 1;
        
        while (j >= 0) {
            comparacoes++;
            if (strcmp(componentes[j].tipo, chave.tipo) > 0) {
                componentes[j + 1] = componentes[j];
                j--;
            } else {
                break;
            }
        }
        componentes[j + 1] = chave;
    }
    
    clock_t fim = clock();
    tempoExecucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
    
    printf("Ordenacao concluida!\n");
    printf("Comparacoes realizadas: %d\n", comparacoes);
    printf("Tempo de execucao: %.6f segundos\n", tempoExecucao);
}

// Selection Sort: Ordena por prioridade (int)
void selectionSortPrioridade() {
    if (totalComponentes < 2) {
        printf("\nPrecisa de pelo menos 2 componentes para ordenar!\n");
        return;
    }
    
    comparacoes = 0;
    clock_t inicio = clock();
    
    printf("\n=== ORDENANDO POR PRIORIDADE (SELECTION SORT) ===\n");
    
    for (int i = 0; i < totalComponentes - 1; i++) {
        int min_idx = i;
        
        for (int j = i + 1; j < totalComponentes; j++) {
            comparacoes++;
            if (componentes[j].prioridade < componentes[min_idx].prioridade) {
                min_idx = j;
            }
        }
        
        if (min_idx != i) {
            // Troca os componentes
            struct Componente temp = componentes[i];
            componentes[i] = componentes[min_idx];
            componentes[min_idx] = temp;
        }
    }
    
    clock_t fim = clock();
    tempoExecucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
    
    printf("Ordenacao concluida!\n");
    printf("Comparacoes realizadas: %d\n", comparacoes);
    printf("Tempo de execucao: %.6f segundos\n", tempoExecucao);
}

// ================== BUSCA BINÁRIA ==================

// Função auxiliar para verificar se o vetor está ordenado por nome
int estaOrdenadoPorNome() {
    for (int i = 0; i < totalComponentes - 1; i++) {
        if (strcmp(componentes[i].nome, componentes[i + 1].nome) > 0) {
            return 0; // Não está ordenado
        }
    }
    return 1; // Está ordenado
}

// Busca binária por nome (requer vetor ordenado por nome)
void buscaBinariaPorNome() {
    if (totalComponentes == 0) {
        printf("\nNenhum componente cadastrado para busca!\n");
        return;
    }
    
    // Verificar se o vetor está ordenado por nome
    if (!estaOrdenadoPorNome()) {
        printf("\nAVISO: Para busca binaria, os componentes devem estar ordenados por nome!\n");
        printf("Deseja ordenar por nome agora? (s/n): ");
        char resposta;
        scanf("%c", &resposta);
        limparBuffer();
        
        if (resposta == 's' || resposta == 'S') {
            bubbleSortNome();
        } else {
            printf("Busca binaria cancelada.\n");
            return;
        }
    }
    
    printf("\n=== BUSCA BINARIA POR NOME ===\n");
    printf("Digite o nome do componente a ser buscado: ");
    
    char nomeBusca[30];
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    comparacoes = 0;
    clock_t inicio = clock();
    
    int esquerda = 0;
    int direita = totalComponentes - 1;
    int encontrado = -1;
    
    while (esquerda <= direita) {
        comparacoes++;
        int meio = esquerda + (direita - esquerda) / 2;
        
        int resultado = strcmp(componentes[meio].nome, nomeBusca);
        
        if (resultado == 0) {
            encontrado = meio;
            break;
        } else if (resultado < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    
    clock_t fim = clock();
    tempoExecucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
    
    if (encontrado != -1) {
        printf("\n>>> COMPONENTE-CHAVE ENCONTRADO! <<<\n");
        printf("O componente '%s' foi encontrado na posicao %d.\n", 
               nomeBusca, encontrado + 1);
        printf("Detalhes do componente:\n");
        printf("  Nome: %s\n", componentes[encontrado].nome);
        printf("  Tipo: %s\n", componentes[encontrado].tipo);
        printf("  Prioridade: %d\n", componentes[encontrado].prioridade);
        printf("\n>>> TORRE DE FUGA PRONTA PARA ATIVACAO! <<<\n");
    } else {
        printf("\nComponente '%s' nao encontrado.\n", nomeBusca);
    }
    
    printf("\n--- METRICAS DA BUSCA ---\n");
    printf("Comparacoes realizadas: %d\n", comparacoes);
    printf("Tempo de execucao: %.6f segundos\n", tempoExecucao);
}

// ================== ANÁLISE DE DESEMPENHO ==================

void analisarDesempenho() {
    if (totalComponentes < 5) {
        printf("\nPara analise de desempenho, cadastre pelo menos 5 componentes!\n");
        return;
    }
    
    printf("\n=== ANALISE COMPARATIVA DE DESEMPENHO ===\n");
    printf("Comparando algoritmos de ordenacao com %d componentes:\n", totalComponentes);
    
    // Fazer uma cópia do vetor original para testes
    struct Componente copia[20];
    for (int i = 0; i < totalComponentes; i++) {
        copia[i] = componentes[i];
    }
    
    // Testar Bubble Sort
    printf("\n1. BUBBLE SORT (por nome):\n");
    clock_t inicio = clock();
    comparacoes = 0;
    
    for (int i = 0; i < totalComponentes - 1; i++) {
        for (int j = 0; j < totalComponentes - i - 1; j++) {
            comparacoes++;
            if (strcmp(copia[j].nome, copia[j + 1].nome) > 0) {
                struct Componente temp = copia[j];
                copia[j] = copia[j + 1];
                copia[j + 1] = temp;
            }
        }
    }
    
    clock_t fim = clock();
    double tempoBubble = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("   Comparacoes: %d\n", comparacoes);
    printf("   Tempo: %.6f segundos\n", tempoBubble);
    
    // Restaurar cópia
    for (int i = 0; i < totalComponentes; i++) {
        copia[i] = componentes[i];
    }
    
    // Testar Insertion Sort
    printf("\n2. INSERTION SORT (por tipo):\n");
    inicio = clock();
    comparacoes = 0;
    
    for (int i = 1; i < totalComponentes; i++) {
        struct Componente chave = copia[i];
        int j = i - 1;
        
        while (j >= 0) {
            comparacoes++;
            if (strcmp(copia[j].tipo, chave.tipo) > 0) {
                copia[j + 1] = copia[j];
                j--;
            } else {
                break;
            }
        }
        copia[j + 1] = chave;
    }
    
    fim = clock();
    double tempoInsertion = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("   Comparacoes: %d\n", comparacoes);
    printf("   Tempo: %.6f segundos\n", tempoInsertion);
    
    // Restaurar cópia
    for (int i = 0; i < totalComponentes; i++) {
        copia[i] = componentes[i];
    }
    
    // Testar Selection Sort
    printf("\n3. SELECTION SORT (por prioridade):\n");
    inicio = clock();
    comparacoes = 0;
    
    for (int i = 0; i < totalComponentes - 1; i++) {
        int min_idx = i;
        
        for (int j = i + 1; j < totalComponentes; j++) {
            comparacoes++;
            if (copia[j].prioridade < copia[min_idx].prioridade) {
                min_idx = j;
            }
        }
        
        if (min_idx != i) {
            struct Componente temp = copia[i];
            copia[i] = copia[min_idx];
            copia[min_idx] = temp;
        }
    }
    
    fim = clock();
    double tempoSelection = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("   Comparacoes: %d\n", comparacoes);
    printf("   Tempo: %.6f segundos\n", tempoSelection);
    
    printf("\n=== RESUMO DA ANALISE ===\n");
    printf("Algoritmo mais rapido: ");
    if (tempoBubble <= tempoInsertion && tempoBubble <= tempoSelection) {
        printf("BUBBLE SORT\n");
    } else if (tempoInsertion <= tempoBubble && tempoInsertion <= tempoSelection) {
        printf("INSERTION SORT\n");
    } else {
        printf("SELECTION SORT\n");
    }
}

// ================== MONTAÇÃO FINAL ==================

void montagemFinal() {
    if (totalComponentes == 0) {
        printf("\nNenhum componente cadastrado para montagem!\n");
        return;
    }
    
    printf("\n=== MONTAGEM FINAL DA TORRE DE FUGA ===\n");
    printf("A zona segura esta se fechando! Montando componentes...\n\n");
    
    // Verificar se há componentes críticos
    int componentesCriticos = 0;
    for (int i = 0; i < totalComponentes; i++) {
        if (componentes[i].prioridade >= 8) {
            componentesCriticos++;
        }
    }
    
    if (componentesCriticos == 0) {
        printf("ALERTA: Nenhum componente critico (prioridade 8+) encontrado!\n");
        printf("A torre pode nao funcionar corretamente.\n");
    } else {
        printf("Componentes criticos identificados: %d\n", componentesCriticos);
    }
    
    // Ordenar por prioridade para montagem
    selectionSortPrioridade();
    
    printf("\n>>> SEQUENCIA DE MONTAGEM (por prioridade):\n");
    printf("=============================================\n");
    
    for (int i = totalComponentes - 1; i >= 0; i--) {
        printf("Etapa %d: %s", totalComponentes - i, componentes[i].nome);
        
        if (componentes[i].prioridade >= 8) {
            printf(" [CRITICO - Prioridade %d]", componentes[i].prioridade);
        }
        
        printf("\n   Tipo: %s\n", componentes[i].tipo);
        printf("   Status: [INSTALADO]\n");
        
        if (i > 0) {
            printf("   ---\n");
        }
    }
    
    printf("\n>>> TORRE DE FUGA MONTADA COM SUCESSO! <<<\n");
    printf(">>> PRONTO PARA EVACUACAO! <<<\n");
}

// ================== MENU PRINCIPAL ==================

void exibirMenu() {
    printf("\n========================================\n");
    printf("      TORRE DE FUGA - MONTAGEM FINAL    \n");
    printf("         ZONA SEGURA FECHANDO!         \n");
    printf("========================================\n");
    printf("Componentes cadastrados: %d/20\n", totalComponentes);
    printf("\nMENU PRINCIPAL:\n");
    printf("1. Cadastrar novo componente\n");
    printf("2. Mostrar todos os componentes\n");
    printf("3. Ordenar por nome (Bubble Sort)\n");
    printf("4. Ordenar por tipo (Insertion Sort)\n");
    printf("5. Ordenar por prioridade (Selection Sort)\n");
    printf("6. Buscar componente-chave (Busca Binaria)\n");
    printf("7. Analisar desempenho dos algoritmos\n");
    printf("8. Executar montagem final da torre\n");
    printf("9. Sair do sistema\n");
    printf("\nEscolha uma opcao: ");
}

int main() {
    printf("========================================\n");
    printf("   SISTEMA DE MONTAGEM - TORRE DE FUGA  \n");
    printf("   DESAFIO FINAL: SOBREVIVENCIA        \n");
    printf("========================================\n");
    printf("\nInstrucoes:\n");
    printf("- Cadastre ate 20 componentes para a torre\n");
    printf("- Ordene por diferentes criterios\n");
    printf("- Encontre o componente-chave com busca binaria\n");
    printf("- Monte a torre antes que a zona segura se feche!\n");
    
    int opcao;
    
    do {
        exibirMenu();
        
        if (scanf("%d", &opcao) != 1) {
            limparBuffer();
            printf("Entrada invalida! Digite um numero de 1 a 9.\n");
            continue;
        }
        limparBuffer();
        
        switch(opcao) {
            case 1:
                cadastrarComponente();
                break;
            case 2:
                mostrarComponentes();
                break;
            case 3:
                bubbleSortNome();
                mostrarComponentes();
                break;
            case 4:
                insertionSortTipo();
                mostrarComponentes();
                break;
            case 5:
                selectionSortPrioridade();
                mostrarComponentes();
                break;
            case 6:
                buscaBinariaPorNome();
                break;
            case 7:
                analisarDesempenho();
                break;
            case 8:
                montagemFinal();
                break;
            case 9:
                printf("\nSaindo do sistema...\n");
                printf(">>> EVACUACAO CONCLUIDA! VOCE SOBREVIVEU! <<<\n");
                break;
            default:
                printf("Opcao invalida! Digite um numero de 1 a 9.\n");
        }
        
    } while(opcao != 9);
    
    return 0;
}