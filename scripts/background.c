/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** background.c
*/

#include "my_runner.h"

void scroll_parallax(game *g, player *p, object *plx, float speed)
{
    if (plx->pos.x <= -plx->rect.width * 2.5f)
        plx->pos.x += plx->rect.width * 2.5f;
    plx->scale.x = 2.5f;
    plx->scale.y = 2.5f;
    if (g->paused == sfFalse || p->goal_reached == sfFalse)
        plx->pos.x -= speed;
    sfSprite_setScale(plx->spr, plx->scale);
    sfSprite_setPosition(plx->spr, plx->pos);
    sfRenderWindow_drawSprite(g->window, plx->spr, NULL);
    sfVector2f pos = {plx->pos.x + plx->rect.width * 2.5f, plx->pos.y};
    sfSprite_setPosition(plx->spr, pos);
    sfRenderWindow_drawSprite(g->window, plx->spr, NULL);
}

void update_background(game *g, player *p)
{
    if (g->level == 1) {
        if (g->frame % 10 == 0)
            g->plx[3]->rect.top += g->plx[3]->rect.height;
        sfSprite_setTextureRect(g->plx[3]->spr, g->plx[3]->rect);
        scroll_parallax(g, p, g->plx[3], 0.4f * g->camera_pan_speed + 0.2f);
        scroll_parallax(g, p, g->plx[0], 0.1f);
        scroll_parallax(g, p, g->plx[1], 0.2f * g->camera_pan_speed);
        scroll_parallax(g, p, g->plx[2], 0.3f * g->camera_pan_speed);
    }
    if (g->level == 2) {
        scroll_parallax(g, p, g->plx[4], 0.1f * g->camera_pan_speed);
        scroll_parallax(g, p, g->plx[5], 0.2f * g->camera_pan_speed + 0.05f);
        scroll_parallax(g, p, g->plx[6], 0.5f * g->camera_pan_speed + 0.75f);
    }
    if (g->level == 3 || g->level == 0) {
        scroll_parallax(g, p, g->plx[7], 0.1f * g->camera_pan_speed + 0.1f);
        scroll_parallax(g, p, g->plx[8], 0.2f * g->camera_pan_speed);
        scroll_parallax(g, p, g->plx[9], 0.3f * g->camera_pan_speed);
        scroll_parallax(g, p, g->plx[10], 0.4f * g->camera_pan_speed);
    }
    sfVector2i mappos = {0, 0};
    sfVector2f tilepos = {0, 0};
    if (g->is_main_menu == sfTrue
    || (g->paused == sfTrue && g->pause_frame >= 250))
        return;
    for (int i = 0; i < g->height; i++)
        for (int j = 0; j < g->width; j++) {
            mappos.x = j;
            mappos.y = i;
            update_tile(g, p, &tilepos, mappos);
        }
}