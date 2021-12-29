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

void update_player(player *p, game *g)
{
    sfVector2i m_p = {p->map_pos.x, p->map_pos.y};
    if (g->score % 100000 == 0 && g->score != 0)
        update_lives(p, g);
    if (is_solid(g->map[m_p.y][m_p.x]) == 0 && p->speed_y == 0)
        do_death(p, g);
    if (g->map[m_p.y][m_p.x] >= 5)
        do_death(p, g);
    if (g->map[m_p.y + 1][m_p.x] == 6 && p->is_grounded == sfTrue)
        player_hit(p, g);
    if (m_p.x == g->width - 2)
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
