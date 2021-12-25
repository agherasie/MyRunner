/*
** EPITECH PROJECT, 2021
** scripts
** File description:
** score.c
*/

#include "my.h"
#include "fcntl.h"

void get_score(int *hiscore)
{
    char buff[255];
    int fp = open("data/score.txt", O_RDONLY);
    if (fp != -1) {
        read(fp, buff, 255);
        *hiscore = my_getnbr(buff);
        close(fp);
    }
    return;
}

void set_score(int *hiscore)
{
    int fp = open("data/score.txt", O_WRONLY);
    if (fp != -1) {
        write(fp, my_itoa(*hiscore), my_strlen(my_itoa(*hiscore)));
        close(fp);
    }
    return;
}