/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** map.c
*/

#include "my_runner.h"

void update_tile(game *g, player *p, sfVector2f *tilepos, sfVector2i mappos)
{
    if (g->map[mappos.y][mappos.x] >= 0 && g->map[mappos.y][mappos.x] <= 9) {
        tilepos->x = mappos.x * 100 - g->camera_pan_x;
        tilepos->y = mappos.y * 100;
        g->tile->rect.top = 0;
        g->tile->rect.left = 50 * g->map[mappos.y][mappos.x];
        sfSprite_setPosition(g->tile->spr, *tilepos);
        sfSprite_setTextureRect(g->tile->spr, g->tile->rect);
        sfRenderWindow_drawSprite(g->window, g->tile->spr, NULL);
    }
}

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

char **create_map(char *filepath, game *g)
{
    int file = open(filepath, O_RDONLY);
    if (file == - 1)
        sfRenderWindow_close(g->window);
    char *buffer = malloc(sizeof(char) * 1000);
    read(file, buffer, 1000);
    close(file);
    g->height = count_lines(buffer);
    g->width = count_columns(buffer);
    char **map = malloc(sizeof(char *) * (g->height + 1));
    for (int i = 0; i < 6; i++)
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
