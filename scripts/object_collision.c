/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** object_collision.c
*/

#include "my_runner.h"


int is_ring_collision(player *p, ring *r, game *g)
{
    if (p->obj->pos.x >= (r->pos.x - 50 + g->camera_pan_x)
    && p->obj->pos.x <= (r->pos.x) + 50 + g->camera_pan_x
    && p->obj->pos.y >= (r->pos.y) - 20
    && p->obj->pos.y <= (r->pos.y) + 20
    && r->is_collected == sfFalse)
        return 0;
    return 1;
}

void ring_collision(player *p, ring *r, game *g, int i)
{
    r->is_collected = sfTrue;
    g->rings++;
    sfMusic_stop(p->sound[RING_COLLECT]);
    sfMusic_play(p->sound[RING_COLLECT]);
}

int is_enemy_collision(player *p, enemy *e, game *g)
{
    if ((p->obj->pos.x >= e->obj->pos.x - 55 + g->camera_pan_x
    && p->obj->pos.x <= e->obj->pos.x + 55 + g->camera_pan_x)
    && (p->obj->pos.y >= e->obj->pos.y - 48
    && p->obj->pos.y <= e->obj->pos.y + 48)
    && e->is_dead == sfFalse)
        return 0;
    return 1;
}

int is_attacking(player *p)
{
    int st = p->anim_state;
    if (st == JUMPING || st == DASHING || st == SPINNING)
        return 0;
    return 1;
}

void enemy_collision(player *p, enemy *e, game *g)
{
    p->is_dropping = sfFalse;
    if (is_attacking(p) == 1 && p->is_hurt == sfFalse)
        player_hit(p, g);
    else if (is_attacking(p) == 0) {
        if (p->anim_state == JUMPING)
            p->speed_y = -8;
        e->is_dead = sfTrue;
        e->frame = 0;
        g->score += 100;
        sfMusic_stop(p->sound[BADNIK_DEATH]);
        sfMusic_play(p->sound[BADNIK_DEATH]);
    }
}