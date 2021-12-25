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
        g->e[i].obj->pos.x += g->camera_pan_x;
        animate_object(g, g->e[i].obj, g->e[i].anim, &g->e[i].frame);
        sfSprite_setTextureRect(g->e[i].obj->spr, g->e[i].obj->rect);
        g->e[i].obj->pos.x -= g->camera_pan_x + g->camera_pan_speed;
        sfSprite_setPosition(g->e[i].obj->spr, g->e[i].obj->pos);
        sfRenderWindow_drawSprite(g->window, g->e[i].obj->spr, NULL);
        //printf("enemypos = %.2f:%.2f\n", g->e[i].obj->pos.x, g->e[i].obj->pos.y);
    }
}