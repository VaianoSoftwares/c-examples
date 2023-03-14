#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_IMPIEGATI 10
#define STR_LEN 64
#define N_ATTRS 5

typedef unsigned short u16;

typedef enum Mansione
{
    INSERVIENTE = 1,
    MANAGER,
    UFFICIO,
} Mansione;

typedef enum TipoBonus
{
    SOMMA = 1,
    PERCENTUALE
} TipoBonus;

typedef struct Impiegato
{
    int id;
    char nome[STR_LEN];
    char cognome[STR_LEN];
    float stipendio;
    Mansione mansione;
} Impiegato;

static char *IMPIEGATI_ATTRS[N_ATTRS] = {"ID", "NOME", "COGNOME", "STIPENDIO(euro)", "MANSIONE"};

void print_impiegati(Impiegato impiegati[], u16 size);
void set_values_length(Impiegato impiegati[], u16 size, int lengths[]);
void set_cols_width(int values_len[], int cols_width[]);
void print_n_chars(char c, int n);
void print_row_separator(int widths[]);
void print_table_header(int widths[]);
void print_table_body(Impiegato impiegati[], u16 size, int cols_width[]);
bool add_impiegato(Impiegato impiegati[], u16 *size);
bool remove_impiegato(Impiegato impiegati[], u16 *size, int id);
void swap(Impiegato *imp1, Impiegato *imp2);
float media_stipendi(Impiegato impiegati[], u16 size);
bool promozione(Impiegato impiegati[], u16 size, int id, float aumento, TipoBonus tipo_bonus);
void sort_by_name(Impiegato impiegati[], u16 size);

int main(void)
{
    Impiegato impiegati[MAX_IMPIEGATI];
    u16 size = 0;

    int choice, id;
    float aumento;
    TipoBonus tipo_bonus;
    bool success;

    do
    {
        print_impiegati(impiegati, size);

        printf("====================================\n");
        printf("1 - Aggiungi dipendente\n");
        printf("2 - Rimuovi dipendente\n");
        printf("3 - Media stipendi\n");
        printf("4 - Promozione dipendente\n");
        printf("5 - Ordinamento dipendenti\n");
        printf("Selezionare 0 per uscire.........\n");
        printf("====================================\n");
        printf("Scelta: ");
        scanf("%d", &choice);

        system("clear");

        switch (choice)
        {
        case 1:
            success = add_impiegato(impiegati, &size);
            if (success)
                printf("Dipendente inserito con successo.\n");
            else
                printf("Impossibile inserire dipendente.\n");
            break;
        case 2:
            printf("Rimozione dipendente | Digitare ID Dipendente: ");
            scanf("%d", &id);

            success = remove_impiegato(impiegati, &size, id);
            if (success)
                printf("Dipendente rimosso con successo.\n");
            else
                printf("Impossibile rimuovere dipendente.\n");
            break;
        case 3:
            printf("Media stipendi: %.2f euro\n", media_stipendi(impiegati, size));
            break;
        case 4:
            printf("Promozione dipendente | Digitare ID Dipendente: ");
            scanf("%d", &id);

            printf("Promozione dipendente | Digitare aumento: ");
            scanf("%f", &aumento);

            printf("Promozione dipendente | Digitare tipo bonus (1-somma 2-percentuale): ");
            scanf("%d", &tipo_bonus);

            success = promozione(impiegati, size, id, aumento, tipo_bonus);
            if (success)
                printf("Promozione dipedente effettuata.\n");
            else
                printf("Impossibile effettuare promozione.\n");
            break;
        case 5:
            sort_by_name(impiegati, size);
            break;
        }

        getchar();
        printf("Premere un tasto per continuare.........");
        getchar();
        system("clear");
    } while (choice);

    return 0;
}

void print_impiegati(Impiegato impiegati[], u16 size)
{
    if (size <= 0)
    {
        printf("Lista impiegati vuota\n");
        return;
    }

    int values_max_len[N_ATTRS];
    int cols_max_width[N_ATTRS];

    set_values_length(impiegati, size, values_max_len);
    set_cols_width(values_max_len, cols_max_width);

    print_row_separator(cols_max_width);
    print_table_header(cols_max_width);
    print_row_separator(cols_max_width);
    print_table_body(impiegati, size, cols_max_width);
    print_row_separator(cols_max_width);
}

void set_values_length(Impiegato impiegati[], u16 size, int lengths[])
{
    int tmp_len;
    char buf[STR_LEN];

    memset(lengths, 0, sizeof(int) * N_ATTRS);

    lengths[N_ATTRS - 1] = 11;

    for (int i = 0; i < size; i++)
    {
        memset(buf, 0, sizeof(buf));
        snprintf(buf, sizeof(buf), "%d", impiegati[i].id);
        tmp_len = strlen(buf);
        if (tmp_len > lengths[0])
            lengths[0] = tmp_len;

        tmp_len = strlen(impiegati[i].nome);
        if (tmp_len > lengths[1])
            lengths[1] = tmp_len;

        tmp_len = strlen(impiegati[i].cognome);
        if (tmp_len > lengths[2])
            lengths[2] = tmp_len;

        memset(buf, 0, sizeof(buf));
        snprintf(buf, sizeof(buf), "%.2f", impiegati[i].stipendio);
        tmp_len = strlen(buf);
        if (tmp_len > lengths[3])
            lengths[3] = tmp_len;
    }
}

