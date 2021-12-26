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
    if (p->is_dropping == sfTrue)
        printf("is_dropping\n");
    printf("pos: %0.2f:%0.2f\n", p->obj->pos.x, p->obj->pos.y);
    printf("map_pos: %i:%i\n", p->map_pos.x, p->map_pos.y);
    if (p->is_hurt == sfTrue)
        printf("is_hurt\n");
}

void invisible_walls(player *p, game *g)
{
    if (p->obj->pos.x <= g->camera_pan_x - 24)
        p->obj->pos.x = g->camera_pan_x - 24;
    g->camera_pan_speed = 0;
    if (p->obj->pos.x >= g->camera_pan_x + W_W / 2)
        g->camera_pan_speed = 5;
    if (p->obj->pos.x >= g->camera_pan_x + W_W - 88)
        g->camera_pan_speed = 10;
    if (p->obj->pos.y <= 0)
        p->obj->pos.y = 0;
}

void camera_adjustments(player *p, game *g, sfBool is_first)
{
    if (is_first == sfTrue) {
        if (p->obj->scale.x < 0)
            p->obj->pos.x -= 48 * 2;
        p->obj->pos.x += g->camera_pan_x;
        if (p->goal_reached == sfFalse)
            p->obj->pos.x -= g->camera_pan_speed;
    } else {
        if (p->obj->scale.x < 0)
            p->obj->pos.x += 48 * 2;
        p->obj->pos.x -= g->camera_pan_x;
    }
}

void draw_player(player *p, game *g)
{
    sfSprite_setScale(p->obj->spr, p->obj->scale);
    sfSprite_setTextureRect(p->obj->spr, p->obj->rect);
    sfSprite_setPosition(p->obj->spr, p->obj->pos);
    sfRenderWindow_drawSprite(g->window, p->obj->spr, NULL);
}

void misc(player *p)
{
    if (p->is_grounded == sfFalse || p->speed_x > 0) {
        p->is_crouching = sfFalse;
        p->is_looking = sfFalse;
    }
    p->map_pos.x = (int)(p->obj->pos.x / 100);
    p->map_pos.y = (int)((p->obj->pos.y + 48) / 100);
}

void sound_update(player *p)
{
    if (p->speed_y >= 1 && p->speed_y <= 2) {
        sfMusic_stop(p->sound[JUMP]);
        sfMusic_stop(p->sound[BADNIK_DEATH]);
    }
    if (p->is_turning == sfTrue)
        sfMusic_play(p->sound[BRAKE]);
    else
        sfMusic_stop(p->sound[BRAKE]);
    if (p->is_hurt == sfFalse) {
        sfMusic_stop(p->sound[RING_LOSS]);
        sfMusic_stop(p->sound[DEATH]);
    }
}

void update_player(player *p, game *g)
{
    if (p->map_pos.x == g->width - 1)
        p->goal_reached = sfTrue;
    if (g->paused == sfFalse) {
        camera_adjustments(p, g, sfTrue);
        if (p->speed_x > 0) {
            p->is_spinning = sfFalse;
            p->is_charging = sfFalse;
        }
        if (p->speed_x <= 8)
            p->is_speeding = sfFalse;
        if (p->is_dashing == sfTrue && p->speed_x == 0)
            p->is_dashing = sfFalse;
        if (p->is_hurt && is_solid(g->map[p->map_pos.y][p->map_pos.x + p->direction]) == 1)
            p->obj->pos.x -= p->cooldown / 10 * p->direction;
        p->cooldown--;
        if (p->speed_x >= 0 && p->is_hurt == sfTrue) {
            p->speed_x = 0;
            if (p->cooldown <= 0)
                p->is_hurt = sfFalse;
        }
        if (p->is_dying == sfTrue)
            restart(g, p);
        misc(p);
        invisible_walls(p, g);
        for (int i = 0; g->e[i].enemytype != -1; i++)
            enemy_collision(p, &g->e[i], g);
        for (int i = 0; g->r[i].is_null != sfTrue; i++)
            ring_collision(p, &g->r[i], g, i);
        movement(p, g);
        raycast(p, g);
        gravity(p);
        animate(p);
        //print_status(p);
        camera_adjustments(p, g, sfFalse);
        sound_update(p);
        if (p->obj->pos.x + g->camera_pan_x >= g->width * 100 - 70)
            p->speed_x = 0;
    }
    draw_player(p, g);
}
