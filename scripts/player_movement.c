/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** player_movement.c
*/

#include "my_runner.h"

void anim_player(player *p)
{
    p->anim_frame++;
    p->obj->rect.height = 48;
    p->obj->rect.width = 48;
    if (p->is_jumping == sfTrue) {
        if (p->anim_frame % 4 == 0)
            p->running_anim++;
        if (p->running_anim > 3) {
            p->running_anim = 0;
        }
    }
    if (p->speed_x != 0) {
        if (p->anim_frame % (FPS / ((int)(p->speed_x) + 1)) == 0)
            p->running_anim++;
        if ((p->running_anim > 5 && p->speed_x < TOPSPEED) || (p->running_anim > 3 && p->speed_x >= TOPSPEED))
            p->running_anim = 0;
    }
    if (p->is_turning == sfTrue) {
        if (p->anim_frame % (FPS / ((int)(p->speed_x) + 1)) == 0)
            p->running_anim++;
        if (p->running_anim > 2) {
            p->running_anim = 0;
        }
    }
    if (p->is_grounded) {
        if (p->speed_x == 0) {
            p->running_anim = 0;
            p->obj->rect.left = 0;
            p->obj->rect.top = 0;
        }
        if ((p->speed_x < TOPSPEED || p->speed_x > -TOPSPEED) && p->speed_x != 0) {
            p->obj->rect.top = 48;
            p->obj->rect.left = 48 * p->running_anim;
        }
        if (p->speed_x >= TOPSPEED || p->speed_x <= -TOPSPEED) {
            p->obj->rect.top = 48 * 2;
            p->obj->rect.left = 48 * p->running_anim;
        }
        if (p->speed_x > 0 && p->is_turning == sfTrue) {
            p->obj->rect.top = 48 * 4;
            p->obj->rect.left = 48 * p->running_anim;
        }
    } else if (p->is_jumping == sfTrue) {
        p->obj->rect.top = 48 * 3;
        p->obj->rect.left = 48 * p->running_anim;
    }
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
    if (p->speed_x == 0)
        p->meters_run = 0;
    if (p->deceleration == sfTrue) {
        if (p->speed_x > 0)
            p->speed_x -= 0.15f;
        if (p->speed_x <= 0.15f) {
            p->speed_x = 0;
            p->deceleration = sfFalse;
        }
    }
    anim_player(p);
    printf("running_anim = %i\n", p->running_anim);
    sfSprite_setTextureRect(p->obj->spr, p->obj->rect);
    printf("speed_x = %f\nspeed_y = %f\n", p->speed_x, p->speed_y);
    printf("meters_run = %f\n\n", p->meters_run);
    if (p->is_jumping == sfTrue)
        printf("is_jumping\n");
    if (p->is_grounded == sfTrue)
        printf("is_grounded\n");
    sfSprite_setPosition(p->obj->spr, p->obj->pos);
    sfRenderWindow_drawSprite(g->window, p->obj->spr, NULL);
}
