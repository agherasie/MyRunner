/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** player_control.c
*/

#include "my_runner.h"

void climbing_controls(game *g, player *p, sfBool release)
{
    if (release == sfFalse) {
        if (g->event.key.code == sfKeyUp)
            p->speed_y = -2;
        if (g->event.key.code == sfKeyDown)
            p->speed_y = 2;
    } else {
        if (g->event.key.code == sfKeyUp && p->speed_y < 0)
            p->speed_y = 0;
        if (g->event.key.code == sfKeyDown && p->speed_y > 0)
            p->speed_y = 0;
    }
}

void flip(player *p, int direction)
{
    if (p->direction != direction) {
        p->speed_x = 0;
        p->direction = direction;
        p->obj->scale.x *= -1;
        p->obj->pos.x += p->obj->rect.width * 2 * (-direction);
    }
}

void turning(player *p, int dir)
{
    if (p->speed_x == 0) {
        p->is_turning = sfFalse;
        p->deceleration = sfFalse;
        p->acceleration = sfTrue;
        flip(p, dir);
    } else if (p->direction != dir)
        p->is_turning = sfTrue;
}

void release_charge(game *g, player *p)
{
    if (g->event.key.code == sfKeyUp)
        if (p->is_charging == sfTrue) {
            p->speed_x = 10;
            p->is_speeding = sfTrue;
        } else
            p->is_looking = sfFalse;
    if (g->event.key.code == sfKeyDown)
        if (p->is_spinning) {
            p->speed_x = 10;
            p->is_dashing = sfTrue;
        } else
            p->is_crouching = sfFalse;
}

void player_keyboard_events(game *g, player *p)
{
    if (g->event.type == sfEvtKeyPressed && p->goal_reached == sfFalse)
        player_press_key(g, p);
    if (g->event.type == sfEvtKeyReleased)
        player_release_key(g, p);
}
