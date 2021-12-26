/*
** EPITECH PROJECT, 2021
** scripts
** File description:
** my_itoa.c
*/

#include "my.h"

int reverse(char *str, int length)
{
    int i = 0;

    while (i < length) {
        char temp;
        temp = str[i];
        str[i] = str[length - 1];
        str[length - 1] = temp;
        i++;
        length--;
    }
    return 0;
}

char *my_itoa(long nb)
{
    int nbr_len = number_of_digits(nb) + 1;
    char *result = malloc(sizeof(char) * (number_of_digits(nb) + 2));
    int i = 0;
    for (i; i < nbr_len; i++) {
        result[nbr_len - 1-  i] = nb % 10 + 48;
        nb = nb / 10;
    }
    result[i] = '\0';
    return result;
}
