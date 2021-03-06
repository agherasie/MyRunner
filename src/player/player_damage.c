/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** player_damage.c
*/

#include "my_runner.h"

void do_damage(player *p, game *g)
{
    p->is_hurt = sfTrue;
    p->speed.y = -8;
    p->cooldown = 7 * 8;
    sfMusic_play(p->sound[RING_LOSS]);
    g->rings = 0;
}

void do_death(player *p, game *g)
{
    if (p->is_dying == sfFalse) {
        g->camera_speed.x = 0;
        stop_music(g);
        sfMusic_stop(p->sound[DEATH]);
        sfMusic_play(p->sound[DEATH]);
        p->speed.y = -10;
        p->is_dying = sfTrue;
    }
}

void player_hit(player *p, game *g)
{
    p->is_climbing = sfFalse;
    p->speed.x = 0;
    if (g->rings > 0)
        do_damage(p, g);
    else
        do_death(p, g);
}
