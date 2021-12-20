/*
** EPITECH PROJECT, 2021
** my_putstr.c
** File description:
** alexandrugherasie
*/

void my_putchar(char c);

int my_putstr(char const *str)
{
    for (str; *str != '\0'; str++) {
        my_putchar(*str);
    }
}
