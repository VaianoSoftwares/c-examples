#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// NODO: ELEMENTO CHE VA A COMPORRE UNA LISTA CONCATENATA
// IL NODO E' COMPOSTO DA:
//  - VALUE: UN VALORE GENERICO CHE IDENTIFICA IL NODO
//  - NEXT: UN PUNTATORE AL NODO SUCCESSIVO
typedef struct Node
{
    int value;
    struct Node *next;
} Node;

// LINKED LIST: LISTA CONCATENATA
// QUESTA LISTA IN PARTICOLARE DISPONE DI:
//  - HEAD: UN PUNTATORE AL PRIMO ELEMENTO IN TESTA ALLA LISTA
//  - SIZE: UN CONTATORE CHE TIENE TRACCIA DEL NUMERO DI NODI CHE COMPONGONO LA LISTA
typedef struct LinkedList
{
    Node *head;
    int size;
} LinkedList;

Node *create_node(int value);
void init_list(LinkedList *list);
void print_list(LinkedList *list);
bool is_empty(LinkedList *list);
Node *get_node(LinkedList *list, int pos);
int find_node(LinkedList *list, int value);
bool insert_node(LinkedList *list, Node *new_node, int pos);
void insert_node_top(LinkedList *list, Node *new_node);
void insert_node_bottom(LinkedList *list, Node *new_node);
Node *remove_node_top(LinkedList *list);
Node *remove_node_bottom(LinkedList *list);
Node *remove_node(LinkedList *list, int pos);

int main(void)
{
    LinkedList l1;
    init_list(&l1);

    printf("l1: ");
    print_list(&l1);

    Node *n1 = create_node(3);
    Node *n2 = create_node(7);
    Node *n3 = create_node(5);

    insert_node_top(&l1, n1);
    insert_node_bottom(&l1, n2);
    insert_node(&l1, n3, 1);

    printf("l1: ");
    print_list(&l1);

    printf("Il primo nodo con valore %d in l1 è in posizione %d\n", 5, find_node(&l1, 5));
    printf("Il primo nodo con valore %d in l1 è in posizione %d\n", 3, find_node(&l1, 3));
    printf("Il primo nodo con valore %d in l1 è in posizione %d\n", 1, find_node(&l1, 1));

    Node *found = get_node(&l1, 3);
    if (found == NULL)
        printf("Posizione %d non valida\n");
    else
        printf("Il nodo in posizione %d ha valore %d\n", 2, found->value);

    free(n1);
    free(n2);
    free(n3);

    return 0;
}

// RESTITUISCE IL PUNTATORE AD UN NUOVO NODO IL QUALE:
//  - VIENE DEFINITO
//  - VIENE ALLOCATA DINAMICAMENTE UN'AREA DI MEMORIA OVE RISIEDERA' IL NODO
//  - VIENE INIZIALIZZATO CON VALUE PASSATO COME ARGOMENTO
Node *create_node(int value)
{
    Node *node = (Node *)malloc(sizeof(Node));

    if (node == NULL)
        return NULL;

    node->next = NULL;
    node->value = value;

    return node;
}

// INIZIALIZZAZIONE DELLA LISTA
// INIZIALMENTE LA LISTA E' VUOTA
void init_list(LinkedList *list)
{
    list->head = (Node *)NULL;
    list->size = 0;
}

// STAMPA A VIDEO DELLA LISTA
void print_list(LinkedList *list)
{
    printf("->");

    Node *tmp_node = list->head;

    while (tmp_node != NULL)
    {
        printf("[%d]->", tmp_node->value);
        tmp_node = tmp_node->next;
    }

    printf("NULL\n");
}

// RITORNA VERO SE LA LISTA E' VUOTA
// RITORNA FALSO ALTRIMENTI
bool is_empty(LinkedList *list)
{
    return list->head == NULL;
}

