/*
** EPITECH PROJECT, 2021
** random
** File description:
** random.c
*/

#include <time.h>
#include <stdlib.h>

int either_or(int either, int orthis)
{
    int max = 1;
    int min = 0;
    int random = rand() % (max - min + 1) + max;
    if (random == 1)
        random = orthis;
    else
        random = either;
    return random;
}

int range(int min, int max)
{
    int random = rand() % (max - min + 1) + min;
    return random;
}
