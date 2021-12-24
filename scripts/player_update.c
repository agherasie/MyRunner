/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** player_update.c
*/

#include "my_runner.h"

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
    printf("pos: %f:%f\n", p->obj->pos.x, p->obj->pos.y);
    printf("map_pos: %i:%i\n", p->map_pos.x, p->map_pos.y);
}

void invisible_walls(player *p, game *g)
{
    if (p->obj->pos.x <= 0)
        p->obj->pos.x = 0;
    if (p->obj->pos.y <= 0)
        p->obj->pos.y = 0;
}

void update_player(player *p, game *g)
{
    if (p->obj->scale.x < 0)
        p->obj->pos.x -= 48 * 2;
    p->map_pos.x = (int)(p->obj->pos.x / 100);
    p->map_pos.y = (int)(p->obj->pos.y / 100);
    invisible_walls(p, g);
    movement(p, g);
    raycast(p, g);
    gravity(p);
    animate(p);
    print_status(p);
    sfSprite_setScale(p->obj->spr, p->obj->scale);
    sfSprite_setTextureRect(p->obj->spr, p->obj->rect);
    if (p->obj->scale.x < 0)
        p->obj->pos.x += 48 * 2;
    sfSprite_setPosition(p->obj->spr, p->obj->pos);
    sfRenderWindow_drawSprite(g->window, p->obj->spr, NULL);
}
