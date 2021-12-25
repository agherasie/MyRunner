/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** background.c
*/

#include "my_runner.h"

void scroll_parallax(game *g, player *p, object *parallax, int speed)
{
    if (g->paused == sfFalse && p->goal_reached == sfFalse)
        if (g->frame % speed == 0)
            parallax->rect.left += g->camera_pan_speed;
    sfSprite_setTextureRect(parallax->spr, parallax->rect);
    sfRenderWindow_drawSprite(g->window, parallax->spr, NULL);
}

void update_background(game *g, player *p)
{
    g->frame++;
    scroll_parallax(g, p, g->parallax0, 3);
    scroll_parallax(g, p, g->parallax1, 2);
    sfVector2i mappos = {0, 0};
    sfVector2f tilepos = {0, 0};
    for (int i = 0; i < g->height; i++)
        for (int j = 0; j < g->width; j++) {
            mappos.x = j;
            mappos.y = i;
            update_tile(g, p, &tilepos, mappos);
        }
}