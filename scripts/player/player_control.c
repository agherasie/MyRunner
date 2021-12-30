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

void directional_key(player *p, int dir, sfBool released, game *g)
{
    if (g->is_runner == sfFalse && p->is_climbing == sfFalse) {
        if (released == sfFalse) {
            if (p->speed_x == 0) {
                p->is_turning = sfFalse;
                p->deceleration = sfFalse;
                p->acceleration = sfTrue;
                flip(p, dir);
            } else if (p->direction != dir) {
                p->is_turning = sfTrue;
            }
        } else {
            p->deceleration = sfTrue;
            p->acceleration = sfFalse;
        }
    }
}

void do_special(player *p)
{
    if (p->character == 's')
        p->is_dropping = sfTrue;
    if (p->character == 't') {
        if (p->is_flying == sfFalse)
            p->cooldown = 150;
        if (p->cooldown > 0)
            p->speed_y = -5;
        p->is_flying = sfTrue;
    }
    if (p->character == 'k'
    && p->is_gliding == sfFalse && p->is_jumping == sfTrue)
        p->is_gliding = sfTrue;
}

void end_climbing(player *p, game *g, sfBool jump)
{
    if (jump == sfFalse) {
        p->obj->pos.x += 40 * p->direction;
        p->obj->pos.y += 40 * p->direction;
        p->speed_x = 0;
    }
    p->is_climbing = sfFalse;
    directional_key(p, p->direction, sfTrue, g);
}

void do_jump(player *p, game *g)
{
    float jump_speed = 10;
    if (p->character == 'k')
        jump_speed = 8;
    if (p->is_grounded == sfTrue || p->is_climbing == sfTrue) {
        if (p->is_climbing == sfTrue)
            end_climbing(p, g, sfTrue);
        p->is_grounded = sfFalse;
        p->is_dashing = sfFalse;
        p->is_jumping = sfTrue;
        p->speed_y -= jump_speed;
        sfMusic_stop(p->sound[JUMP]);
        sfMusic_play(p->sound[JUMP]);
    } else if (p->is_jumping == sfTrue)
        do_special(p);
}

void player_release_key(game *g, player *p)
{
    if (g->event.key.code == sfKeyRight && p->direction == 1)
        directional_key(p, 1, sfTrue, g);
    if (g->event.key.code == sfKeyLeft && p->direction == -1)
        directional_key(p, -1, sfTrue, g);
    if (g->event.key.code == sfKeyUp && p->is_climbing == sfTrue) {
        if (p->speed_y < 0)
            p->speed_y = 0;
    }
    if (g->event.key.code == sfKeyDown && p->is_climbing == sfTrue) {
        if (p->speed_y > 0)
            p->speed_y = 0;
    }
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
    if (g->event.key.code == sfKeyS) {
        if (p->is_gliding == sfTrue)
            p->speed_x = 0;
        p->is_gliding = sfFalse;
    }
}

void player_keyboard_events(game *g, player *p)
{
    if (g->event.type == sfEvtKeyPressed && p->goal_reached == sfFalse) {
        if (g->event.key.code == sfKeyRight)
            directional_key(p, 1, sfFalse, g);
        if (g->event.key.code == sfKeyLeft)
            directional_key(p, -1, sfFalse, g);
        if (p->is_climbing == sfTrue) {
            if (g->event.key.code == sfKeyUp)
                p->speed_y = -2;
            if (g->event.key.code == sfKeyDown)
                p->speed_y = 2;
        }
        if (g->event.key.code == sfKeyS) {
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
    if (g->event.type == sfEvtKeyReleased)
        player_release_key(g, p);
}
