/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** horizontal_collision.c
*/

#include "my_runner.h"

void do_wall_collision(player *p, int dir, int rnd_pos)
{
    p->obj->pos.x = rnd_pos * 100 + 30 * dir;
    if (p->direction == dir && p->is_gliding == sfTrue) {
        if (p->is_climbing == sfFalse)
            p->speed_y = 0;
        p->is_climbing = sfTrue;
    }
    if (p->direction == dir) {
        p->can_move = sfFalse;
        p->speed_x = 0;
    }
}

void wall_collision(player *p, game *g)
{
    p->can_move = sfTrue;
    int rnd_pos = p->map_pos.x;
    if (is_solid(g->map[p->map_pos.y][rnd_pos + 1]) == 0) {
        if (p->obj->pos.x >= rnd_pos * 100 + 30)
            do_wall_collision(p, 1, rnd_pos);
    } else if (p->direction == 1 && p->is_climbing == sfTrue)
        end_climbing(p, g, sfFalse);
    if (p->obj->pos.x >= rnd_pos + 50)
        rnd_pos++;
    if (is_solid(g->map[p->map_pos.y][rnd_pos - 1]) == 0) {
        if (p->obj->pos.x <= rnd_pos * 100 - 30)
            do_wall_collision(p, -1, rnd_pos);
    } else if (p->direction == -1 && p->is_climbing == sfTrue)
        end_climbing(p, g, sfFalse);
}
