#include <stdlib.h>
#include <stdio.h>
#include <math.h>

float delta(float a, float b, float c);
int eq_secondo_grado(float a, float b, float c, float *soluzioni);
float eq_primo_grado(float m, float q);

int main(void)
{
    float a, b, c;
    float soluzioni[2];

    printf("ax^2 + bx + c = 0\n");

    printf("a: ");
    scanf("%f", &a);
    printf("b: ");
    scanf("%f", &b);
    printf("c: ");
    scanf("%f", &c);

    if (a == 0 && b == 0)
    {
        if (c == 0)
        {
            printf("0 = 0\nVero per ogni x in R\n");
        }
        else
        {
            printf("%f = 0\nImpossibile\n", c);
        }
    }
    else if (a == 0)
    {
        // CASO: EQUAZIONE DI PRIMO GRADO
        soluzioni[0] = eq_primo_grado(b, c);
        printf("%fx + %f = 0\nx = %f\n", b, c, soluzioni[0]);
    }
    else
    {
        // CASO: EQUAZIONE DI SECONDO GRADO
        printf("%fx^2 + %fx + %f = 0\n", a, b, c);

        if (!eq_secondo_grado(a, b, c, soluzioni))
        {
            printf("x1 = %f\tx2 = %f\n", soluzioni[0], soluzioni[1]);
        }
        else
        {
            printf("Non ha soluzione in R\n");
        }
    }

    return 0;
}

float delta(float a, float b, float c)
{
    return b * b - 4 * a * c;
}

// CALCOLA LE RADICI DI UN POLINOMIO DI SECONDO GRADO
// RITORNA 0 SE HA SOLUZIONE NEI REALI
// RITORNA -1 ALTRIMENTI
int eq_secondo_grado(float a, float b, float c, float *soluzioni)
{
    float d = delta(a, b, c);

    if (d < 0)
    {
        return -1;
    }

    soluzioni[0] = (-1 * b - sqrt(d)) / (2 * a);
    soluzioni[1] = (-1 * b + sqrt(d)) / (2 * a);

    return 0;
}

// CALCOLA LA SOLUZIONE DI UN POLINOMIO DI PRIMO GRADO
float eq_primo_grado(float m, float q)
{
    return -1 * q / m;
}