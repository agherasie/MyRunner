/*
** EPITECH PROJECT, 2021
** B-CPE-100-LYN-1-1-cpoolday09-alexandru.gherasie
** File description:
** my.h
*/

#ifndef MY_H_
    #define MY_H_

    #include <stdlib.h>
    #include <time.h>
    #include <stdio.h>
    #include <unistd.h>

void my_putchar(char c);
int my_putstr(char const *str);
int my_revstr(char *str);
int my_strlen(char const *str);
int my_put_nbr(long nb);
int print_zero(int c, int c2);
int checks(int *nb);
int my_strcmp(char const *s1, char const *s2);
int my_getnbr(char const *str);
char *my_strcpy(char *dest, char const *src);
char *my_strncpy(char *dest, char const *src, int n);
int power_of_nbr(long number);
int number_of_digits(long number);
int power_of_ten(int count);
int is_num(char c);
char *base_conversion(long nb, int base, char ten);
int either_or(int either, int orthis);
int range(int min, int max);
char *my_itoa(long nb);
void get_score(int *hiscore);
void set_score(int *hiscore);

#endif /* MY_H_ */
