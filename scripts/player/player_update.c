/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** player_update.c
*/

#include "my_runner.h"

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

void do_death(player *p, game *g)
{
    if (p->is_dying == sfFalse) {
        g->camera_pan_speed = 0;
        sfMusic_stop(g->bg_music);
        sfMusic_stop(p->sound[DEATH]);
        sfMusic_play(p->sound[DEATH]);
        p->speed_y = -10;
        p->is_dying = sfTrue;
    }
}

void update_player(player *p, game *g)
{
    if (g->score % 100000 == 0 && g->score != 0)
        update_lives(p, g);
    if (is_solid(g->map[p->map_pos.y][p->map_pos.x]) == 0 && p->speed_y == 0)
        do_death(p, g);
    if (g->map[p->map_pos.y][p->map_pos.x] == 5)
        do_death(p, g);
    if (p->map_pos.x == g->width - 1)
        p->goal_reached = sfTrue;
    if (p->goal_reached == sfTrue) {
        tally(p, g);
    } else if (g->paused == sfFalse && g->is_runner == sfTrue) {
        p->speed_x = 5;
        p->is_dashing = sfFalse;
    }
    if (g->paused == sfFalse)
        update_unpaused(p, g);
    draw_player(p, g);
}
