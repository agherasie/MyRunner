/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** collision.c
*/

#include "my_runner.h"

void edging(game *g, player *p)
{
    p->is_edging = sfFalse;
    if (g->map[p->map_pos.y + 1][p->map_pos.x + 1] == 0)
        if (p->obj->pos.x > p->map_pos.x * 100 + 35 && p->obj->pos.x < p->map_pos.x * 100 + 50)
            p->is_edging = sfTrue;
    if (p->obj->pos.x > p->map_pos.x * 100 + 50)
        p->map_pos.x++;
    if (p->map_pos.x - 1 >= 0)
        if (g->map[p->map_pos.y + 1][p->map_pos.x - 1] == 0)
            if (p->obj->pos.x > p->map_pos.x * 100 - 50 && p->obj->pos.x < p->map_pos.x * 100 - 35)
                p->is_edging = sfTrue;
}

void raycast(player *p, game *g)
{
    edging(g, p);
    for (int i = 0; g->map[p->map_pos.y + i + 1] != NULL; i++)
        if (g->map[p->map_pos.y + i + 1][p->map_pos.x] != 0) {
            p->collision_y = (p->map_pos.y + i) * 100 + 4;
            break;
        }
}

void wall_collision(player *p, game *g)
{
    p->can_move = sfTrue;
    int rnd_pos = p->map_pos.x;
    if (g->map[p->map_pos.y][rnd_pos + 1] != 0 && (int)(p->obj->pos.x) % 100 >= 30 && p->direction == 1) {
        p->speed_x = 0;
        p->obj->pos.x = (rnd_pos * 100) + 30;
        p->can_move = sfFalse;
    }
    if (p->obj->pos.x >= rnd_pos + 50)
        rnd_pos++;
    if (rnd_pos - 1 >= 0)
        if (g->map[p->map_pos.y][rnd_pos - 1] != 0 && p->obj->pos.x <= rnd_pos * 100 - 26 && p->direction == -1) {
            p->speed_x = 0;
            p->obj->pos.x = rnd_pos * 100 - 26;
            p->can_move = sfFalse;
        }
}