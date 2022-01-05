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
    if (*id >= 0 && *id <= 99) {
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
