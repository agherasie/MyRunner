/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** collision.c
*/

#include "my_runner.h"

int is_solid(int square)
{
    if (square == 2 || square == 3 || square == 6)
        return 0;
    return 1;
}

void invisible_walls(player *p, game *g)
{
    if (p->obj->pos.x <= g->camera_pan.x - 24) {
        p->obj->pos.x = g->camera_pan.x - 24;
        if (p->direction == -1)
            p->speed_x = 0;
        if (g->is_runner == sfTrue)
            do_death(p, g);
    }
    if (p->obj->pos.y <= 0)
        p->obj->pos.y = 0;
}
