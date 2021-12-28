/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** player_movement.c
*/

#include "my_runner.h"

void acceleration(player *p)
{
    float topspeed = TOPSPEED;
    if (p->character == 's')
        topspeed = TOPSPEED + 0.75f;
    float prev_speed_x = p->speed_x;
    if (p->acceleration == sfTrue)
        p->speed_x += 0.15f;
    if (p->speed_x >= topspeed + 0.15f)
        p->speed_x = prev_speed_x;
    if (p->speed_x > 0)
        p->meters_run += p->speed_x / 40;
}

void deceleration(player *p)
{
    float decel = 0.15f;
    if (p->is_dashing == sfTrue)
        decel = 0.05f;
    if (p->deceleration == sfTrue || p->is_dashing == sfTrue) {
        if (p->speed_x > 0)
            p->speed_x -= decel;
        if (p->speed_x <= decel) {
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
    if (p->obj->pos.y == p->collision_y) {
        p->is_grounded = sfTrue;
        if (p->is_gliding == sfTrue)
            p->speed_x = 0;
        p->is_flying = sfFalse;
        p->is_gliding = sfFalse;
        if (p->is_dropping == sfTrue) {
            p->speed_x = TOPSPEED;
            p->is_dashing = sfTrue;
            p->is_dropping = sfFalse;
            sfMusic_stop(p->sound[SPIN]);
            sfMusic_play(p->sound[SPIN]);
        }
    } else
        p->is_grounded = sfFalse;
    if (p->is_grounded == sfFalse)
        if (p->is_flying == sfTrue)
            p->speed_y += 0.125f;
        else if (p->is_gliding == sfTrue) {
            p->speed_y = 1;
            p->speed_x = 5.5f;
        } else
            p->speed_y += 0.4f;
    if (p->obj->pos.y > p->collision_y) {
        p->speed_y = 0;
        p->obj->pos.y = p->collision_y;
        p->is_grounded = sfTrue;
        p->is_jumping = sfFalse;
    }
}
