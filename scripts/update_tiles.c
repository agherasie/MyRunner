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

void update_tile(game *g, player *p, sfVector2f *tilepos, sfVector2i mappos)
{
    if (g->map[mappos.y][mappos.x] >= 0 && g->map[mappos.y][mappos.x] <= 9) {
        if (g->map[mappos.y][mappos.x] == 2
        && g->map[mappos.y - 1][mappos.x] == 0)
            g->map[mappos.y][mappos.x] = 3;
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
