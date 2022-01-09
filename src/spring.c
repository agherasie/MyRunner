/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** spring.c
*/

#include "my_runner.h"

void which_spring(player *p, char *spring, game *g)
{
    switch (*spring) {
        case 100:
            p->speed.y = -15;
            p->is_jumping = sfTrue;
            break;
        case 102:
            p->speed.y = -27;
            p->is_jumping = sfTrue;
            break;
        case 104:
            p->speed.x = 0;
            directional_key(p, 1, sfFalse, g);
            p->speed.x = 10;
            directional_key(p, 1, sfTrue, g);
            break;
    }
}

void spring_collision(player *p, char *spring, game *g)
{
    sfVector2i m_p = {p->map_pos.x, p->map_pos.y};
    p->is_climbing = sfFalse;
    sfMusic_stop(p->sound[SPRING]);
    sfMusic_play(p->sound[SPRING]);
    which_spring(p, spring, g);
    *spring += 1;
    p->cooldown = 10;
}
