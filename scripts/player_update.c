/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** player_update.c
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

void print_status(player *p)
{
    printf("running_anim = %i\n", p->running_anim);
    printf("speed_x = %f\nspeed_y = %f\n", p->speed_x, p->speed_y);
    printf("meters_run = %f\n\n", p->meters_run);
    if (p->is_jumping == sfTrue)
        printf("is_jumping\n");
    if (p->is_grounded == sfTrue)
        printf("is_grounded\n");
    if (p->is_turning == sfTrue)
        printf("is_turning\n");
    printf("map_pos: %i:%i\n", p->map_pos.x, p->map_pos.y);
}

void raycast(player *p, game *g)
{
    p->map_pos.x = p->obj->pos.x / 100;
    p->map_pos.y = p->obj->pos.y / 100;
    for (int i = 0; g->map[p->map_pos.y + i + 1] != NULL; i++) {
        if (g->map[p->map_pos.y + i + 1][p->map_pos.x] != 0) {
            p->collision_y = (p->map_pos.y + i) * 100 + 4;
            break;
        }
    }
}

void update_player(player *p, game *g)
{
    raycast(p, g);
    gravity(p);
    movement(p);
    animate(p);
    print_status(p);
    sfSprite_setScale(p->obj->spr, p->obj->scale);
    sfSprite_setTextureRect(p->obj->spr, p->obj->rect);
    sfSprite_setPosition(p->obj->spr, p->obj->pos);
    sfRenderWindow_drawSprite(g->window, p->obj->spr, NULL);
}
