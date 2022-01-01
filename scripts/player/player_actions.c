/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** player_actions.c
*/

#include "my_runner.h"

void on_landing(player *p, game *g)
{
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
}

void do_special(player *p)
{
    if (p->character == 's')
        p->is_dropping = sfTrue;
    if (p->character == 't') {
        if (p->is_flying == sfFalse)
            p->cooldown = 150;
        if (p->cooldown > 0)
            p->speed_y = -5;
        p->is_flying = sfTrue;
    }
    if (p->character == 'k'
    && p->is_gliding == sfFalse && p->is_jumping == sfTrue)
        p->is_gliding = sfTrue;
}

void end_climbing(player *p, game *g, sfBool jump)
{
    if (jump == sfFalse) {
        p->obj->pos.x += 40 * p->direction;
        p->obj->pos.y += 40 * p->direction;
        p->speed_x = 0;
    }
    p->is_climbing = sfFalse;
    directional_key(p, p->direction, sfTrue, g);
}

void do_jump(player *p, game *g)
{
    float jump_speed = 10;
    if (p->character == 'k')
        jump_speed = 8;
    if (p->is_grounded == sfTrue || p->is_climbing == sfTrue) {
        if (p->is_climbing == sfTrue)
            end_climbing(p, g, sfTrue);
        p->is_grounded = sfFalse;
        p->is_dashing = sfFalse;
        p->is_jumping = sfTrue;
        p->speed_y -= jump_speed;
        sfMusic_stop(p->sound[JUMP]);
        sfMusic_play(p->sound[JUMP]);
    } else if (p->is_jumping == sfTrue)
        do_special(p);
}
