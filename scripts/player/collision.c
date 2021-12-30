/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** collision.c
*/

#include "my_runner.h"

int is_solid(int square)
{
    if (square == 2 || square == 3)
        return 0;
    return 1;
}

void camera_movement(player *p, game *g)
{
    g->camera_speed = (sfVector2f) {0, 0};
    if (p->is_dying == sfFalse && g->is_runner == sfTrue)
        g->camera_speed.x = 3;
    if (p->is_dying == sfTrue)
        return;
    if (p->obj->pos.y <= g->camera_pan.y + W_H / 4)
        g->camera_speed.y = -10;
    if (p->obj->pos.y >= g->camera_pan.y + W_H / 2)
        if (p->is_gliding == sfTrue)
            g->camera_speed.y = p->speed_y;
        else
            g->camera_speed.y = 10;
    if (p->obj->pos.x >= g->camera_pan.x + W_W / 2)
        if (p->is_gliding == sfFalse)
            g->camera_speed.x = 10;
        else
            g->camera_speed.x = p->speed_x;
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

void edging(game *g, player *p)
{
    p->is_edging = 0;
    if (is_solid(g->map[p->map_pos.y + 1][p->map_pos.x + 1]) == 1)
        if (p->obj->pos.x > p->map_pos.x * 100 + 35
        && p->obj->pos.x < p->map_pos.x * 100 + 50)
            p->is_edging = 1;
    if (p->obj->pos.x > p->map_pos.x * 100 + 50)
        p->map_pos.x++;
    if (p->map_pos.x - 1 >= 0)
        if (is_solid(g->map[p->map_pos.y + 1][p->map_pos.x - 1]) == 1)
            if (p->obj->pos.x > p->map_pos.x * 100 - 50
            && p->obj->pos.x < p->map_pos.x * 100 - 35)
                p->is_edging = -1;
}

void raycast(player *p, game *g)
{
    edging(g, p);
    for (int i = 0; g->map[p->map_pos.y + i + 1] != NULL; i++)
        if (is_solid(g->map[p->map_pos.y + i + 1][p->map_pos.x]) == 0) {
            p->collision_y = (p->map_pos.y + i) * 100 + 4;
            break;
        }
    if (is_solid(g->map[p->map_pos.y][p->map_pos.x]) == 0)
        if ((int)(p->obj->pos.y) % 100 < 50)
            p->speed_y = 1;
}

void wall_collision(player *p, game *g)
{
    p->can_move = sfTrue;
    int rnd_pos = p->map_pos.x;
    if (is_solid(g->map[p->map_pos.y][rnd_pos + 1]) == 0
    && p->obj->pos.x >= rnd_pos * 100 + 30) {
        p->obj->pos.x = rnd_pos * 100 + 30;
        if (p->direction == 1) {
            p->can_move = sfFalse;
            p->speed_x = 0;
        }
    }
    if (p->obj->pos.x >= rnd_pos + 50)
        rnd_pos++;
    if (is_solid(g->map[p->map_pos.y][rnd_pos - 1]) == 0
    && p->obj->pos.x <= rnd_pos * 100 - 30) {
        p->obj->pos.x = rnd_pos * 100 - 30;
        if (p->direction == -1) {
            p->can_move = sfFalse;
            p->speed_x = 0;
        }
    }
}
