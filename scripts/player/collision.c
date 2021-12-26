/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** collision.c
*/

#include "my_runner.h"

int is_solid(int square)
{
    if (square == 0 || square == 1 || square == 4)
        return 1;
    return 0;
}

void edging(game *g, player *p)
{
    p->is_edging = 0;
    if (is_solid(g->map[p->map_pos.y + 1][p->map_pos.x + 1]) == 1)
        if (p->obj->pos.x > p->map_pos.x * 100 + 35
        && p->obj->pos.x < p->map_pos.x * 100 + 50)
            p->is_edging = 1;
    if (p->obj->pos.x > p->map_pos.x * 100 + 50)
        p->map_pos.x++;
    if (p->map_pos.x - 1 >= 0)
        if (is_solid(g->map[p->map_pos.y + 1][p->map_pos.x - 1]) == 1)
            if (p->obj->pos.x > p->map_pos.x * 100 - 50
            && p->obj->pos.x < p->map_pos.x * 100 - 35)
                p->is_edging = -1;
}

void raycast(player *p, game *g)
{
    edging(g, p);
    for (int i = 0; g->map[p->map_pos.y + i + 1] != NULL; i++)
        if (is_solid(g->map[p->map_pos.y + i + 1][p->map_pos.x]) == 0) {
            p->collision_y = (p->map_pos.y + i) * 100 + 4;
            break;
        }
}

void wall_collision(player *p, game *g)
{
    p->can_move = sfTrue;
    int rnd_pos = p->map_pos.x;
    if (is_solid(g->map[p->map_pos.y][rnd_pos + 1]) == 0
    && (int)(p->obj->pos.x) % 100 >= 30 && p->direction == 1) {
        p->speed_x = 0;
        p->obj->pos.x = (rnd_pos * 100) + 30;
        p->can_move = sfFalse;
    }
    if (p->obj->pos.x >= rnd_pos + 50)
        rnd_pos++;
    if (rnd_pos - 1 >= 0)
        if (is_solid(g->map[p->map_pos.y][rnd_pos - 1]) == 0
        && p->obj->pos.x <= rnd_pos * 100 - 26 && p->direction == -1) {
            p->speed_x = 0;
            p->obj->pos.x = rnd_pos * 100 - 26;
            p->can_move = sfFalse;
        }
}

void ring_collision(player *p, ring *r, game *g, int i)
{
    if (p->obj->pos.x >= (r->pos.x - 50 + g->camera_pan_x)
    && p->obj->pos.x <= (r->pos.x) + 50 + g->camera_pan_x
    && p->obj->pos.y >= (r->pos.y) - 20
    && p->obj->pos.y <= (r->pos.y) + 20
    && r->is_collected == sfFalse) {
        r->is_collected = sfTrue;
        g->rings++;
        sfMusic_stop(p->sound[RING_COLLECT]);
        sfMusic_play(p->sound[RING_COLLECT]);
    }
}

void enemy_collision(player *p, enemy *e, game *g)
{
    if ((p->obj->pos.x >= e->obj->pos.x - 48 + g->camera_pan_x
    && p->obj->pos.x <= e->obj->pos.x + 48 + g->camera_pan_x)
    && (p->obj->pos.y >= e->obj->pos.y - 20
    && p->obj->pos.y <= e->obj->pos.y + 20)
    && e->is_dead == sfFalse) {
        p->is_dropping = sfFalse;
        if (p->anim_state != JUMPING
        && p->anim_state != DASHING && p->anim_state != SPINNING
        && p->is_hurt == sfFalse) {
            p->is_hurt = sfTrue;
            p->speed_x = 0;
            p->speed_y = -8;
            p->cooldown = 7 * 8;
            g->score -= 150;
            if (g->rings > 0) {
                sfMusic_play(p->sound[RING_LOSS]);
                g->rings = 0;
            }
            else {
                sfMusic_stop(p->sound[DEATH]);
                sfMusic_stop(g->bg_music);
                sfMusic_play(p->sound[DEATH]);
            }
        } else if (p->anim_state == JUMPING
        || p->anim_state == DASHING || p->anim_state == SPINNING) {
            if (p->anim_state == JUMPING)
                p->speed_y = -8;
            e->is_dead = sfTrue;
            e->frame = 0;
            g->score += 100;
            sfMusic_play(p->sound[BADNIK_DEATH]);
        }
    }
}