// DATA LA POSIZIONE, RESTITUISCE L'INDIRIZZO DEL NODO IN QUELLA DATA POSIZIONE
// RITORNA NULL SE IL NODO NON VIENE TROVATO
Node *get_node(LinkedList *list, int pos)
{
    if (pos < 0 || pos >= list->size)
        return NULL;

    Node *tmp_node = list->head;

    for (int i = 0; i < pos; i++)
        tmp_node = tmp_node->next;

    return tmp_node;
}

// RESTITUISCE LA POSIZIONE DEL PRIMO NODO DEL VALORE PASSATO PER ARGOMENTO
// RITORNA -1 SE IL NODO NON VIENE TROVATO
int find_node(LinkedList *list, int value)
{
    int pos = 0;
    Node *tmp_node = list->head;

    while (tmp_node != NULL)
    {
        if (tmp_node->value == value)
            return pos;

        tmp_node = tmp_node->next;
        pos++;
    }

    return -1;
}

// INSERIMENTO IN TESTA ALLA LISTA DEL NODO NEW_NODE
void insert_node_top(LinkedList *list, Node *new_node)
{
    if (is_empty(list))
    {
        list->head = new_node;
        list->size++;
        return;
    }

    new_node->next = list->head;
    list->head = new_node;
    list->size++;
}

// INSERIMENTO IN FONDO ALLA LISTA DEL NODO NEW_NODE
void insert_node_bottom(LinkedList *list, Node *new_node)
{
    if (is_empty(list))
    {
        list->head = new_node;
        list->size++;
        return;
    }

    Node *tmp_node = list->head;

    while (tmp_node->next != NULL)
        tmp_node = tmp_node->next;

    tmp_node->next = new_node;
    list->size++;
}

// INSERIMENTO ALLA POSIZIONE POS DEL NODO NEW_NODE NELLA LISTA
bool insert_node(LinkedList *list, Node *new_node, int pos)
{
    if (pos < 0 || pos > list->size)
    {
        return false;
    }
    else if (pos == 0)
    {
        insert_node_top(list, new_node);
        return true;
    }
    else if (pos == list->size)
    {
        insert_node_bottom(list, new_node);
        return true;
    }

    Node *prev_node = list->head;
    Node *next_node = prev_node->next;

    for (int i = 1; i < pos; i++)
    {
        prev_node->next = next_node;
        next_node = next_node->next;
    }

    prev_node->next = new_node;
    new_node->next = next_node;
    list->size++;

    return true;
}

// RIMOZIONE DEL NODO IN TESTA ALLA LISTA
Node *remove_node_top(LinkedList *list)
{
    if (is_empty(list))
        return NULL;

    Node *tmp_node = list->head;
    list->head = list->head->next;
    list->size--;

    return tmp_node;
}

// RIMOZIONE DEL NODO IN FONDO ALLA LISTA
Node *remove_node_bottom(LinkedList *list)
{
    if (is_empty(list))
        return NULL;

    Node *prev_node = list->head;
    Node *curr_node = prev_node->next;

    if (list->size == 1)
    {
        init_list(list);
        return prev_node;
    }

    while (curr_node->next != NULL)
    {
        prev_node = prev_node->next;
        curr_node = curr_node->next;
    }

    prev_node->next = (Node *)NULL;
    curr_node->next = (Node *)NULL;

    list->size--;

    return curr_node;
}

// RIMOZIONE DEL NODO IN POSIZIONE POS NELLA LISTA
Node *remove_node(LinkedList *list, int pos)
{
    if (pos < 0 || pos >= list->size)
        return NULL;
    else if (pos == 0)
        return remove_node_top(list);
    else if (pos == list->size - 1)
        return remove_node_bottom(list);

    Node *prev_node = list->head;
    Node *curr_node = prev_node->next;

    for (int i = 1; i < pos; i++)
    {
        prev_node->next = curr_node;
        curr_node = curr_node->next;
    }

    prev_node->next = curr_node->next;
    curr_node->next = (Node *)NULL;

    return curr_node;
}