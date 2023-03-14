#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

void initialize_array(int arr[], int size);
void print_array(int arr[], int size);
int linear_search(int arr[], int size, int value);
void selection_sort(int arr[], int size);
void swap(int arr[], int i, int j);
void occurrencies(int arr[], int size, int occur[]);

int main(void)
{
    // RANDOM SEED GENERATOR
    srand(time(NULL));

    // DEFINIZIONE DI ARR, ARRAY DI INTERI DI DIMENSIONE 10
    int arr[10];

    // DIMENSIONE DI ARR
    // sizeof(arr) -> 40 byte
    // sizeof(int) -> 4 byte
    // 40 / 4 = 10 elementi
    int size_arr = sizeof(arr) / sizeof(arr[0]);
    printf("Dimensione di arr: %d\n", size_arr);

    // INIZIALIZZAZIONE DI ARR
    initialize_array(arr, size_arr);

    // STAMPA A VIDEO ARR INIZIALIZZATO
    printf("ARR NON ORDINATO: ");
    print_array(arr, size_arr);

    // RICERCA DI X IN ARR
    int x = rand() % 10;
    int x_pos = linear_search(arr, size_arr, x);

    if (x_pos < 0)
    {
        printf("NESSUN VALORE %d TROVATO IN ARR\n", x);
    }
    else
    {
        printf("IL VALORE %d SI TROVA IN POSIZIONE %d IN ARR\n", x, x_pos);
    }

    // ORDINAMENTO ARRAY
    selection_sort(arr, size_arr);

    // STAMPA A VIDEO ARR ORDINATO
    printf("ARR ORDINATO IN ORDINE CRESCENTE: ");
    print_array(arr, size_arr);

    // DETERMINAZIONE DELL'ARRAY DELLE OCCORRENZE DI ARR
    int occur_arr[size_arr];
    occurrencies(arr, size_arr, occur_arr);
    printf("OCCUR_ARR: ");
    print_array(occur_arr, size_arr);

    return 0;
}

// ASSEGNO VALORI CASUALI COMPRESI TRA 0 E 9 A TUTTI GLI ELEMENTI DI ARR
void initialize_array(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 10;
    }
}

// STAMPA A VIDEO TUTTI GLI ELEMENTI DI ARR
void print_array(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");
}

// RICERCA LINEARE DEL VALORE VALUE IN ARR; RITORNA LA POSIZIONE DI VALUE IN ARR, -1 ALTRIMENTI
int linear_search(int arr[], int size, int value)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == value)
        {
            return i;
        }
    }

    return -1;
}

// ORDINAMENTO ARRAY IN ORDINE CRESCENTE CON SELECTION SORT
void selection_sort(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int min = i;

        for (int j = i + 1; j < size; j++)
        {
            if (arr[j] < arr[min])
            {
                min = j;
            }
        }

        swap(arr, i, min);
    }
}

// SCAMBIO GLI ELEMENTI IN POSIZIONE I e J DI ARR
void swap(int arr[], int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

// OCCUR E' L'ARRAY DELLE OCCORRENZE DI ARR
// ESEMPIO: OCCUR[4] AVRA' VALORE PARI AL NUMERO DI ELEMENTI
//          UGUALI A 4 PRESENTI IN ARR
void occurrencies(int arr[], int size, int occur[])
{
    // INIZIALIZZAZIONE DI OCCUR
    // VIENE ASSEGNATO VALORE 0 A TUTTI I SUOI ELEMENTI
    memset(occur, 0, size * sizeof(int));

    for (int i = 0; i < size; i++)
    {
        occur[arr[i]]++;
    }
}