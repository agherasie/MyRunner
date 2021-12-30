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
        p->obj->pos.x += g->camera_pan.x;
        p->obj->pos.y += g->camera_pan.y;
        if (p->goal_reached == sfFalse) {
            p->obj->pos.x -= g->camera_speed.x;
            p->obj->pos.y -= g->camera_speed.y;
        }
    } else {
        if (p->obj->scale.x < 0)
            p->obj->pos.x += 48 * 2;
        p->obj->pos.x -= g->camera_pan.x;
        p->obj->pos.y -= g->camera_pan.y;
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

void spring_collision(player *p, char *spring, game *g)
{
    sfVector2i m_p = {p->map_pos.x, p->map_pos.y};
    p->is_climbing = sfFalse;
    sfMusic_stop(p->sound[SPRING]);
    sfMusic_play(p->sound[SPRING]);
    switch (*spring) {
        case 100:
            p->speed_y = -15;
            p->is_jumping = sfTrue;
            break;
        case 102:
            p->speed_y = -27;
            p->is_jumping = sfTrue;
            break;
        case 104:
            p->speed_x = 0;
            directional_key(p, 1, sfFalse, g);
            p->speed_x = 7;
            directional_key(p, 1, sfTrue, g);
            break;
    }
    *spring += 1;
    p->cooldown = 10;
}

void update_player(player *p, game *g)
{
    sfVector2i m_p = {p->map_pos.x, p->map_pos.y};
    if (p->is_climbing == sfTrue) {
        p->speed_x = 0;
        p->is_gliding = sfFalse;
    }
    if (g->score % 100000 == 0 && g->score != 0)
        update_lives(p, g);
    if (g->map[m_p.y][m_p.x] >= 100 && g->map[m_p.y][m_p.x] % 2 == 0)
        spring_collision(p, &g->map[m_p.y][m_p.x], g);
    if (is_solid(g->map[m_p.y][m_p.x]) == 0 && p->speed_y == 0)
        do_death(p, g);
    if (g->map[m_p.y][m_p.x] == 5 || g->map[m_p.y][m_p.x] == 6)
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
