/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** background.c
*/

#include "my_runner.h"

void scroll_parallax(game *g, player *p, object *parallax, float speed)
{
    if (parallax->pos.x <= -parallax->rect.width * 2.5f)
        parallax->pos.x += parallax->rect.width * 2.5f;
    parallax->scale.x = 2.5f;
    parallax->scale.y = 2.5f;
    if (g->paused == sfFalse || p->goal_reached == sfFalse)
        parallax->pos.x -= speed;
    sfSprite_setScale(parallax->spr, parallax->scale);
    sfSprite_setPosition(parallax->spr, parallax->pos);
    sfRenderWindow_drawSprite(g->window, parallax->spr, NULL);
    sfSprite_setPosition(parallax->spr, (sfVector2f) {parallax->pos.x + parallax->rect.width * 2.5f, parallax->pos.y});
    sfRenderWindow_drawSprite(g->window, parallax->spr, NULL);
}

void update_background(game *g, player *p)
{
    if (g->frame % 10 == 0)
        g->parallax3->rect.top += g->parallax3->rect.height;
    sfSprite_setTextureRect(g->parallax3->spr, g->parallax3->rect);
    scroll_parallax(g, p, g->parallax3, 0.4f * g->camera_pan_speed + 0.2f);
    scroll_parallax(g, p, g->parallax0, 0.1f);
    scroll_parallax(g, p, g->parallax1, 0.2f * g->camera_pan_speed);
    scroll_parallax(g, p, g->parallax2, 0.3f * g->camera_pan_speed);
    sfVector2i mappos = {0, 0};
    sfVector2f tilepos = {0, 0};
    for (int i = 0; i < g->height && g->is_main_menu == sfFalse && (g->paused == sfFalse || g->pause_frame < 250); i++)
        for (int j = 0; j < g->width; j++) {
            mappos.x = j;
            mappos.y = i;
            update_tile(g, p, &tilepos, mappos);
        }
}