/*
** EPITECH PROJECT, 2021
** my_strlen.c
** File description:
** alexandrugherasie
*/

int my_strlen(char const *str)
{
    int strlen = 0;
    for (str; *str != '\0'; str++) {
        strlen++;
    }
    return strlen;
}
