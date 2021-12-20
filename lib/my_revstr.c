/*
** EPITECH PROJECT, 2021
** my_revstr.c
** File description:
** alexandrugherasie
*/

int my_strcount(char const *str)
{
    int strlen = 0;

    for (str; *str != '\0'; str++) {
        strlen++;
    }
    return strlen;
}

int my_revstr(char *str)
{
    int i = 0;
    int length = my_strcount(str);

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