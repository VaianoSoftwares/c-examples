#include <stdlib.h>
#include <stdio.h>

#define MAX_LEN 17

int binary_to_base10(char *bit_sequence, int lenght);
void base10_to_binary(int number, char *bit_sequence);
int is_odd(int x);
int pow2(int exp);
int abs(int x);

int main(void)
{
    char bin_str1[] = "0011001000110111";
    printf("%s = %d\n", bin_str1, binary_to_base10(bin_str1, sizeof(bin_str1)));

    char bin_str2[MAX_LEN];
    base10_to_binary(-127, bin_str2);
    printf("%d = %s\n", -127, bin_str2);

    return 0;
}

// DATA UNA STRINGA DI BIT ESSA VIENE CONVERTITA NEL SUO VALORE CORRISPETTIVO IN DECIMALE
int binary_to_base10(char *bit_sequence, int lenght)
{
    int result = 0;

    for (int i = 1; bit_sequence[i] != 0; i++)
    {
        result += (int)(bit_sequence[i] - '0') * (pow2(lenght - 2 - i));
    }

    return (bit_sequence[0] == '0') ? result : -result;
}

// DATO UN INTERO IN BASE 10 ESSO VIENE CONVERTITO IN BINARIO
void base10_to_binary(int number, char *bit_sequence)
{
    bit_sequence[0] = (char)('0' + (number < 0));

    number = abs(number);

    for (int i = MAX_LEN - 2; i > 0; i--)
    {
        bit_sequence[i] = (char)('0' + is_odd(number));
        number >>= 1;
    }
}

// ritorna 1 se x e' dispari
// ritorna 0 altrimenti
int is_odd(int x)
{
    return x & 1;
}

// valore assoluto di x
int abs(int x)
{
    return (x < 0) ? -x : x;
}

// 2 elevato alla exp (2^exp)
int pow2(int exp)
{
    return 1 << exp;
}