/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** enemy.c
*/

#include "my_runner.h"

void enemy_death(enemy *e, player *p)
{
    e->is_dead = sfTrue;
    e->frame = 0;
    sfMusic_stop(p->sound[BADNIK_DEATH]);
    sfMusic_play(p->sound[BADNIK_DEATH]);
}

void enemy_movement(enemy *e, game *g, player *p, float speed)
{
    float collision_y = 0;
    int x = (int)((e->obj->pos.x + g->camera_pan.x) / 100);
    int y = (int)((e->obj->pos.y + g->camera_pan.y) / 100);
    if ((int)(e->obj->pos.x + g->camera_pan.x) % 100 >= 50)
        x++;
    if (y != 5 && is_solid(g->map[y + 1][x]) == 1)
        e->obj->pos.y += 5;
    for (int i = 0; g->map[y + i + 1] != NULL; i++)
        if (is_solid(g->map[y + i + 1][x]) == 0) {
            collision_y = (y + i) * 100 - g->camera_pan.y;
            break;
        }
    if (e->obj->pos.y >= collision_y)
        e->obj->pos.y = collision_y;
    if (is_solid(g->map[y][x]) == 0)
        enemy_death(e, p);
    if (e->enemytype == 1
    && p->obj->pos.x > e->obj->pos.x - 200
    && p->obj->pos.x < e->obj->pos.x + 250
    && (y >= p->map_pos.y - 1) && (y <= p->map_pos.y + 1))
        e->obj->pos.x -= speed * e->direction;
}

void enemy_raycast(enemy *e, game *g, player *p)
{
    float speed = 2;
    sfSprite_setScale(e->obj->spr, (sfVector2f) {2 * e->direction, 2});
    if (e->obj->pos.x > p->obj->pos.x + 2 && e->is_dead == sfFalse)
        e->direction = 1;
    else if (e->obj->pos.x < p->obj->pos.x - 2 && e->is_dead == sfFalse)
        e->direction = -1;
    else
        speed = 0;
    enemy_movement(e, g, p, speed);
}

void update_enemies(game *g, player *p, enemy *e)
{
    if (g->paused == sfFalse && p->goal_reached == sfFalse) {
        e->obj->pos.x -= g->camera_speed.x;
        e->obj->pos.y -= g->camera_speed.y;
    }
    sfVector2f pos = e->obj->pos;
    pos.x += e->direction == 1 ? 0 : 100;
    sfSprite_setPosition(e->obj->spr, pos);
    if (e->is_dead == sfFalse)
        enemy_raycast(e, g, p);
    if (e->is_dead == sfTrue) {
        e->obj->rect.top = 50;
        animate_object(g, e->obj, e->anim[1], &e->frame);
    } else
        animate_object(g, e->obj, e->anim[0], &e->frame);
    sfSprite_setTextureRect(e->obj->spr, e->obj->rect);
    sfRenderWindow_drawSprite(g->window, e->obj->spr, NULL);
}
