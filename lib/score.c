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
        int i = 0;
        for (i; buff[i] != 'x'; i++);
        buff[i] = '\0';
        *hiscore = my_getnbr(buff);
        close(fp);
    }
    return;
}

void set_score(int *hiscore)
{
    int fp = open("data/score.txt", O_WRONLY);
    if (fp != -1) {
        char *output = malloc(sizeof(char) * (my_strlen(my_itoa(*hiscore) + 2)));
        my_strcpy(output, my_itoa(*hiscore));
        output[my_strlen(output)] = 'x';
        output[my_strlen(output)] = '\0';
        write(fp, output, my_strlen(output));
        close(fp);
    }
    return;
}