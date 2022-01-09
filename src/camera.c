/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** camera.c
*/

#include "my_runner.h"

void x_movement(player *p, game *g)
{
    if (p->obj->pos.x >= g->camera_pan.x + W_W / 2)
        if (p->is_gliding == sfFalse)
            g->camera_speed.x = TOPSPEED;
        else
            g->camera_speed.x = p->speed.x;
    if (p->obj->pos.x >= g->camera_pan.x + W_W - 100)
        g->camera_speed.x = TOPSPEED * 2;
}

void y_movement(player *p, game *g)
{
    if (p->obj->pos.y <= g->camera_pan.y + W_H / 4)
        if (p->is_climbing == sfTrue)
            g->camera_speed.y = p->speed.y;
        else
            g->camera_speed.y = -10;
    if (p->obj->pos.y >= g->camera_pan.y + W_H / 2)
        if (p->is_gliding == sfTrue || p->is_climbing == sfTrue)
            g->camera_speed.y = p->speed.y;
        else
            g->camera_speed.y = 10;
}

void camera_movement(player *p, game *g)
{
    g->camera_speed = (sfVector2f) {0, 0};
    if (g->act == 3)
        return;
    if (p->is_dying == sfFalse && g->is_runner == sfTrue)
        g->camera_speed.x = 3;
    if (p->is_dying == sfTrue)
        return;
    y_movement(p, g);
    x_movement(p, g);
}
