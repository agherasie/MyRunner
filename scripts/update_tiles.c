/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** update_tiles.c
*/

#include "my_runner.h"

void draw_tile(game *g, sfSprite *spr, sfVector2f pos)
{
    sfSprite_setPosition(g->tile->spr, pos);
    sfSprite_setTextureRect(g->tile->spr, g->tile->rect);
    sfRenderWindow_drawSprite(g->window, g->tile->spr, NULL);
}

void tile_interpretor(char **map, int y, int x)
{
    int maxy = 0;
    for (maxy; map[maxy] != NULL; maxy++);
    if (map[y][x] == 2 && map[y - 1][x] == 0)
        map[y][x] = 3;
    if (x > 3 && y < maxy - 1 && map[y + 1][x] == 3 && map[y][x] == 0
    && map[y][x - 1] == 2 && map[y][x + 1] == 2)
        map[y][x] = either_or(100, 5);
    if (map[y][x] == 5)
        return;
    if (y > 2 && y < maxy - 1 && map[y + 1][x] == 3
    && is_solid(map[y + 1][x]) == 0
    && is_solid(map[y][x + 1]) == 0 && is_solid(map[y - 1][x + 1]) == 0)
        if (is_solid(map[y - 3][x + 1]) == 0)
            map[y][x] = 102;
        else
            map[y][x] = 100;
    if (y < maxy - 1 && map[y + 1][x] == 3 && map[y][x - 1] == 2
    && is_solid(map[y][x + 1]) == 1 && is_solid(map[y][x + 2]) == 1)
        map[y][x] = 104;
    if (map[y][x] == 0 && y == maxy - 1)
        map[y][x] = 6;
}

void draw_game_object(game *g, sfVector2i mappos, char object)
{
    sfIntRect rect = (sfIntRect) {50 * (object % 100), 50 * 3, 50, 50};
    sfSprite_setTextureRect(g->ring->spr, rect);
    g->ring->pos.x = mappos.x * 100 - g->camera_pan.x;
    g->ring->pos.y = mappos.y * 100 - g->camera_pan.y;
    sfSprite_setPosition(g->ring->spr, g->ring->pos);
    sfRenderWindow_drawSprite(g->window, g->ring->spr, NULL);
}

void update_tile(game *g, player *p, sfVector2f *tilepos, sfVector2i mappos)
{
    char *id = &g->map[mappos.y][mappos.x];
    if (*id >= 0 && *id <= 9) {
        tilepos->x = mappos.x * 100 - g->camera_pan.x;
        tilepos->y = mappos.y * 100 - g->camera_pan.y;
        g->tile->rect.top = 50 * (g->level - 1);
        g->tile->rect.left = 50 * *id;
        draw_tile(g, g->tile->spr, *tilepos);
        if (*id == 3) {
            g->tile->rect.left += 50;
            tilepos->y -= 100;
            draw_tile(g, g->tile->spr, *tilepos);
        }
    }
    if (*id >= 100) {
        if (p->cooldown < 0 && *id % 2 != 0)
            *id -= 1;
        draw_game_object(g, mappos, *id);
    }
}
