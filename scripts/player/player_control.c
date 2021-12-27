/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** player_control.c
*/

#include "my_runner.h"

void flip(player *p, int direction)
{
    if (p->direction != direction) {
        p->speed_x = 0;
        p->direction = direction;
        p->obj->scale.x *= -1;
        p->obj->pos.x += p->obj->rect.width * 2 * (-direction);
    }
}

void directional_key(player *p, int direction, sfBool released, game *g)
{
    if (g->is_runner == sfFalse) {
        if (released == sfFalse) {
            if (p->speed_x == 0) {
                p->is_turning = sfFalse;
                p->deceleration = sfFalse;
                p->acceleration = sfTrue;
                flip(p, direction);
            } else if (p->direction != direction && p->speed_x > TOPSPEED - 0.5f) {
                p->is_turning = sfTrue;
            }
        } else {
            p->deceleration = sfTrue;
            p->acceleration = sfFalse;
        }
    }
}

void do_jump(player *p)
{
    if (p->is_grounded == sfTrue) {
        p->is_grounded = sfFalse;
        p->is_jumping = sfTrue;
        p->speed_y = -10;
        sfMusic_play(p->sound[JUMP]);
    } else if (p->is_jumping == sfTrue) {
        p->is_dropping = sfTrue;
    }
}

void player_keyboard_events(game *g, player *p)
{
    if (g->event.type == sfEvtKeyPressed && p->goal_reached == sfFalse) {
        if (g->event.key.code == sfKeyRight)
            directional_key(p, 1, sfFalse, g);
        if (g->event.key.code == sfKeyLeft)
            directional_key(p, -1, sfFalse, g);
        if (g->event.key.code == sfKeyS)
            if (p->anim_state != CROUCHING && p->anim_state != LOOKING
            && p->anim_state != SPINNING && p->is_charging == sfFalse)
                do_jump(p);
            else {
                sfMusic_stop(p->sound[SPIN]);
                sfMusic_play(p->sound[SPIN]);
                if (p->anim_state == CROUCHING)
                    p->is_spinning = sfTrue;
                if (p->anim_state == LOOKING)
                    p->is_charging = sfTrue;
                p->is_crouching = sfFalse;
                p->is_looking = sfFalse;
            }
        if (g->event.key.code == sfKeyUp && p->is_grounded && p->speed_x == 0)
            p->is_looking = sfTrue;
        if (g->event.key.code == sfKeyDown && p->is_grounded)
            if (p->speed_x == 0)
                p->is_crouching = sfTrue;
            else {
                sfMusic_stop(p->sound[SPIN]);
                sfMusic_play(p->sound[SPIN]);
                p->is_dashing = sfTrue;
            }
    }
    if (g->event.type == sfEvtKeyReleased) {
        if (g->event.key.code == sfKeyRight && p->direction == 1)
            directional_key(p, 1, sfTrue, g);
        if (g->event.key.code == sfKeyLeft && p->direction == -1)
            directional_key(p, -1, sfTrue, g);
        if (g->event.key.code == sfKeyUp)
            if (p->is_charging) {
                p->speed_x = 10;
                p->is_speeding = sfTrue;
            } else
                p->is_looking = sfFalse;
        if (g->event.key.code == sfKeyDown)
            if (p->is_spinning) {
                p->speed_x = 8;
                p->is_dashing = sfTrue;
            } else
                p->is_crouching = sfFalse;
    }
}
