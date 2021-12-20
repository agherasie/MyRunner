/*
** EPITECH PROJECT, 2021
** scripts
** File description:
** my_itoa.c
*/

#include "my.h"

char *my_itoa(long nb)
{
    int nbr_len = number_of_digits(nb) + 1;
    char *result = malloc(sizeof(char) * (number_of_digits(nb)) + 1);
    for (int i = 0; i < nbr_len; i++) {
        result[i] = nb % 10 + 48;
        nb = nb / 10;
    }
    result[nbr_len] = '\0';
    my_revstr(result);
    return result;
}
