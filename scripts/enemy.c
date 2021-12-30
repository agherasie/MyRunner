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

void enemy_raycast(enemy *e, game *g, player *p)
{
    float speed = 2;
    sfSprite_setScale(e->obj->spr, (sfVector2f) {2 * e->direction, 2});
    if (e->obj->pos.x > p->obj->pos.x + 2)
        e->direction = 1;
    else if (e->obj->pos.x < p->obj->pos.x - 2)
        e->direction = -1;
    else
        speed = 0;
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

enemy create_enemy(int type, float spawn_pos, int free_spot)
{
    enemy e;
    if (type == -1)
        e.obj = create_object(50, 2, "art/crabmeat.png");
    if (type == 0)
        e.obj = create_object(50, 2, "art/crabmeat.png");
    if (type == 1)
        e.obj = create_object(50, 2, "art/motorbug.png");
    e.pos = spawn_pos;
    e.obj->pos.y = free_spot * 100 - 10;
    e.obj->pos.x = e.pos;
    e.enemytype = type;
    e.direction = -1;
    e.frame = 0;
    create_animation(&e.anim[0], 4, 30, sfTrue);
    create_animation(&e.anim[1], 5, 10, sfFalse);
    create_animation(&e.anim[2], 5, 10, sfFalse);
    e.is_dead = sfFalse;
    return e;
}

int find_free_spot(char **map, int map_pos_x)
{
    for (int y = 1; map[y] != NULL; y++)
        if (is_solid(map[y][map_pos_x]) == 0
        && is_solid(map[y - 1][map_pos_x]) == 1)
            return y - 1;
}

enemy *create_enemies(int enemy_count, char **map)
{
    enemy_count -= 2;
    enemy *e = malloc(sizeof(enemy) * (enemy_count + 1));
    e[enemy_count] = create_enemy(-1, 0, 0);
    for (int i = 0; i < enemy_count; i++) {
        int random_value = range(i * 300 + 500, i * 300 + 500);
        int free_spot = 0;
        int map_pos_x = random_value / 100;
        if (random_value % 100 >= 50)
            map_pos_x++;
        free_spot = find_free_spot(map, map_pos_x);
        e[i] = create_enemy(either_or(0, 1), random_value, free_spot);
        if (map[free_spot][map_pos_x] == 5 || map[5][map_pos_x] == 6
        || map[free_spot][map_pos_x] >= 100) {
            e[i].is_dead = sfTrue;
            e[i].frame = e[i].anim->length;
        }
    }
    return e;
}
