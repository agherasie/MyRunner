/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** animation.c
*/

#include "my_runner.h"

void basic_anims(player *p)
{
    if (p->speed.x == 0)
        p->anim_state = IDLE;
    if (p->direction * p->is_edging == 1)
        p->anim_state = FEDGING;
    if (p->direction * p->is_edging == -1)
        p->anim_state = BEDGING;
    if (p->is_looking == sfTrue)
        p->anim_state = LOOKING;
    if (p->is_crouching == sfTrue)
        p->anim_state = CROUCHING;
    if (p->speed.x > 0 && p->speed.x < 8)
        p->anim_state = WALKING;
    if (p->speed.x >= 8)
        p->anim_state = RUNNING;
    if (p->speed.x >= 9)
        p->anim_state = SPEEDING;
    if (p->is_turning == sfTrue && p->speed.x > 6)
        p->anim_state = TURNING;
    if (p->is_jumping == sfTrue)
        p->anim_state = JUMPING;
}

void special_anims(player *p)
{
    if (p->can_move == sfFalse && p->anim_state == WALKING)
        p->anim_state = PUSHING;
    if (p->is_spinning == sfTrue)
        p->anim_state = SPINNING;
    if (p->is_charging == sfTrue
    || p->is_flying == sfTrue || p->is_gliding == sfTrue)
        p->anim_state = SPEEDING;
    if (p->is_climbing == sfTrue)
        p->anim_state = SPECIAL;
    if (p->is_flying == sfTrue && p->cooldown < 10)
        p->anim_state = SPECIAL;
    if (p->is_dashing == sfTrue)
        p->anim_state = DASHING;
    if (p->is_hurt == sfTrue)
        p->anim_state = HURTING;
    if (p->goal_reached == sfTrue)
        p->anim_state = THUMBSUP;
    if (p->is_dying == sfTrue)
        p->anim_state = DYING;
}

void choose_anim_state(player *p)
{
    basic_anims(p);
    special_anims(p);
}

void animate(player *p)
{
    int prev_state = p->anim_state;
    choose_anim_state(p);
    if (prev_state != p->anim_state)
        p->running_anim = 0;
    p->anim_frame++;
    p->obj->rect.height = 48;
    p->obj->rect.width = 48;
    if (p->anim_frame % p->anim[p->anim_state].speed == 0
    && p->anim[p->anim_state].length != 1)
        p->running_anim++;
    if (p->anim[p->anim_state].loop == sfFalse
    && p->running_anim == p->anim[p->anim_state].length)
        p->running_anim = p->anim[p->anim_state].length - 1;
    if (p->running_anim > p->anim[p->anim_state].length - 1)
        p->running_anim = 0;
    p->obj->rect.top = 48 * p->anim_state;
    p->obj->rect.left = 48 * p->running_anim;
}

void animate_object(game *g, object *obj, animation anim, int *frame)
{
    obj->rect.height = 50;
    obj->rect.width = 50;
    if (g->frame % anim.speed == 0 && anim.length != 1)
        *frame += 1;
    if (anim.loop == sfFalse && *frame == anim.length)
        *frame = anim.length - 1;
    if (*frame > anim.length - 1)
        *frame = 0;
    obj->rect.left = 50 * *frame;
}
