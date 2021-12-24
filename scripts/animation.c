/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** animation.c
*/

#include "my_runner.h"

void choose_anim_state(player *p)
{
    if (p->speed_x == 0)
        p->anim_state = IDLE;
    if (p->is_edging == sfTrue && p->direction == 1)
        p->anim_state = FEDGING;
    if (p->is_edging == sfTrue && p->direction == -1)
        p->anim_state = BEDGING;
    if (p->speed_x > 0 && p->speed_x < 8)
        p->anim_state = WALKING;
    if (p->speed_x >= 8)
        p->anim_state = RUNNING;
    if (p->is_turning == sfTrue)
        p->anim_state = TURNING;
    if (p->is_jumping == sfTrue)
        p->anim_state = JUMPING;
    if (p->can_move == sfFalse && p->anim_state == WALKING)
        p->anim_state = PUSHING;
}

void animate(player *p)
{
    choose_anim_state(p);
    p->anim_frame++;
    p->obj->rect.height = 48;
    p->obj->rect.width = 48;
    if (p->anim_frame % p->anim[p->anim_state].speed == 0 && p->anim[p->anim_state].length != 1)
        p->running_anim++;
    if (p->running_anim > p->anim[p->anim_state].length - 1)
        p->running_anim = 0;
    p->obj->rect.top = 48 * p->anim_state;
    p->obj->rect.left = 48 * p->running_anim;
}