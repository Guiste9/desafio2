#include <stdio.h>
#include <time.h>
#include <stdlib.h>

struct node {
    int data;
    struct node* next;
};

typedef struct node node;

void bestFit(node** head_ref, int tamProcess[], int processo);
void firstFit(node** head_ref, int tamProcess[], int n);
int gerarlista(node** head_ref);
void display(node* node1);
void append(node** head_ref, int new_data);

int main() {
    srand(time(NULL));

    node* head = NULL;

    int n = gerarlista(&head);

    display(head);

    int num = 0;

    int *tamprocessm = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        tamprocessm[i] = rand() % 100 + 1;
    }

    do {
        puts("escolha 1 para o firstfit\n\n2 para o bestfit\n\n3 para sair do programa");
        scanf("%d", &num);

        switch (num) {
            case 1:
                firstFit(&head, tamprocessm, n);
                break;
            case 2:
                bestFit(&head, tamprocessm, n);
                break;
        }

    } while (num != 3);

    free(tamprocessm);

    return 0;
}

void firstFit(node** head_ref, int tamProcess[], int n) {
    node* current = *head_ref;

    printf("\nnumero do processo\ttamanho do processo\tnumero do bloco\n");
    for (int i = 0; i < n; i++) {
        int processoSize = tamProcess[i];
        int allocated = 0;

        while (current != NULL) {
            if (current->data >= processoSize) {
                printf("%d\t\t\t%d\t\t\t\t%d\n", i + 1, processoSize, current->data);
                current->data -= processoSize;
                allocated = 1;
                break;
            }
            current = current->next;
        }

        if (!allocated) {
            printf("%d\t\t\t%d\t\t\t\tnao foi alocado\n", i + 1, processoSize);
        }

        current = *head_ref; // Resetar para o início da lista para o próximo processo
    }
}

void bestFit(node** head_ref, int tamProcess[], int n) {
    node* current = *head_ref;

    printf("\nnumero do processo\ttamanho do processo\tnumero do bloco\n");
    for (int i = 0; i < n; i++) {
        int processoSize = tamProcess[i];
        int allocated = 0;
        node* bestFitBlock = NULL;

        while (current != NULL) {
            if (current->data >= processoSize && (!bestFitBlock || current->data < bestFitBlock->data)) {
                bestFitBlock = current;
            }
            current = current->next;
        }

        if (bestFitBlock != NULL) {
            printf("%d\t\t\t%d\t\t\t\t%d\n", i + 1, processoSize, bestFitBlock->data);
            bestFitBlock->data -= processoSize;
            allocated = 1;
        }

        if (!allocated) {
            printf("%d\t\t\t%d\t\t\t\tnao foi alocado\n", i + 1, processoSize);
        }

        current = *head_ref; // Resetar para o início da lista para o próximo processo
    }
}

void append(node** head_ref, int new_data) {
    node* novo_node = (node*)malloc(sizeof(node));
    node* last = *head_ref;

    novo_node->data = new_data;
    novo_node->next = NULL;

    if (*head_ref == NULL) {
        *head_ref = novo_node;
        return;
    }
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = novo_node;
}

void display(node* node1) {
    while (node1 != NULL) {
        printf("%d ->", node1->data);
        node1 = node1->next;
    }
    printf("NULL\n");
}

int gerarlista(node** head_ref) {
    int tamlista = rand() % 10 + 1; // Gera um número aleatório de processos (1 a 10)
    
    for (int i = 0; i < tamlista; i++) {
        append(head_ref, rand() % 100 + 1);
    }
    
    return tamlista;
}