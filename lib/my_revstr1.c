/*
** EPITECH PROJECT, 2021
** my_revstr.c
** File description:
** alexandrugherasie
*/

#include "my.h"

int my_revstr(char *str)
{
    int i = 0;
    int length = my_strlen(str);

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