#include <stdlib.h>
#include <stdio.h>

int get_string_length(char str[]);
void concat_strings(char str1[], char str2[], char concat_str[]);
void to_upper_case(char str[]);
void to_lower_case(char str[]);

int main(void)
{
    // DEFINIZIONE ED INIZIALIZZAZIONE DI STR1 E STR2
    char str1[64] = "una stringa";
    char str2[] = " ed un'altra stringa";

    // OTTENGO LUNGHEZZA DI STR1 E STR2
    int str1_len = get_string_length(str1);
    int str2_len = get_string_length(str2);

    printf("str1 e' lunga: %d\nstr2 e' lunga: %d\n", str1_len, str2_len);

    // LUNGHEZZA DI STR3 = LUNGHEZZA DI STR1 + LUNGHEZZA DI STR2 + 1
    char str3[str1_len + str2_len + 1];

    // CONCATENO STR1 CON STR2 IN STR3
    concat_strings(str1, str2, str3);

    printf("str1: %s\nstr2: %s\nstr3: %s\n", str1, str2, str3);

    char str4[] = "lAstRA a sIGnA 420";
    char str5[] = "CAstiGLIon dE_PEpoLI";

    to_lower_case(str4);
    to_upper_case(str5);

    printf("str4: %s\nstr5: %s\n", str4, str5);

    return 0;
}

// LUNGHEZZA STRINGA DI STR
int get_string_length(char str[])
{
    int count = 0;

    // '\0' STA AD INDICARE IL CARATTERE DI FINE STRINGA
    // INCREMENTO COUNT FINCHE' NON RISCOSTRO IL CARATTERE DI FINE STRINGA
    while (str[count++] != '\0')
        ;

    return count;
}

// CONCATENO STR1 CON STR2 IN CONCAT_STR
void concat_strings(char str1[], char str2[], char concat_str[])
{
    int count = 0;

    // COPIO STR1 IN CONCAT_STR
    for (int i = 0; str1[i] != 0; i++)
    {
        concat_str[count++] = str1[i];
    }

    // COPIO STR2 IN CONCAT_STR
    for (int i = 0; str2[i] != 0; i++)
    {
        concat_str[count++] = str2[i];
    }

    // CARATTERE DI FINE STRINGA PER CONCAT_STR
    concat_str[count] = 0;
}

// TRASFORMO TUTTE LE LETTERE DI UNA STRINGA IN MAIUSCOLO
void to_upper_case(char str[])
{
    int i = 0;

    while (str[i++] != 0)
    {
        // 97 CORRISPONDE AL CARATTERE 'a', 122 CORRISPONDE AL CARATTERE 'z'
        // SE str[i] E' COMPRESO TRA 97 E 122 ALLORA E' UNA LETTERA MINUSCOLA
        // SOTTRARRE 32 EQUIVALE A TRASFORMARE UNA LETTERA MINUSCOLA IN UNA MAIUSCOLA
        if (str[i] >= 97 && str[i] <= 122)
        {
            str[i] -= 32;
        }
    }
}

// TRASFORMO TUTTE LE LETTERE DI UNA STRINGA IN MINUSCOLO
void to_lower_case(char str[])
{
    int i = 0;

    while (str[i++] != 0)
    {
        // 65 CORRISPONDE AL CARATTERE 'A', 90 CORRISPONDE AL CARATTERE 'Z'
        // SE str[i] E' COMPRESO TRA 65 E 90 ALLORA E' UNA LETTERA MINUSCOLA
        // AGGIUNGERE 32 EQUIVALE A TRASFORMARE UNA LETTERA MAIUSCOLA IN UNA MINUSCOLA
        if (str[i] >= 65 && str[i] <= 90)
        {
            str[i] += 32;
        }
    }
}