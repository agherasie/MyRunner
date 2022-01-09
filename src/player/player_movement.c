/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** player_movement.c
*/

#include "my_runner.h"

void acceleration(player *p, game *g)
{
    float accel = 0.15f;
    if (g->level == 2)
        accel *= 1.5f;
    float topspeed = TOPSPEED;
    if (p->character == 's')
        topspeed = TOPSPEED + 0.75f;
    float prev_speed_x = p->speed.x;
    if (p->acceleration == sfTrue)
        p->speed.x += accel;
    if (p->speed.x >= topspeed + accel)
        p->speed.x = prev_speed_x;
}

void deceleration(player *p, game *g)
{
    float decel = 0.15f;
    if (g->level == 2)
        decel /= 5;
    if (p->is_dashing == sfTrue)
        decel /= 2;
    if (p->is_turning == sfTrue)
        decel *= 2;
    if (p->deceleration == sfTrue || p->is_dashing == sfTrue) {
        if (p->speed.x > 0)
            p->speed.x -= decel;
        if (p->speed.x <= decel) {
            p->speed.x = 0;
            p->deceleration = sfFalse;
        }
    }
}

void movement(player *p, game *g)
{
    if (p->can_move == sfTrue)
        p->obj->pos.x += p->speed.x * p->direction;
    p->obj->pos.y += p->speed.y;
    if (p->speed.x == 0)
        p->is_turning = sfFalse;
    wall_collision(p, g);
    acceleration(p, g);
    deceleration(p, g);
}

void aerial_movement(player *p)
{
    p->is_grounded = sfFalse;
    if (p->is_flying == sfTrue)
        p->speed.y += 0.125f;
    else if (p->is_gliding == sfTrue) {
        p->speed.y = 1;
        p->speed.x = 5;
    } else
        p->speed.y += 0.4f;
}

void gravity(player *p, game *g)
{
    if (p->obj->pos.y == p->collision.y)
        on_landing(p, g);
    else
        aerial_movement(p);
    if (p->obj->pos.y > p->collision.y) {
        p->speed.y = 0;
        p->obj->pos.y = p->collision.y;
        p->is_grounded = sfTrue;
        p->is_jumping = sfFalse;
    }
}
