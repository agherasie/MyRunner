/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** enemy.c
*/

#include "my_runner.h"

void update_enemies(game *g, player *p)
{
    for (int i = 0; i < 1; i++) {
        g->e[i].obj->pos.x -= g->camera_pan_speed;
        sfSprite_setPosition(g->e[i].obj->spr, g->e[i].obj->pos);
        if (g->e[i].is_dead == sfTrue) {
            g->e[i].obj->rect.top = 50;
            animate_object(g, g->e[i].obj, g->e[i].anim[1], &g->e[i].frame);
        } else {
            animate_object(g, g->e[i].obj, g->e[i].anim[0], &g->e[i].frame);
        }
        sfSprite_setTextureRect(g->e[i].obj->spr, g->e[i].obj->rect);
        sfRenderWindow_drawSprite(g->window, g->e[i].obj->spr, NULL);
    }
}