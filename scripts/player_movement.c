/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** player_movement.c
*/

#include "my_runner.h"

void acceleration(player *p)
{
    if (p->acceleration == sfTrue)
        p->speed_x += 0.15f;
    if (p->speed_x >= TOPSPEED)
        p->speed_x = TOPSPEED;
    if (p->speed_x > 0)
        p->meters_run += p->speed_x / 40;
}

void deceleration(player *p)
{
    if (p->deceleration == sfTrue) {
        if (p->speed_x > 0)
            p->speed_x -= 0.15f;
        if (p->speed_x <= 0.15f) {
            p->speed_x = 0;
            p->deceleration = sfFalse;
        }
    }
}

void movement(player *p, game *g)
{
    if (p->can_move == sfTrue)
        p->obj->pos.x += p->speed_x * p->direction;
    p->obj->pos.y += p->speed_y;
    if (p->speed_x == 0) {
        p->is_turning = sfFalse;
        p->meters_run = 0;
    }
    wall_collision(p, g);
    acceleration(p);
    deceleration(p);
}

void gravity(player *p)
{
    if (p->obj->pos.y == p->collision_y)
        p->is_grounded = sfTrue;
    else
        p->is_grounded = sfFalse;
    if (p->is_grounded == sfFalse) {
        p->speed_y += 0.4f;
    }
    if (p->obj->pos.y > p->collision_y) {
        p->speed_y = 0;
        p->obj->pos.y = p->collision_y;
        p->is_grounded = sfTrue;
        p->is_jumping = sfFalse;
    }
}

