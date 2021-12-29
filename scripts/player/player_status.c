/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** player_status.c
*/

#include "my_runner.h"

void dashing(player *p)
{
    if (p->speed_x > 0) {
        p->is_spinning = sfFalse;
        p->is_charging = sfFalse;
    }
    if (p->speed_x <= 8)
        p->is_speeding = sfFalse;
    if (p->is_dashing == sfTrue && p->speed_x == 0)
        p->is_dashing = sfFalse;
}

void damage(player *p, game *g)
{
    if (p->is_hurt) {
        p->is_dropping = sfFalse;
        p->is_flying = sfFalse;
        p->is_gliding = sfFalse;
    }
    int solid = is_solid(g->map[p->map_pos.y][p->map_pos.x + p->direction]);
    if (p->is_hurt && solid == 1)
        p->obj->pos.x -= p->cooldown / 10 * p->direction;
    p->cooldown--;
    if (p->speed_x >= 0 && p->is_hurt == sfTrue) {
        p->speed_x = 0;
        if (p->cooldown <= 0)
            p->is_hurt = sfFalse;
    }
}

void dying(player *p, game *g)
{
    sfMusic_stop(g->bg_music);
    p->speed_y += 0.25f;
    p->obj->pos.y += p->speed_y;
    if (p->obj->pos.y > W_H) {
        g->lives--;
        if (g->lives == 0) {
            g->relaunch = sfTrue;
            sfRenderWindow_close(g->window);
        }
        else {
            g->score = 0;
            restart(g, p);
        }
    }
}

void update_living(player *p, game *g)
{
    for (int i = 0; g->e[i].enemytype != -1; i++)
        if (is_enemy_collision(p, &g->e[i], g) == 0)
            enemy_collision(p, &g->e[i], g);
    for (int i = 0; g->r[i].is_null != sfTrue; i++)
        if (is_ring_collision(p, &g->r[i], g) == 0)
            ring_collision(p, &g->r[i], g, i);
    misc(p);
    movement(p, g);
    raycast(p, g);
    gravity(p);
}

void update_unpaused(player *p, game *g)
{
    if (p->obj->pos.x + g->camera_pan_x >= g->width * 100 - 70)
        p->speed_x = 0;
    camera_adjustments(p, g, sfTrue);
    dashing(p);
    damage(p, g);
    invisible_walls(p, g);
    animate(p);
    if (p->is_dying == sfTrue)
        dying(p, g);
    else
        update_living(p, g);
    camera_adjustments(p, g, sfFalse);
    sound_update(p);
}
