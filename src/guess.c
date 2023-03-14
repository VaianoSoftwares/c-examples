#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

int main(void)
{
    // RANDOM SEED GENERATOR
    srand(time(NULL));

    // NUMERO RANDOM DA INDOVINARE
    int num_to_guess = (rand() % 99) + 1;
    // NUMERO DI TENTATIVI IMPIEGATI PER INDOVINARE IL NUMERO
    int attempts = 0;

    int user_guess;

    do
    {
        // INSERIMENTO IN INPUT DA TASTIERA DI UN INTERO COMPRESO TRA 1 E 99
        printf("Scegli un numero compreso tra 1 e 99: ");
        scanf("%d", &user_guess);

        if (user_guess > num_to_guess)
        {
            printf("Troppo grande!\n");
        }
        else if (user_guess < num_to_guess)
        {
            printf("Troppo piccolo!\n");
        }

        ++attempts;
    } while (user_guess != num_to_guess);

    printf("Vittoria epica royale!\nHai indovinato in %d tentativi.\n", attempts);

    return 0;
}
