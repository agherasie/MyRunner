/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** player_movement.c
*/

#include "my_runner.h"

void animate(player *p)
{
    if (p->speed_x == 0)
        p->anim_state = IDLE;
    if (p->speed_x > 0 && p->speed_x < 8)
        p->anim_state = WALKING;
    if (p->speed_x >= 8)
        p->anim_state = RUNNING;
    if (p->is_turning == sfTrue)
        p->anim_state = TURNING;
    if (p->is_jumping == sfTrue)
        p->anim_state = JUMPING;
    p->anim_frame++;
    p->obj->rect.height = 48;
    p->obj->rect.width = 48;
    if (p->anim_frame % 10 == 0 && p->anim[p->anim_state].length != 1)
        p->running_anim++;
    if (p->running_anim > p->anim[p->anim_state].length - 1)
        p->running_anim = 0;
    p->obj->rect.top = 48 * p->anim_state;
    p->obj->rect.left = 48 * p->running_anim;
}

void update_player(player *p, game *g)
{
    sfSprite_setScale(p->obj->spr, p->obj->scale);
    if (p->is_grounded == sfFalse) {
        p->speed_y += 0.4f;
    }
    if (p->obj->pos.y > 500) {
        p->speed_y = 0;
        p->obj->pos.y = 500;
        p->is_grounded = sfTrue;
        p->is_jumping = sfFalse;
    }
    if (p->acceleration == sfTrue)
        p->speed_x += 0.15f;
    if (p->speed_x >= TOPSPEED)
        p->speed_x = TOPSPEED;
    p->obj->pos.x += p->speed_x * p->direction;
    p->obj->pos.y += p->speed_y;
    if (p->speed_x > 0)
        p->meters_run += p->speed_x / 40;
    if (p->speed_x == 0) {
        p->is_turning = sfFalse;
        p->meters_run = 0;
    }
    if (p->deceleration == sfTrue) {
        if (p->speed_x > 0)
            p->speed_x -= 0.15f;
        if (p->speed_x <= 0.15f) {
            p->speed_x = 0;
            p->deceleration = sfFalse;
        }
    }
    animate(p);
    printf("running_anim = %i\n", p->running_anim);
    sfSprite_setTextureRect(p->obj->spr, p->obj->rect);
    printf("speed_x = %f\nspeed_y = %f\n", p->speed_x, p->speed_y);
    printf("meters_run = %f\n\n", p->meters_run);
    if (p->is_jumping == sfTrue)
        printf("is_jumping\n");
    if (p->is_grounded == sfTrue)
        printf("is_grounded\n");
    if (p->is_turning == sfTrue)
        printf("is_turning\n");
    sfSprite_setPosition(p->obj->spr, p->obj->pos);
    sfRenderWindow_drawSprite(g->window, p->obj->spr, NULL);
}
