/*
** EPITECH PROJECT, 2021
** B-MAT-100-LYN-1-1-101pong-alexandru.gherasie
** File description:
** base_conversions.c
*/

#include "my.h"
#include <stdlib.h>

char *base_conversion(long nb, int base, char ten)
{
    char *new_nb = malloc(sizeof(char) * (number_of_digits(nb) + 2));
    int count = 0;
    int digit = 0;
    int stored_char = 0;
    for (nb; nb > 0; nb /= base) {
        digit = nb % base;
        stored_char = '0' + digit;
        if (digit > 9)
            stored_char += ten - 58;
        new_nb[count] = stored_char;
        count++;
    }
    my_revstr(new_nb);
    return new_nb;
}

int to_octal(int nb)
{
    int new_nb = 0;
    int power_of_ten = 1;
    for (nb; nb > 0; nb /= 8) {
        new_nb += (nb % 8) * power_of_ten;
        power_of_ten *= 10;
    }
    return new_nb;
}

int to_binary(int nb)
{
    int new_nb = 0;
    int power_of_ten = 1;
    for (nb; nb > 0; nb /= 2) {
        new_nb += (nb % 2) * power_of_ten;
        power_of_ten *= 10;
    }
    return new_nb;
}