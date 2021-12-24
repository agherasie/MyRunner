/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** player_update.c
*/

#include "my_runner.h"

void animate(player *p)
{
    p->obj->text = sfTexture_createFromFile("art/sonic_sheet.png", NULL);
    if (p->speed_x == 0)
        p->anim_state = IDLE;
    if (p->is_edging == sfTrue && p->direction == 1)
        p->anim_state = FEDGING;
    if (p->is_edging == sfTrue && p->direction == -1)
        p->anim_state = BEDGING;
    if (p->speed_x > 0 && p->speed_x < 8)
        p->anim_state = WALKING;
    if (p->speed_x >= 8)
        p->anim_state = RUNNING;
    if (p->is_turning == sfTrue)
        p->anim_state = TURNING;
    if (p->is_jumping == sfTrue)
        p->anim_state = JUMPING;
    if (p->can_move == sfFalse && p->anim_state == WALKING)
        p->anim_state = PUSHING;
    p->anim_frame++;
    p->obj->rect.height = 48;
    p->obj->rect.width = 48;
    if (p->anim_frame % p->anim[p->anim_state].speed == 0 && p->anim[p->anim_state].length != 1)
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
    printf("pos: %f:%f\n", p->obj->pos.x, p->obj->pos.y);
    printf("map_pos: %i:%i\n", p->map_pos.x, p->map_pos.y);
    printf("collision: y=%f x=%f\n", p->collision_y / 100, p->collision_x / 100);
}

void raycast(player *p, game *g)
{
    p->is_edging = sfFalse;
    int rnd_pos = p->map_pos.x * 100;
    if (g->map[p->map_pos.y + 1][p->map_pos.x + p->direction] == 0) {
        if (p->obj->pos.x > (48 - 10) + rnd_pos && p->obj->pos.x < (48) + rnd_pos)
            p->is_edging = sfTrue;
        if (p->obj->pos.x > rnd_pos - 10 && p->obj->pos.x < rnd_pos)
            p->is_edging = sfTrue;
    }
    if (p->obj->pos.x >= rnd_pos + 50)
        p->map_pos.x++;
    for (int i = 0; g->map[p->map_pos.y + i + 1] != NULL; i++) {
        if (g->map[p->map_pos.y + i + 1][p->map_pos.x] != 0) {
            p->collision_y = (p->map_pos.y + i) * 100 + 4;
            break;
        }
    }
}

void update_player(player *p, game *g)
{
    if (p->obj->scale.x < 0)
        p->obj->pos.x -= 48 * 2;
    p->map_pos.x = (int)(p->obj->pos.x / 100);
    p->map_pos.y = (int)(p->obj->pos.y / 100);
    movement(p, g);
    raycast(p, g);
    gravity(p);
    animate(p);
    //print_status(p);
    sfSprite_setScale(p->obj->spr, p->obj->scale);
    sfSprite_setTextureRect(p->obj->spr, p->obj->rect);
    if (p->obj->scale.x < 0)
        p->obj->pos.x += 48 * 2;
    sfSprite_setPosition(p->obj->spr, p->obj->pos);
    sfRenderWindow_drawSprite(g->window, p->obj->spr, NULL);
}