void set_cols_width(int values_len[], int cols_width[])
{
    int attr_len;

    for (int i = 0; i < N_ATTRS; i++)
    {
        attr_len = strlen(IMPIEGATI_ATTRS[i]);
        cols_width[i] = (values_len[i] > attr_len) ? values_len[i] : attr_len;
    }
}

void print_n_chars(char c, int n)
{
    for (int i = 0; i < n; i++)
        printf("%c", c);
}

void print_row_separator(int widths[])
{
    int n_chars;

    for (int i = 0; i < N_ATTRS; i++)
    {
        printf("+");
        n_chars = widths[i] + 2;
        print_n_chars('-', n_chars);
    }
    printf("+\n");
}

void print_table_header(int widths[])
{
    int tmp_len, spaces;

    for (int i = 0; i < N_ATTRS; i++)
    {
        tmp_len = strlen(IMPIEGATI_ATTRS[i]);
        spaces = widths[i] + 1 - tmp_len;

        printf("| %s", IMPIEGATI_ATTRS[i]);
        print_n_chars(' ', spaces);
    }
    printf("|\n");
}

void print_table_body(Impiegato impiegati[], u16 size, int cols_width[])
{
    int spaces;
    char buf[STR_LEN];

    for (int i = 0; i < size; i++)
    {
        snprintf(buf, sizeof(buf), "%d", impiegati[i].id);
        spaces = cols_width[0] - strlen(buf) + 1;
        printf("| %d", impiegati[i].id);
        print_n_chars(' ', spaces);

        spaces = cols_width[1] - strlen(impiegati[i].nome) + 1;
        printf("| %s", impiegati[i].nome);
        print_n_chars(' ', spaces);

        spaces = cols_width[2] - strlen(impiegati[i].cognome) + 1;
        printf("| %s", impiegati[i].cognome);
        print_n_chars(' ', spaces);

        snprintf(buf, sizeof(buf), "%.2f", impiegati[i].stipendio);
        spaces = cols_width[3] - strlen(buf) + 1;
        printf("| %.2f", impiegati[i].stipendio);
        print_n_chars(' ', spaces);

        printf("| ");
        switch (impiegati[i].mansione)
        {
        case INSERVIENTE:
            printf("inserviente");
            break;
        case MANAGER:
            printf("manager    ");
            break;
        case UFFICIO:
            printf("ufficio    ");
            break;
        }
        printf(" |\n");
    }
}

bool add_impiegato(Impiegato impiegati[], u16 *size)
{
    static int impiegati_id = 100;
    char buf[STR_LEN];
    int len_buf;

    if (*size >= MAX_IMPIEGATI)
        return false;

    impiegati[*size].id = impiegati_id++;

    getchar();

    memset(buf, 0, sizeof(buf));

    printf("Impiegato %d | Inserire nome: ", impiegati[*size].id);
    fgets(buf, STR_LEN, stdin);

    len_buf = strlen(buf) - 1;
    buf[len_buf] = 0;
    strncpy(impiegati[*size].nome, buf, len_buf + 1);

    memset(buf, 0, sizeof(buf));

    printf("Impiegato %d | Inserire cognome: ", impiegati[*size].id);
    fgets(buf, STR_LEN, stdin);

    len_buf = strlen(buf) - 1;
    buf[len_buf] = 0;
    strncpy(impiegati[*size].cognome, buf, len_buf + 1);

    printf("Impiegato %d | Inserire stipendio: ", impiegati[*size].id);
    scanf("%f", &impiegati[*size].stipendio);

    printf("Impiegato %d | Inserire mansione (1-inserviente, 2-manager, 3-ufficio): ", impiegati[*size].id);
    scanf("%d", &impiegati[*size].mansione);

    ++(*size);
    return true;
}

bool remove_impiegato(Impiegato impiegati[], u16 *size, int id)
{
    for (int i = 0; i < *size; i++)
    {
        if (impiegati[i].id == id)
        {
            swap(&impiegati[i], &impiegati[*size - 1]);
            --(*size);
            return true;
        }
    }

    return false;
}

void swap(Impiegato *imp1, Impiegato *imp2)
{
    Impiegato temp = *imp1;
    *imp1 = *imp2;
    *imp2 = temp;
}

float media_stipendi(Impiegato impiegati[], u16 size)
{
    float sum = 0.0f;

    for (int i = 0; i < size; i++)
        sum += impiegati[i].stipendio;

    return (size > 0) ? (sum / size) : 0.0f;
}

bool promozione(Impiegato impiegati[], u16 size, int id, float aumento, TipoBonus tipo_bonus)
{
    for (int i = 0; i < size; i++)
    {
        if (impiegati[i].id == id)
        {
            switch (tipo_bonus)
            {
            case SOMMA:
                impiegati[i].stipendio += aumento;
                break;
            case PERCENTUALE:
                float aumento_percentuale = impiegati[i].stipendio * aumento / 100;
                impiegati[i].stipendio += aumento_percentuale;
                break;
            default:
                return false;
            }

            return true;
        }
    }

    return false;
}

void sort_by_name(Impiegato impiegati[], u16 size)
{
    int min, surname_cmp, name_cmp;

    for (int i = 0; i < size - 1; i++)
    {
        min = i;

        for (int j = i + 1; j < size; j++)
        {
            surname_cmp = strcmp(impiegati[i].cognome, impiegati[j].cognome);
            name_cmp = strcmp(impiegati[i].nome, impiegati[j].nome);

            if (surname_cmp > 0 || (surname_cmp == 0 && name_cmp > 0))
                min = j;
        }

        swap(&impiegati[i], &impiegati[min]);
    }
}