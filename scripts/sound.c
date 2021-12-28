/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** sound.c
*/

#include "my_runner.h"

void sound_update(player *p)
{
    if (p->is_turning == sfTrue)
        sfMusic_play(p->sound[BRAKE]);
    else
        sfMusic_stop(p->sound[BRAKE]);
    if (p->is_hurt == sfFalse)
        sfMusic_stop(p->sound[RING_LOSS]);
    if (p->goal_reached == sfTrue
    && sfMusic_getStatus(p->sound[GOALSIGN]) != sfPlaying)
        sfMusic_play(p->sound[GOALSIGN]);
    if (p->goal_reached == sfFalse)
        sfMusic_stop(p->sound[GOALSIGN]);
}
