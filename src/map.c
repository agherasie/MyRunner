/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** map.c
*/

#include "my_runner.h"

void skip_buffer(char **buffer)
{
    while (**buffer < '0' || **buffer > '9')
        *buffer += 1;
}

int count_lines(char *buffer)
{
    int count = 0;
    for (int i = 0; buffer[i] != 'x'; i++)
        if (buffer[i] == '\n')
            count++;
    return count;
}

int count_columns(char *buffer)
{
    int count = 0;
    for (int i = 0; buffer[i] != '\n'; i++)
        count++;
    return count;
}

char **map_fill(game *g, char *buffer)
{
    char **map = malloc(sizeof(char *) * (g->height + 1));
    for (int i = 0; i < g->height; i++)
        map[i] = malloc(sizeof(char) * (g->width + 1));
    map[g->height] = NULL;
    for (int i = 0; i < g->height; i++) {
        for (int j = 0; j < g->width; j++) {
            skip_buffer(&buffer);
            map[i][j] = *buffer - 48;
            buffer++;
        }
        map[i][g->width] = '\0';
    }
    return map;
}

char **create_map(char *filepath, game *g)
{
    int file = open(filepath, O_RDONLY);
    if (file == - 1)
        sfRenderWindow_close(g->window);
    char *buffer = malloc(sizeof(char) * 100000);
    read(file, buffer, 100000);
    close(file);
    g->height = count_lines(buffer);
    g->width = count_columns(buffer);
    char **map = map_fill(g, buffer);
    for (int i = 0; i < g->height; i++)
        for (int j = 0; j < g->width; j++)
            tile_interpretor(map, i, j);
    for (int i = 0; i < g->height; i++)
        for (int j = 0; j < g->width; j++)
            tile_interpretor(map, i, j);
    return map;
}
