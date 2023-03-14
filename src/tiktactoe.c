#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define N 3

void print_grid(char grid[N][N]);
bool check_grid(char grid[N][N]);
bool rows(char grid[N][N]);
bool columns(char grid[N][N]);
bool left_diagonal(char grid[N][N]);
bool right_diagonal(char grid[N][N]);

int main(void)
{
    // DEFINIZIONE DI GRID, UNA MATRICE QUADRATA NxN
    char grid[N][N];

    // INIZIALIZZAZIONE DELLA MATRICE
    // AD OGNI ELEMENTO VIENE ASSEGNATO UN CARATTERE SPAZIO
    memset(grid, (int)' ', sizeof(grid));

    // 'X' <- PLAYER 1
    // 'O' <- PLAYER 2
    char signs[] = {'X', 'O'};

    // NUMERO DI SPAZI LIBERI NELLA TABELLA
    int free_spaces = N * N;

    // SE CURRENT_PLAYER E' UGUALE AD 1 ALLORA E' IL TURNO DI PLAYER 1
    // SE E' UGUALE A 2 E' TURNO DI PLAYER 2
    int current_player = 1;
    int player_choice[2];

    while (free_spaces > 0)
    {
        // AD OGNI TURNO VIENE STAMPATA A VIDEO LA TABELLA
        print_grid(grid);

        // PLAYER DEVE SCEGLIERE UNA CASELLA LIBERA
        // INSERENDO IN INPUT NUMERO DI RIGA E COLONNA DELLA CASELLA
        printf("Player %d | Scegli una casella libera.\n", current_player);
        printf("Player %d | Riga (1 - %d): ", current_player, N);
        scanf("%d", &player_choice[0]);
        printf("Player %d | Colonna (1 - %d): ", current_player, N);
        scanf("%d", &player_choice[1]);

        // CONTROLLO SE GLI INPUT DA TASTIERA SONO VALIDI
        // IN CASO DI INPUT ERRATI IL PLAYER DOVRA' REIMMETTERNE DI NUOVI
        if (player_choice[0] < 1 || player_choice[0] > 3 ||
            player_choice[1] < 1 || player_choice[1] > 3 ||
            grid[player_choice[0] - 1][player_choice[1] - 1] != ' ')
        {
            printf("Player %d | Seleziona una casella valida!\n\n\n", current_player);
            continue;
        }

        // VIENE ASSEGNATO IL VALORE TESTA O CROCE ALLA CASELLA SCELTA
        grid[player_choice[0] - 1][player_choice[1] - 1] = signs[current_player - 1];

        // CONTROLLO SE CI SONO CONFIGURAZIONI VINCENTI NELLA TABELLA
        // SE PRESENTI, LA PARTITA TERMINA CON UNO DEI 2 PLAYER COME VINCITORE
        if (check_grid(grid))
            break;

        // CONTATORE CHE TIENE TRACCIA DI QUANTI SPAZI VUOTI SONO RIMASTI
        // VIENE DECREMENTATO DI 1 OGNI QUAL VOLTA VIENE OCCUPATA UNA CASELLA
        // SE IL CONTATORE ARRIVA A ZERO LA PARTITA TERMINA CON UN PAREGGIO
        free_spaces--;

        // A FINE DI OGNI TURNO VIENE FATTO A CAMBIO CON L'ALTRO PLAYER
        if (current_player == 1)
            current_player = 2;
        else
            current_player = 1;

        printf("\n\n\n");
    }

    print_grid(grid);

    if (free_spaces <= 0)
        printf("Pareggio!\n");
    else if (current_player == 1)
        printf("Player 1 ha vinto! ggwp\n");
    else
        printf("Player 2 ha vinto! ggwp\n");

    return 0;
}

// STAMPA A VIDEO LA TABELLA
void print_grid(char grid[N][N])
{
    for (int i = 1; i <= N; i++)
    {
        printf(" %d  ", i);
    }

    printf("\n");

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf(" %c ", grid[i][j]);

            if (j != N - 1)
                printf("|");
        }

        printf(" %d\n", i + 1);

        if (i != N - 1)
            printf("---+---+---\n");
    }
}

// RICERCA PER POSSIBILI CONFIGURAZIONI VINCENTI NELLA TABELLA
// RITORNA 1 SE TROVA UNA CONFIGURAZIONE VALIDA
// RITORNA 0 ALTRIMENTI
bool check_grid(char grid[N][N])
{
    return rows(grid) ||
           columns(grid) ||
           left_diagonal(grid) ||
           right_diagonal(grid);
}

// RICERCA CONFIGURAZIONI VINCENTI PER RIGHE
// RITORNA VERO SE TROVA UNA CONFIGURAZIONE VALIDA
// RITORNA FALSO ALTRIMENTI
bool rows(char grid[N][N])
{
    bool valid_config;

    for (int i = 0; i < N; i++)
    {
        valid_config = true;

        for (int j = 0; j < N - 1; j++)
        {
            if (grid[i][j] == ' ' || grid[i][j] != grid[i][j + 1])
            {
                valid_config = false;
                break;
            }
        }

        if (valid_config)
            return true;
    }

    return false;
}

// RICERCA CONFIGURAZIONI VINCENTI PER COLONNE
// RITORNA VERO SE TROVA UNA CONFIGURAZIONE VALIDA
// RITORNA FALSO ALTRIMENTI
bool columns(char grid[N][N])
{
    bool valid_config;

    for (int i = 0; i < N; i++)
    {
        valid_config = true;

        for (int j = 0; j < N - 1; j++)
        {
            if (grid[j][i] == ' ' || grid[j][i] != grid[j + 1][i])
            {
                valid_config = false;
                break;
            }
        }

        if (valid_config)
            return true;
    }

    return false;
}

// RICERCA CONFIGURAZIONE VINCENTE PER DIAGONALE SINISTRA
// RITORNA VERO SE TROVA UNA CONFIGURAZIONE VALIDA
// RITORNA FALSO ALTRIMENTI
bool left_diagonal(char grid[N][N])
{
    for (int i = 0; i < N - 1; i++)
    {
        if (grid[i][i] == ' ' ||
            grid[i][i] != grid[i + 1][i + 1])
            return false;
    }

    return true;
}

// RICERCA CONFIGURAZIONE VINCENTE PER DIAGONALE DESTRA
// RITORNA VERO SE TROVA UNA CONFIGURAZIONE VALIDA
// RITORNA FALSO ALTRIMENTI
bool right_diagonal(char grid[N][N])
{
    for (int i = 0; i < N - 1; i++)
    {
        if (grid[i][N - 1 - i] == ' ' ||
            grid[i][N - 1 - i] != grid[i + 1][N - 2 - i])
            return false;
    }

    return true;
}