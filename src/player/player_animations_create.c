/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** player_animations_create.c
*/

#include "my_runner.h"

player create_knux_animations(player p)
{
    create_animation(&p.anim[IDLE], 1, 1, sfFalse);
    create_animation(&p.anim[WALKING], 8, 8, sfTrue);
    create_animation(&p.anim[RUNNING], 4, 5, sfTrue);
    create_animation(&p.anim[JUMPING], 4, 3, sfTrue);
    create_animation(&p.anim[TURNING], 2, 10, sfTrue);
    create_animation(&p.anim[PUSHING], 4, 20, sfTrue);
    create_animation(&p.anim[FEDGING], 2, 12, sfTrue);
    create_animation(&p.anim[BEDGING], 3, 8, sfTrue);
    create_animation(&p.anim[LOOKING], 2, 10, sfFalse);
    create_animation(&p.anim[CROUCHING], 2, 10, sfFalse);
    create_animation(&p.anim[THUMBSUP], 4, 12, sfTrue);
    create_animation(&p.anim[HURTING], 6, 7, sfFalse);
    create_animation(&p.anim[SPINNING], 6, 5, sfTrue);
    create_animation(&p.anim[DASHING], 4, 3, sfTrue);
    create_animation(&p.anim[SPEEDING], 1, 1, sfFalse);
    create_animation(&p.anim[DYING], 2, 10, sfFalse);
    create_animation(&p.anim[SPECIAL], 7, 15, sfTrue);
    return p;
}

player create_tails_animations(player p)
{
    create_animation(&p.anim[IDLE], 4, 15, sfTrue);
    create_animation(&p.anim[WALKING], 8, 8, sfTrue);
    create_animation(&p.anim[RUNNING], 6, 5, sfTrue);
    create_animation(&p.anim[JUMPING], 4, 3, sfTrue);
    create_animation(&p.anim[TURNING], 2, 10, sfTrue);
    create_animation(&p.anim[PUSHING], 4, 20, sfTrue);
    create_animation(&p.anim[FEDGING], 4, 5, sfTrue);
    create_animation(&p.anim[BEDGING], 4, 5, sfTrue);
    create_animation(&p.anim[LOOKING], 2, 10, sfFalse);
    create_animation(&p.anim[CROUCHING], 1, 1, sfFalse);
    create_animation(&p.anim[THUMBSUP], 8, 8, sfFalse);
    create_animation(&p.anim[HURTING], 4, 7, sfFalse);
    create_animation(&p.anim[SPINNING], 3, 5, sfTrue);
    create_animation(&p.anim[DASHING], 3, 3, sfTrue);
    create_animation(&p.anim[SPEEDING], 2, 3, sfTrue);
    create_animation(&p.anim[DYING], 3, 10, sfFalse);
    create_animation(&p.anim[SPECIAL], 2, 6, sfTrue);
    return p;
}

player create_sonic_animations(player p)
{
    create_animation(&p.anim[IDLE], 1, 1, sfTrue);
    create_animation(&p.anim[WALKING], 8, 8, sfTrue);
    create_animation(&p.anim[RUNNING], 4, 5, sfTrue);
    create_animation(&p.anim[JUMPING], 8, 3, sfTrue);
    create_animation(&p.anim[TURNING], 3, 10, sfTrue);
    create_animation(&p.anim[PUSHING], 4, 20, sfTrue);
    create_animation(&p.anim[FEDGING], 8, 5, sfTrue);
    create_animation(&p.anim[BEDGING], 8, 5, sfTrue);
    create_animation(&p.anim[LOOKING], 2, 10, sfFalse);
    create_animation(&p.anim[CROUCHING], 2, 10, sfFalse);
    create_animation(&p.anim[THUMBSUP], 13, 8, sfFalse);
    create_animation(&p.anim[HURTING], 8, 7, sfFalse);
    create_animation(&p.anim[SPINNING], 6, 5, sfTrue);
    create_animation(&p.anim[DASHING], 8, 3, sfTrue);
    create_animation(&p.anim[SPEEDING], 4, 3, sfTrue);
    create_animation(&p.anim[DYING], 4, 10, sfFalse);
    return p;
}
