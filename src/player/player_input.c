/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** player_input.c
*/

#include "my_runner.h"

void player_release_key(game *g, player *p)
{
    if (g->event.key.code == sfKeyRight && p->direction == 1)
        directional_key(p, 1, sfTrue, g);
    if (g->event.key.code == sfKeyLeft && p->direction == -1)
        directional_key(p, -1, sfTrue, g);
    if (p->is_climbing == sfTrue)
        climbing_controls(g, p, sfTrue);
    release_charge(g, p);
    if (g->event.key.code == sfKeyS) {
        if (p->is_gliding == sfTrue)
            p->speed.x = 0;
        p->is_gliding = sfFalse;
    }
}

void directional_key(player *p, int dir, sfBool released, game *g)
{
    if (g->is_runner == sfFalse && p->is_climbing == sfFalse) {
        if (released == sfFalse)
            turning(p, dir);
        else {
            p->deceleration = sfTrue;
            p->acceleration = sfFalse;
        }
    }
}

void s_key(game *g, player *p)
{
    if (p->anim_state != CROUCHING && p->anim_state != LOOKING
    && p->anim_state != SPINNING && p->is_charging == sfFalse)
        do_jump(p, g);
    else {
        if (p->anim_state == CROUCHING) {
            sfMusic_stop(p->sound[SPIN]);
            sfMusic_play(p->sound[SPIN]);
            p->is_spinning = sfTrue;
        }
        if (p->anim_state == LOOKING && p->character == 's') {
            sfMusic_stop(p->sound[SPIN]);
            sfMusic_play(p->sound[SPIN]);
            p->is_charging = sfTrue;
        }
        p->is_crouching = sfFalse;
        p->is_looking = sfFalse;
    }
}

void player_press_key(game *g, player *p)
{
    if (g->event.key.code == sfKeyRight)
        directional_key(p, 1, sfFalse, g);
    if (g->event.key.code == sfKeyLeft)
        directional_key(p, -1, sfFalse, g);
    if (p->is_climbing == sfTrue)
        climbing_controls(g, p, sfFalse);
    if (g->event.key.code == sfKeyS)
        s_key(g, p);
    if (g->event.key.code == sfKeyUp && p->is_grounded && p->speed.x == 0)
        p->is_looking = sfTrue;
    if (g->event.key.code == sfKeyDown && p->is_grounded)
        if (p->speed.x == 0)
            p->is_crouching = sfTrue;
        else {
            sfMusic_stop(p->sound[SPIN]);
            sfMusic_play(p->sound[SPIN]);
            p->is_dashing = sfTrue;
        }
}
