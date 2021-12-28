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
    if (map[y][x] == 2 && map[y - 1][x] == 0)
        map[y][x] = 3;
    if (x > 3 && y < 5 && map[y + 1][x] == 3 && map[y][x] == 0
    && map[y][x - 1] == 2 && map[y][x + 1] == 2)
        map[y][x] = 5;
    if (map[y][x] == 0 && y == 5)
        map[y][x] = 6;
}

void update_tile(game *g, player *p, sfVector2f *tilepos, sfVector2i mappos)
{
    if (g->map[mappos.y][mappos.x] >= 0 && g->map[mappos.y][mappos.x] <= 9) {
        tilepos->x = mappos.x * 100 - g->camera_pan_x;
        tilepos->y = mappos.y * 100;
        g->tile->rect.top = 0;
        g->tile->rect.left = 50 * g->map[mappos.y][mappos.x];
        draw_tile(g, g->tile->spr, *tilepos);
        if (g->map[mappos.y][mappos.x] == 3) {
            g->tile->rect.left += 50;
            tilepos->y -= 100;
            draw_tile(g, g->tile->spr, *tilepos);
        }
    }
}
