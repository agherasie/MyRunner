/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** tally.c
*/

#include "my_runner.h"

void update_lives(player *p, game *g)
{
    g->score += g->lives * 100;
    sfMusic_stop(p->sound[ONEUP]);
    sfMusic_play(p->sound[ONEUP]);
    g->lives++;
}

void counting(player *p, game *g)
{
    if (g->rings > 0 && p->cooldown % g->tally_speed == 0) {
        if (p->cooldown % 15 == 0) {
            sfMusic_stop(p->sound[TALLY]);
            sfMusic_play(p->sound[TALLY]);
        }
        g->score += 100;
        g->rings--;
    }
    if (g->seconds != 0) {
        if (g->seconds < 60)
            g->score += 1000;
        else if (g->seconds < 120)
            g->score += 500;
        else if (g->seconds < 180)
            g->score += 500;
    }
    g->seconds = 0;
    if (g->rings == 0 && p->cooldown > 50)
        p->cooldown = 50;
}

void tally(player *p, game *g)
{
    if (g->rings > 50 && g->tally_speed == 5)
        g->tally_speed = 2;
    if (p->cooldown < 0)
        p->cooldown = 10000;
    if (p->cooldown > 0 && p->cooldown <= 9700)
        counting(p, g);
    if (p->cooldown == 0) {
        if (g->level != 3) {
            g->level++;
            restart(g, p);
        } else {
            g->relaunch = sfTrue;
            sfRenderWindow_close(g->window);
        }
    }
}
