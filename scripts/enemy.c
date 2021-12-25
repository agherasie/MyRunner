/*
** EPITECH PROJECT, 2021
** MyRunner
** File description:
** enemy.c
*/

#include "my_runner.h"

void update_enemies(game *g, player *p)
{
    for (int i = 0; g->e[i].enemytype != -1; i++) {
        if (g->paused == sfFalse)
            g->e[i].obj->pos.x -= g->camera_pan_speed;
        sfSprite_setPosition(g->e[i].obj->spr, g->e[i].obj->pos);
        if (g->e[i].is_dead == sfTrue) {
            g->e[i].obj->rect.top = 50;
            animate_object(g, g->e[i].obj, g->e[i].anim[1], &g->e[i].frame);
        } else {
            animate_object(g, g->e[i].obj, g->e[i].anim[0], &g->e[i].frame);
        }
        sfSprite_setTextureRect(g->e[i].obj->spr, g->e[i].obj->rect);
        sfRenderWindow_drawSprite(g->window, g->e[i].obj->spr, NULL);
    }
}

enemy create_enemy(int type, float spawn_pos, int free_spot)
{
    enemy e;
    if (type == -1)
        e.obj = create_object(50, 2, "art/crabmeat.png");
    if (type == 0)
        e.obj = create_object(50, 2, "art/crabmeat.png");
    e.pos = spawn_pos;
    e.obj->pos.y = free_spot * 100;
    e.obj->pos.x = e.pos;
    e.enemytype = type;
    e.direction = -1;
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
    enemy *e = malloc(sizeof(enemy) * (enemy_count + 1));
    e[enemy_count] = create_enemy(-1, 0, 0);
    for (int i = 0; e[i].enemytype != -1; i++) {
        int random_value = range(enemy_count / 3 * 100 - 10, enemy_count / 3 * 100 + 30);
        int free_spot = 0;
        random_value *= i;
        random_value += 600;
        int map_pos_x = random_value / 100;
        if (random_value % 100 >= 50)
            map_pos_x++;
        free_spot = find_free_spot(map, map_pos_x);
        e[i] = create_enemy(0, random_value, free_spot);
    }
    return e;
}
