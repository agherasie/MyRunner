/*
** EPITECH PROJECT, 2021
** random
** File description:
** random.c
*/

#include <time.h>
#include <stdlib.h>

int either_or(int either, int or)
{
    int max = 1;
    int min = 0;
    srand(time(NULL));
    int random = rand() % (max - min + 1) + max;
    if (random == 1)
        random = or;
    else
        random = either;
    return random;
}

int range(int min, int max)
{
    srand(time(NULL));
    int random = rand() % (max - min + 1) + min;
    return random;
}