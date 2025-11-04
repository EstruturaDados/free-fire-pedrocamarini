#include <stdio.h>  // Para printf, scanf
#include <stdlib.h> // Para system("cls") ou system("clear")
#include <string.h> // Para strcmp (vamos usar na remoção)

// --- Constantes e Estruturas ---

// Define a capacidade máxima da mochila, conforme o desafio Novato
#define MAX_ITENS 10 

// 1. Estrutura (Struct) para representar um item
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// --- "Banco de Dados" Global ---

// 2. Vetor estático para a mochila e o contador de itens
Item mochila[MAX_ITENS];
int contadorItens = 0; // Controla quantos itens TEMOS na mochila

// --- Protótipos das Funções ---
// (Avisando ao C que essas funções existem)

void adicionarItem();
void removerItem();
void listarItens();
void pausarTela(); // Função útil para "Pressione Enter para continuar"

// --- Função Principal (main) ---

int main() {
    int opcao;

    // 3. Menu interativo com do-while
    do {
        // Limpa a tela para o menu ficar mais organizado
        #ifdef _WIN32
            system("cls"); // Comando para Windows
        #else
            system("clear"); // Comando para Linux/Mac
        #endif

        printf("======================================\n");
        printf(" MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
        printf(" (Itens na Mochila: %d/%d)\n", contadorItens, MAX_ITENS);
        printf("======================================\n\n");
        printf("Escolha uma opcao:\n");
        printf("1. Adicionar Item (Loot)\n");
        printf("2. Remover Item\n");
        printf("3. Listar Itens na Mochila\n");
        printf("0. Sair\n\n");
        printf("Opcao: ");
        
        // Lê a escolha do usuário
        scanf("%d", &opcao);
        
        // Limpa o buffer do teclado (para evitar problemas com scanf de strings depois)
        while (getchar() != '\n'); 

        // 4. Switch para tratar a escolha
        switch (opcao) {
            case 1:
                adicionarItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 0:
                printf("\nSaindo do sistema... Ate a proxima, sobrevivente!\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                break;
        }

        // Se a opção não for 'Sair', pausa a tela
        if (opcao != 0) {
            pausarTela();
        }

    } while (opcao != 0); // O loop continua enquanto a opção for diferente de 0

    return 0;
}

// --- Implementação das Funções ---

/**
 * @brief Adiciona um novo item na mochila.
 * * Verifica se a mochila esta cheia. Se nao estiver,
 * pede ao usuario o nome, tipo e quantidade do item
 * e o adiciona no vetor.
 */
void adicionarItem() {
    printf("\n--- Adicionar Novo Item ---\n");

    // 1. Verificar se a mochila está cheia
    if (contadorItens >= MAX_ITENS) {
        printf("A mochila esta cheia! Nao e possivel adicionar mais itens.\n");
        printf("Remova um item antes de adicionar outro.\n");
        return; // Retorna ao menu principal
    }

    // 2. Se não estiver cheia, pede os dados do novo item.
    //    Vamos adicionar o item direto na posição do 'contadorItens'
    
    printf("Nome do Item: ");
    // Lê o nome. O " %[^\n]" é um truque para ler strings com espaços.
    scanf(" %[^\n]", mochila[contadorItens].nome);
    while (getchar() != '\n'); // Limpa o buffer do teclado

    printf("Tipo do Item (ex: arma, municao, cura, etc.): ");
    scanf(" %[^\n]", mochila[contadorItens].tipo);
    while (getchar() != '\n'); // Limpa o buffer do teclado

    printf("Quantidade: ");
    scanf("%d", &mochila[contadorItens].quantidade);
    while (getchar() != '\n'); // Limpa o buffer do teclado

    // 3. Informa o sucesso e incrementa o contador
    printf("\nItem '%s' (Tipo: %s, Qtd: %d) adicionado com sucesso!\n",
           mochila[contadorItens].nome,
           mochila[contadorItens].tipo,
           mochila[contadorItens].quantidade);
           
    contadorItens++; // IMPORTANTE: Avisa que temos +1 item na mochila
}

/**
 * @brief Remove um item da mochila pelo nome.
 * * Pede ao usuario o nome do item a ser removido.
 * Busca no vetor e, se encontrar, remove o item
 * e reorganiza o vetor.
 */
void removerItem() {
    printf("\n--- Remover Item ---\n");

    // 1. Verifica se a mochila esta vazia
    if (contadorItens == 0) {
        printf("\nA mochila ja esta vazia! Nao ha o que remover.\n");
        return; // Retorna ao menu
    }

    char nomeParaRemover[30];
    printf("Digite o nome exato do item que deseja remover: ");
    scanf(" %[^\n]", nomeParaRemover);
    while (getchar() != '\n'); // Limpa o buffer

    int indiceItem = -1; // Usamos -1 para indicar que "nao foi encontrado"
    int i;

    // 2. Loop para encontrar o item
    for (i = 0; i < contadorItens; i++) {
        // strcmp retorna 0 se as strings forem IGUAIS
        if (strcmp(nomeParaRemover, mochila[i].nome) == 0) {
            indiceItem = i; // Achamos o item! Guardamos sua posicao.
            break; // Para o loop de busca
        }
    }

    // 3. Verifica se o item foi encontrado
    if (indiceItem == -1) {
        // Se o indice ainda e -1, o item nao foi encontrado
        printf("\nItem '%s' nao encontrado na mochila.\n", nomeParaRemover);
    } else {
        // 4. Se foi encontrado (indice != -1), vamos remove-lo

        // Pega o nome do item ANTES de apaga-lo, para a mensagem
        char nomeRemovido[30];
        strcpy(nomeRemovido, mochila[indiceItem].nome);

        // Loop para "puxar" os itens seguintes para a esquerda
        // Comeca do indice que encontramos e vai ate o PENULTIMO item
        for (i = indiceItem; i < contadorItens - 1; i++) {
            mochila[i] = mochila[i + 1]; // Copia o proximo item para a posicao atual
        }

        // 5. Decrementa o contador
        contadorItens--; 

        printf("\nItem '%s' removido com sucesso!\n", nomeRemovido);
        printf("Itens restantes na mochila: %d/%d\n", contadorItens, MAX_ITENS);
    }
}


/**
 * @brief Lista todos os itens atualmente na mochila.
 * * Percorre o vetor de itens (de 0 ate contadorItens)
 * e exibe os dados de cada item em formato de tabela.
 */
void listarItens() {
    printf("\n--- Itens na Mochila (%d/%d) ---\n", contadorItens, MAX_ITENS);
    
    // 1. Verificar se a mochila está vazia
    if (contadorItens == 0) {
        printf("\nA mochila esta vazia!\n");
        return; // Retorna ao menu
    }

    // 2. Se não estiver vazia, imprime o cabeçalho da tabela
    // O "%-30s" significa "string alinhada a esquerda com 30 espacos"
    // O "%-20s" significa "string alinhada a esquerda com 20 espacos"
    // O "%3s"   significa "string alinhada a direita com 3 espacos"
    
    printf("\n");
    printf("%-30s | %-20s | %s\n", "NOME DO ITEM", "TIPO", "QTD");
    printf("------------------------------------------------------------------\n");

    // 3. Cria um loop (for) para passar por cada item
    for (int i = 0; i < contadorItens; i++) {
        // Imprime os dados de cada item formatado
        printf("%-30s | %-20s | %3d\n",
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }
}

/**
 * @brief Pausa a execucao ate o usuario pressionar Enter.
 */
void pausarTela() {
    printf("\nPressione Enter para continuar...");
    while (getchar() != '\n'); // Aguarda o usuário pressionar Enter
}